#include "stdio.h"
#include "string.h"
typedef struct c_node{
    char data;
    struct c_node *next;
} C_NODE;    
void createLinkList(C_NODE **headp, char s[]);
void judgePalindrome(C_NODE *head);
int main()  
{
char s[1000],*pc=s;
int len=0;
C_NODE *head,*p;
scanf("%[^\n]",s);
createLinkList(&head,s);   
for(p=head;p;p=p->next) len++;
if (len!=strlen(s)) { printf("单链表长度不正确");return 1;}
else for(p=head;p;p=p->next)
        if (p->data!=*pc++) { printf("单链表有错误结点");return 1;}
judgePalindrome(head);
return 1;
}
void createLinkList(C_NODE **headp, char s[]) 
{
    C_NODE *tail=NULL;
    *headp = NULL;
    int i=0;
  while(s[i])
  {
    C_NODE *p =(C_NODE*) malloc(sizeof(C_NODE));
    strcpy(p->data, s[i]);
    if(*headp =NULL)
    *headp=p;
    else
    tail->next=p;
    tail=p;
    
    if(tail!=NULL)
    tail->next=NULL;
    i++;
  }
  return;

}

void judgePalindrome(C_NODE *head)
{
  C_NODE *p;
  int lenth=0;
  p=head;
  while(p)
  {
    p=p->next;
    lenth++;
  }    
 char *stack = (char*)malloc(lenth/2*sizeof(char));
  p=head;
  int top=-1;
  for(int i=0;i<lenth/2;i++)
{
    stack[++top]=p->data;
    p=p->next;
}
if(lenth%2==1)
    p=p->next;
while(p)
{
    if(stack[top--]!=p->data)
    {
        printf("false\n");
        return;
    }
    p=p->next;
}
printf("true\n");
return;
}