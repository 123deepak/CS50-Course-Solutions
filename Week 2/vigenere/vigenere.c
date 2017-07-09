#include <stdio.h>
#include <cs50.h>
#include <string.h>

string changeit(string str, string cip){
    int len = strlen(str);
    int temp = strlen(cip);
    int t=0;
    for(int i=0; i<len; i++){
        if(t == temp)
            t = 0;
        if(str[i] >= 'a' && str[i]<='z'){
            if(cip[t] >= 'a' && cip[t]<='z'){
                if('z' >= (str[i] + cip[t] - 'a')){
                    str[i] = str[i] + cip[t] - 'a';
                }
                else{
                    str[i] = (str[i] + cip[t] - 'a') - 'z' + 'a' - 1;    
                }
            }
            else
            {
                if('z' >= (str[i] + cip[t] - 'A')){
                    str[i] = str[i] + cip[t] - 'A';
                }
                else{
                    str[i] = (str[i] + cip[t] - 'A') - 'z' + 'a' - 1;    
                }
            }
            t++;
        }
        else if(str[i] >= 'A' && str[i]<='Z'){
            if(cip[t] >= 'a' && cip[t]<='z'){
                if('Z' >= (str[i] + cip[t] - 'a')){
                    str[i] = str[i] + cip[t] - 'a';
                }
                else{
                    str[i] = (str[i] + cip[t] - 'a') - 'z' + 'a' - 1;    
                }
            }
            else{
                if('Z' >= (str[i] + cip[t] - 'A')){
                    str[i] = str[i] + cip[t] - 'A';
                }
                else{
                    str[i] = (str[i] + cip[t] - 'A') - 'z' + 'a' - 1;    
                }
            }
            t++;
        }
    }
    return str;
}

int main(int argc, string argv[])
{
    if(argc==2)
    {
        string cip = argv[1];
        int len = strlen(cip);
        for(int i=0; i<len; i++){
           if( (cip[i] >= 'a' && cip[i]<='z') || (cip[i] >= 'A' && cip[i]<='Z') )
           {
               
           }
           else
           goto a;
        }
        printf("plaintext:  ");
        string str = get_string();
        str = changeit(str,argv[1]);
        printf("ciphertext:  ");
        printf("%s\n",str);
        return 0;
    }
    a:
    printf("Error\n");
    return 1;
}