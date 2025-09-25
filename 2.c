#include<stdio.h>
#include"civetweb.h"
#include<string.h>
#include<math.h>

float calculate_expression(const char*expression){
    int num1,num2;
    char op;


if (sscanf(expression, "%d%c%d", &num1, &op, &num2) >= 2) {
        switch (op) {
            case '+': return num1 + num2;
            case '-': return num1 - num2;
            case '*': return num1 * num2;
            case '/': return num2 != 0 ? num1 / num2 : NAN;
            default: return NAN;
        }
}
   return NAN;
}
int calculate_handler(struct mg_connection *conn, void *cbdata) {
    const struct mg_request_info *req_info = mg_get_request_info(conn);
    
    
    char expr[256];
    if (mg_get_var(conn, "expr", expr, sizeof(expr)) > 0) {
        float result = calculate_expression(expr);
        char response[256];
        
        if (isnan(result)) {
            snprintf(response, sizeof(response), 
                    "{\"error\": \"Invalid expression: %s\"}", expr);
            mg_printf(conn, "HTTP/1.1 400 Bad Request\r\n"
                      "Content-Type: application/json\r\n"
                      "Access-Control-Allow-Origin: *\r\n\r\n%s", response);
        } else {
            snprintf(response, sizeof(response), 
                    "{\"expression\": \"%s\", \"result\": %.6f}", expr, result);
            mg_printf(conn, "HTTP/1.1 200 OK\r\n"
                      "Content-Type: application/json\r\n"
                      "Access-Control-Allow-Origin: *\r\n\r\n%s", response);
        }
    } else {
        mg_printf(conn, "HTTP/1.1 400 Bad Request\r\n"
                  "Content-Type: application/json\r\n\r\n"
                  "{\"error\": \"Missing expr parameter\"}");
    }
    
    return 1; 
}


int home_handler(struct mg_connection *conn, void *cbdata) {
    const char *page = "<html><body>"
                      "<h1>Calculator Server</h1>"
                      "<p>Usage: /ping?expr=2+3</p>"
                      "</body></html>";
    
    mg_printf(conn, "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n%s", page);
    return 1;
}

int main() {
    struct mg_context *ctx;
    struct mg_callbacks callbacks;
    const char *options[] = {
        "listening_ports", "8080",
        "document_root", ".",
        NULL
    };
    
    memset(&callbacks, 0, sizeof(callbacks));
    
    ctx = mg_start(&callbacks, NULL, options);
    if (ctx == NULL) {
        fprintf(stderr, "Failed to start server\n");
        return 1;
    }
    
    
    mg_set_request_handler(ctx, "/ping", calculate_handler, NULL);
    mg_set_request_handler(ctx, "/", home_handler, NULL);
    
    printf("Calculator server running on http://localhost:8080\n");
    printf("Press Enter to stop...\n");
    getchar();
    
    mg_stop(ctx);
    return 0;
}