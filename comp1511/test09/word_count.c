#include<stdio.h>
int main(void){
    char x;
    int m = 1998,i = 0,k = 0,line = 0, ch = 0 ,word = 0;
    x = getchar();
    while(x != EOF){
        ch++;
        m = x;//m will be the last non-EOF character.
        if((x - 10) * (x - 32) != 0){ 
            i = 1;
        }else {
            line = line + (x == 10);
            k = 1;
        }if(i == 1 && k == 1){
            word++;
            i = 0;
            k = 0;
        }else{
            k = 0;
        }
        x = getchar();      
    }
    printf("\n%d lines %d words %d characters\n",
    line, word + (ch != 0) - (ch != 0) * ((m-10) * (m-32) == 0), ch);
    return 0;
}
