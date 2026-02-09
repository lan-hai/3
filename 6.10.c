#include<stdio.h>
#include<string.h>
int main ()
{
    char m[100];
    char n[100];
    fgets(m,100,stdin);
    m[strcspn(m, "\n")] = 0; 
    fgets(n,100,stdin);
    n[strcspn(n, "\n")] = 0;
    int j,k,s=0;
    j=strlen(m);
    k=strlen(n);
    
    int i, p;
    i = 0;
    while(i <= j - k)  
    {
        int flag = 1;
        for(p=0; p<k; p++)
        {
            if(m[i+p] != n[p])
            {
                flag = 0;
                break;
            }
        }
        
        if(flag) 
        {
            for(p=i; p<=j-k; p++)
            {
                m[p] = m[p+k];
            }
            s = 1;
            j = j - k; 
        }
        else
        {
            i++; 
        }
    }
    m[j] = '\0'; 
    printf("%s\n",m);
    printf("%d",s);
    return 0;
}