#include<stdio.h>
int main(void){
    printf("Enter a string: ");
    char s[4096] = {46};
    int i = 0;
    while((scanf("%c",&s[i]) == 1)){  

        i++;
    }
    i = i - 2;
    int a;
    a = 0;
    int w = 0;
    char m[4096] = {46};
    while(a <= i) {
        if(s[a] <= 'Z' && s[a] >= 'A'){
            m[w] = s[a] + 'a' - 'A';
            w++;
        }else if(s[a] <= 'z' && s[a] >= 'a'){
            m[w] = s[a];
            w++;
        }
        a++;           
    }
    w = w - 1;
    int c = 0;
    a = 0;
    while(c <= w){
        if(m[w-c] != m[c]){
            a++;            
        }
        c++;
    }if(a == 0){
        printf("String is a palindrome");
    }else{
        printf("String is not a palindrome");
    }
    printf("\n");            
}
