#include <stdio.h>
#include <cs50.h>
#include <string.h>

string changeit(string str, int l){
    int len = strlen(str);
    for(int i=0; i<len; i++){
        if(str[i] >= 'a' && str[i]<='z'){
            if('z' > (str[i] + l)){
                str[i] = str[i] + l;
            }
            else{
                str[i] = (str[i] + l) - 'z' + 'a' - 1;    
            }
        }
        else if(str[i] >= 'A' && str[i]<='Z'){
           if('Z' > (str[i] + l)){
                str[i] = str[i] + l;
            }
            else{
                str[i] = (str[i] + l) - 'Z' + 'A' - 1;    
            }
        }
    }
    return str;
}

int main(int argc, string argv[])
{
    if(argc==2)
    {
        printf("plaintext:  ");
        string str = get_string();
        str = changeit(str,(atoi(argv[1]))%26);
        printf("ciphertext:  ");
        printf("%s\n",str);
        return 0;
    }
    printf("Error\n");
    return 1;
}