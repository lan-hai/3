#include<stdio.h>
#include<string.h>
int main ()
{
 char *(*p)(char *, const char *);
 char a[80],b[80];
 char *result;
 int choice;
 while(1)
 {
    do
    {
      scanf("%d", &choice);
        
    } while(choice<1 || choice>4);
    switch(choice)
    {
        case 1:p=strcpy;break;
        case 2:p=strcat;break;
        case 3:p=strtok;break;
        case 4:   goto down;
    }
    getchar();
    fgets(a,80,stdin);
    a[strcspn(a, "\n")] = 0; 
    fgets(b,80,stdin);
    b[strcspn(b, "\n")] = 0;
    result=p(a,b);
    printf("%s\n",result);
 }
down:
 return 0;
}
