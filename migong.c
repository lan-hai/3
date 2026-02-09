#include <stdio.h>

int maze[10][10];      
int path[10][10];      
int rows, cols;
int count = 0;         

int can_go(int x, int y) {
    return (x >= 0 && x < rows && y >= 0 && y < cols && 
            maze[x][y] == 1 && path[x][y] == 0);
}


void dfs(int x, int y) {
    
    if (x == rows-1 && y == cols-1) {
        count++;
        printf("%d\n", count);
        
        
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (j<cols-1)
                printf("%d ", path[i][j]);
                else
                printf("%d", path[i][j]);
            }
            printf("\n");
        }
        return;
    }
    
    int dx[] = {0, 1, 0, -1};
    int dy[] = {1, 0, -1, 0};
    
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        
        if (can_go(nx, ny)) {
            path[nx][ny] = 1;      
            dfs(nx, ny);           
            path[nx][ny] = 0;      
        }
    }
}

int main() {
    
    scanf("%d %d", &rows, &cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            scanf("%d", &maze[i][j]);
            path[i][j] = 0;        
        }
    }
    
    
    path[0][0] = 1;
    dfs(0, 0);
    
    return 0;
}