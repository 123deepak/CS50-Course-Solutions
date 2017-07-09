#include <stdio.h>
#include <cs50.h>

int main()
{
    while(1)
    {
        printf("Height: ");
        int a = get_int();
        if(a==0)
        break;
        else if (a<0)
        continue;
        else if(a<=23)
        {
            for(int i=1; i<=a;i++)
            {
                for(int j=1;j<=a-i;j++)
                printf(" ");
                for(int j=1;j<=i;j++)
                printf("#");
                printf("  ");
                for(int j=1;j<=i;j++)
                printf("#");
                printf("\n");
            }
            break;
        }
    }
}