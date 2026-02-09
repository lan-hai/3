 #include<stdio.h>
 #include<string.h>
 void scheduler(char *,int m);
 void task0();
 void task1();
 void task2();
void task3();
void task4();
void task5();
void task6();
void task7();
 int main()
 {
    int m;
    char str[100];
    scanf("%s",str);
    m = strlen(str);
    scheduler(str,m);
    return 0;
 }
 void task0()
 {
    printf("task0 is called!\n");
 }

  void task1()
 {
    printf("task1 is called!\n");
 }
  void task2()
 {
    printf("task2 is called!\n");
 }
  void task3()
 {
    printf("task3 is called!\n");
 }
  void task4()
 {
    printf("task4 is called!\n");
 }
  void task5()
 {
    printf("task5 is called!\n");
 }
  void task6()
 {
    printf("task6 is called!\n");
 }
  void task7()
 {
    printf("task7 is called!\n");
 }
void scheduler(char *str,int m)
{
    void (*taskptr[8])()={task0,task1,task2,task3,task4,task5,task6,task7};
    for(int i=0;i<m;i++)
    {
        (*taskptr[str[i]-'0'])();
    }
   
}