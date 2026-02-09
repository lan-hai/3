#include<stdio.h>
void RemoveSave(int *n,int* m)
{
for(int i=0;i<(*m)-1;i++)
  if(n[i]==n[i+1])
  {                                                                                          
        for(int j=i;j<(*m)-1;j++)
        {
            n[j]=n[j+1];
        }
        (*m)--;
        i--;
  }                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  
}
int main ()
{
int m;
scanf("%d",&m);
int n[m];
for(int i=0;i<m;i++)
{
    scanf("%d",&n[i]);
}
RemoveSave(n,&m);
for(int k=0;k<m;k++)
{
    printf("%d ",n[k]);
}
printf("\n%d",m );

return 0;
}