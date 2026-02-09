#include<stdio.h>
#include<math.h>
int meishensushu(int i);
int main()
{
int n;
scanf("%d",&n);
if(n>3)
{
printf("M(2)=3\n");
for(int l=4;l<=n;l++)
{
if (meishensushu(l))
printf("M(%d)=%d\n",meishensushu(l),l);
}
}
return 0;
}
int meishensushu(int i)
{
    int sign=0;
for(int j=2;j<=sqrt(i);j++)
{
    if (i%j==0)
    {
        return 0;
    }
    else
    sign=1;
    
}
if ((int)(log2(i+1))%1==0)
{
    for(int k=2;k<=sqrt(log2(i+1));k++)
    {
        if((int)(log2(i+1))%k==0)
        {
            return 0;
        }
        else if(sign==1)
        return (log2(i+1));
    }
}
}