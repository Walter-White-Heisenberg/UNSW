#include<stdio.h>
int main(void){
    char x;
    int line = 0, ch = 0 ,word = 1, i = 0, k = 0;
    x = getchar();
    while(x != EOF){
        if((x < 91 && x > 64) || (x < 123 && x > 96)){
            ch++;
            i = 1;
        }else if(x == 10){
            line++;
            k = 1;
        }else if(x == 32){
            k = 1;
        }if(i + k == 2){
            word++;
            i = 0;
            k = 0;
        }
        x = getchar();
    }
    if(ch == 0){
        word = 0;
    }
    printf("\n%d lines %d words %d characters\n",line + 1, word, ch);
    return 0;
}
