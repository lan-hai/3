#include<stdio.h>
int main ()
{
char *p;
int m;
scanf("%d",&m);
p=(char *)&m;
char low,high;
for(int k=0;k<4;k++)
{
    low = *p&0x0f;
    if (low<10)
    low+='0';
    else
    low=low-10+'a';
    high=(*p>>4)&0x0f;
      if (high<10)
    high+='0';
    else
    high=high-10+'a';
    p++;
    printf("%c %c ",high,low);    
}

return 0;

}