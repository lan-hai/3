#include<stdio.h>
int main ()
{
int m,n;
scanf("%d %d",&m,&n);
int k[m][n];
int l[n][m];
for(int i=0;i<m;i++)
{
    for(int j=0;j<n;j++)
    {
        scanf("%d",&k[i][j]);
        l[j][i]=0;
    }
}
for(int i=0;i<n;i++)
{
    for(int j=0;j<m;j++)
    {
        l[n-1-i][j]=k[j][i];
    }

}
for(int i=0;i<n;i++)
{
    for(int j=0;j<m;j++)
    {
        if (j!=m-1)
        printf("%d ",l[i][j]);
        else
        printf("%d",l[i][j]);
    }
    printf("\n");
}
return 0;
}