#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student{
    char xuehao[20];
    char name[20];
    int yingyu;
    int shuxue;
    int wuli;
    int cyuyan;
    int sum;
    float average;
    struct student *next;
};
void createlist(struct student ** head,struct student **tail,int n);
void sortlist(struct student *head);
int main(void)
{
    int m;
    struct student *head = NULL;
    struct student *tail = NULL;
    while (1)
    {
        if (scanf("%d", &m) != 1) break;
        if (m == 0)
            break;
        if (m == 1)
        {
            int n;
            scanf("%d", &n);
            if(head==NULL)
                createlist(&head, &tail, n);
                else
                createlist(&tail->next, &tail, n);
                 struct student *l = head;
            while (l)
            {
                l->sum = l->yingyu + l->shuxue + l->wuli + l->cyuyan;
                l->average = (float)(l->sum) / 4.0f;
                l = l->next;
            }
            sortlist(head);
        }
        else if (m == 2)
        {
            struct student *l = head;
            while (l)
            {
                printf("%s %s %d %d %d %d\n", l->xuehao, l->name, l->yingyu, l->shuxue, l->wuli, l->cyuyan);
                l = l->next;
            }
        }
        else if (m == 3)
        {
            char search_name[20];
            int type;
            int score;
            if (scanf("%19s %d %d", search_name, &type, &score) != 3) continue;
            struct student *l = head;

            while (l != NULL && strcmp(l->xuehao, search_name) != 0)
            {
                l = l->next;
            }

            if (l != NULL)
            {
                if (type == 1)
                {
                    l->yingyu = score;
                }
                else if (type == 2)
                {
                    l->shuxue = score;
                }
                else if (type == 3)
                {
                    l->wuli = score;
                }
                else if (type == 4)
                {
                    l->cyuyan = score;
                }
                l->sum = l->yingyu + l->shuxue + l->wuli + l->cyuyan;
                l->average = (float)(l->sum) / 4.0f;
           
            }
            sortlist(head);
           
           
        }
        else if (m == 4)
        {
            struct student *l = head;
            while (l)
            {
                l->sum = l->yingyu + l->shuxue + l->wuli + l->cyuyan;
                l->average = (float)(l->sum) / 4.0f;
                l = l->next;
            }
            struct student *o = head;
            while(o)
            {
                printf("%s %s %.2f\n",o->xuehao,o->name,o->average);
                o=o->next;
            }
        }
        else if (m == 5)
        {
            struct student *l = head;
            struct student *o = head;
             while (o)
            {
                o->sum = o->yingyu + o->shuxue + o->wuli + o->cyuyan;
                o->average = (float)(o->sum) / 4.0f;
                o = o->next;
            }
            while (l)
            {
                printf("%s %s %d %.2f\n", l->xuehao, l->name, l->sum, l->average);
                l = l->next;
            }
        }
    }

    struct student *p = head;
    while (p)
    {
        struct student *temp = p;
        p = p->next;
        free(temp);
    }
    return 0;
}
void createlist(struct student ** head,struct student **tail,int n)
{
    struct student *p = NULL;
    *head = NULL;
    *tail = NULL;
    int i;
    for (i = 0; i < n; i++)
    {
        p = (struct student *)malloc(sizeof(struct student));
        if (!p) exit(EXIT_FAILURE);
        if (scanf("%19s %19s %d %d %d %d", p->xuehao, p->name, &(p->yingyu), &(p->shuxue), &(p->wuli), &(p->cyuyan)) != 6)
        {
            free(p);
            break;
        }
        p->next = NULL;
        if (*head == NULL)
        {
            *head = p;
            *tail = p;
        }
        else
        {
            (*tail)->next = p;
            *tail = p;
        }
    }
    if (*tail)
        (*tail)->next = NULL;
}
void sortlist(struct student *head)
{
    struct student *i,*j;
    int temp;
    for(i=NULL;head!=i;i=j)
    {
        for(j = head;j->next!=i;j=j->next)
        {
        if(j->sum>j->next->sum)
        {
            
            char t1[20],t2[20];
            int t3,t4,t5,t6,t7;
            float t8;
            strcpy(t1,j->xuehao);
            strcpy(t2,j->name);
            t3=j->yingyu;
            t4=j->shuxue;
            t5=j->wuli;
            t6=j->cyuyan;
            t7=j->sum;
            t8=j->average;

            strcpy(j->xuehao,j->next->xuehao);
            strcpy(j->name,j->next->name);
            j->yingyu=j->next->yingyu;
            j->shuxue=j->next->shuxue;
            j->wuli=j->next->wuli;
            j->cyuyan=j->next->cyuyan;
            j->sum=j->next->sum;
            j->average=j->next->average;

            strcpy(j->next->xuehao,t1);
            strcpy(j->next->name,t2);
            j->next->yingyu=t3;
            j->next->shuxue=t4;
            j->next->wuli=t5;
            j->next->cyuyan=t6;
            j->next->sum=t7;
            j->next->average=t8;
        }
    }
}