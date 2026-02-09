#include<stdio.h>
#include<string.h>
#include<stdlib.h>
void readfile(char*filename);
void readfile1(char*filename,int count);
int main()
{
	// 请在此处编辑您的代码
	/********** Begin **********/
    FILE * fp;
    char c;
    char *filename="src/step1_1/test1.c";
    char * s,* s0;
    scanf("%s %s",s,s0);
    char * s1="typr_c";
    char * s2="/p";
    if(strcmp(s,s1)==0)
    {
       if(strcmp(s0,s2)==0)
       {
         int count =0;
         while(scanf("%c",&c)==1)
         {
             count++;
         }
         readfile1(filename,count);
       }
       else
       {
       readfile(filename);
       }




    }
    
	/********** End **********/
	return 0; 
}
void readfile(char*filename)
{
    FILE * fp;
    char ch[100];
    if(fp=fopen(filename,"r")==NULL)
    {
        printf("can't open");
        exit(-1);
    }
    else
    {
      int i=1;
      while(!feof(fp))
      {
        if(fgets(ch,100,fp)!=NULL)
        {
            printf("%d  ",i);
            printf("%s",ch);
            printf("\n");
            
        }
        i++;
      } 
    }
}
void readfile1(char*filename,int count)
{
    FILE *fp;
    char ch[100];
    if(fp=fopen(filename,"r")==NULL)
    {
        printf("can't open");
        exit(-1);
    }
    else
    {
      int i=1;
      while(!feof(fp))
      {
        if(fgets(ch,100,fp)!=NULL)
        {
            printf("%d  ",i);
            printf("%s",ch);
            printf("\n");
            
        }
        i++;
        if(i=11&&count!=0)
        {
            i=1;
            count--;
        }
      } 
    }

}