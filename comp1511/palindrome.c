#include<stdio.h>
int main(void){
    printf("Enter a string: ");
    char s[4096] = {46};
    int i = 0;
    while((scanf("%c",&s[i]) == 1)){  
        i++;
    } 
    i = i - 2;
    int c=0
    while(c <= i){
        if(m[i] != s[i]){
            a++;
        }
    }if(a == 0){
        printf("String is a palindrome");
    }else{
        printf("String is not a palindrome");
    }
    printf("\n");            
}
