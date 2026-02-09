#include<stdio.h>
struct bit{
    unsigned int bit0:1;
    unsigned int bit1:1;    
    unsigned int bit2:1;
    unsigned int bit3:1;
    unsigned int bit4:1;
    unsigned int bit5:1;
    unsigned int bit6:1;
    unsigned int bit7:1;
}a;
union{
    struct bit a;
    unsigned int b;
}x;
void f0()
{
    printf("the function 0 is called!\n");
}
void f1()
{
    printf("the function 1 is called!\n");
}
void f2()
{
    printf("the function 0 is called!\n");
}
void f3()
{
    printf("the function 0 is called!\n");
}
void f4()
{
    printf("the function 4 is called!\n");
}
void f5()
{
    printf("the function 5 is called!\n");
}
void f6()
{
    printf("the function 6 is called!\n");
}
void f7()
{
    printf("the function 7 is called!\n");
}
int main()
{
    void (*funptr[8])()={f0,f1,f2,f3,f4,f5,f6,f7};
    int i;
    scanf("%u",&x.b);
    if(x.a.bit0)
        (*funptr[0])();
    if(x.a.bit1)
        (*funptr[1])();
    if(x.a.bit2)
        (*funptr[2])();
    if(x.a.bit3)
        (*funptr[3])();
    if(x.a.bit4)
        (*funptr[4])();
    if(x.a.bit5)
        (*funptr[5])();
    if(x.a.bit6)
        (*funptr[6])();
    if(x.a.bit7)
        (*funptr[7])();
    return 0;
}