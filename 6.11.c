#include<stdio.h>
#include<ctype.h>
void getbignum(int *,int);
void mulitiplybignum(int *,int*,int *)  ;
void printbignum(int *);

int main ()
{
    int x[201],y[201],z[402];
    int lenx,leny;
    getbignum(x,200);
    getbignum(y,200);
    mulitiplybignum(x,y,z);
    printbignum(z);
    return 0;
}
void getbignum(int *x,int lim)
{
 int i,t,c;
 int *p1,*p2;
 for(i=1;i<=lim;i++)
    x[i]=0;
    for(i=1;i<=lim && isdigit(c=getchar());i++)
        x[i]=c-'0';
    x[0]=i-1;
    for(p1=x+1,p2=x+x[0];p1<p2; p1++,p2--)
    {
        t=*p1;
        *p1=*p2;
        *p2=t;
    }
}
void mulitiplybignum(int *x,int *y,int *z)
{
    int i,j;
    for(i=0;i<=x[0]+y[0];i++)
        z[i]=0;
    for(i=1;i<=x[0];i++)
        for(j=1;j<=y[0];j++)
            z[i+j-1]+=x[i]*y[j];
    z[0]=x[0]+y[0];
    for(i=1;i<=z[0];i++)
    {
        z[i+1]+=z[i]/10;
        z[i]%=10;
    }
    if(z[z[0]+1]>0)
        z[0]++;
}  
void printbignum(int *x)
{
    int i;
    for(i=x[0];i>=1;i--)
        putchar(x[i]+'0');
    putchar('\n');
}
