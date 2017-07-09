#include <stdio.h>
#include <cs50.h>

int main()
{
    int c;
    printf("O hai! How much change is owed?\n");
    while(1){
        c=0;
        float n = get_float();
        int num;
        if(n<0){
            printf("How much change is owed?\n");
        }
        if(n>=1){
            c = ((int)n/1)*4;
            n = n-(int)n;
            if(n==0)
            goto a1;
            n = n + .000666;
        }
        n=n*100;
        num=n;
        while(num>0){
            if(num>=25){
                num=num-25;
                c++;
            }
            else if(num>=10){
                num=num-10;
                c++;
            }
            else if(num>=5){
                num=num-5;
                c++;
            }
            else if(num>=1){
                num=num-1;
                c++;
            }
            if(num==0)
              goto a1;
        }
    }
    a1:
        printf("%i\n",c);
}