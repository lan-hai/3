#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int count = 0;

struct intNodes {
    char data;
    struct intNodes* next;
};
typedef struct intNodes Node;

// 创建链表（以回车结束）
Node* createlist() {
    Node* head, *tail, *p;
    char x;
    head = NULL;
    tail = NULL;
    
    // 读取第一个字符，跳过可能的空白字符
    scanf("%c", &x);
    
    while(1) {
        // 检查是否读取失败或遇到换行符
        if(x == '\n') {
            break;
        }
        
        p = (Node*)malloc(sizeof(Node));
        p->data = x;
        p->next = NULL;
        
        if(head == NULL) {
            head = p;
        } else {
            tail->next = p;
        }
        tail = p;
        count++;
        
        // 读取下一个字符
        scanf("%c", &x);
    }
    
    if(tail != NULL) {
        tail->next = NULL;
    }
    
    return head;
}

// 遍历输出链表（字符间有空格）
void printlist(Node* head) {
    Node* p = head;
    while(p != NULL) {
        if(p->next != NULL)
            printf("%c ", p->data);
        else
            printf("%c", p->data);
        p = p->next;
    }
    printf("\n");
}

// 计算绝对值
int abs_val(int a) {
    return a > 0 ? a : -a;
}

// 修改节点，返回新的头节点
Node* changeNode(Node* head, char x) {
    Node* p = head;
    Node* q = NULL;
    Node* temp = NULL;
    Node* new = NULL;
    Node* j = head;
    int min;
    int sign = 0;
    
    // 查找要删除的节点
    while(p != NULL && p->data != x) {
        q = p;
        p = p->next;
    }
    
    // 如果找到，删除节点
    if(p != NULL && p->data == x) {
        if(p == head) {
            head = p->next;
        } else {
            q->next = p->next;
        }
        free(p);
        sign = 1;
        count--;  // 更新节点计数
    }
    
    // 如果没找到，插入新节点
    if(sign == 0) {
        new = (Node*)malloc(sizeof(Node));
        new->data = x;
        new->next = NULL;
        
        // 如果链表为空
        if(head == NULL) {
            head = new;
        } else {
            // 找到差值最小的节点
            min = abs_val(head->data - x);
            temp = head;
            j = head->next;
            
            while(j != NULL) {
                int diff = abs_val(j->data - x);
                if(diff < min) {
                    min = diff;
                    temp = j;
                }
                j = j->next;
            }
            
            // 在temp后面插入新节点
            new->next = temp->next;
            temp->next = new;
        }
        count++;  // 更新节点计数
    }
    
    return head;
}

// 将链表转换为字符串
char* listToString(Node* head) {
    char* str = (char*)malloc((count + 1) * sizeof(char));
    Node* p = head;
    int n = 0;
    while(p != NULL) {
        str[n] = p->data;
        n++;
        p = p->next;
    }
    str[n] = '\0';
    return str;
}

int main() {
    char m;
    Node* head, *l;
    
    // 创建链表
    head = createlist();
    l = head;
    
    // 打印链表（带空格）
    printlist(head);
    
    // 将链表转换为字符串并输出
    char* str = listToString(head);
    printf("%s\n", str);
    
    // 读取要处理的字符（跳过可能的空白字符）
    scanf(" %c", &m);  // 注意空格，用于跳过换行符
    
    // 修改链表
    head = changeNode(head, m);
    
    // 输出修改后的字符串
    char* newStr = listToString(head);
    printf("%s\n", newStr);
    
    // 释放内存
    free(str);
    free(newStr);
    
    // 释放链表
    Node* p = head;
    while(p != NULL) {
        Node* temp = p;
        p = p->next;
        free(temp);
    }
    
    return 0;
}
