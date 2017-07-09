#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
int main()
{
    string my_str = get_string();
    int length = strlen(my_str);
    for(int i=0; i<length; i++){
        if(i==0){
            if(my_str[i]!=' '){
                char ch = toupper(my_str[i]);
                printf("%c", ch);
            }
        }
        else{
            if((my_str[i-1]==' ') && (my_str[i]!= ' ')){
                char ch = toupper(my_str[i]);
                printf("%c", ch);
            }
        }
    }
    printf("\n");
    return 0;
}