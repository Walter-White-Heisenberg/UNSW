#include<stdio.h>
int main(int ggg, char **vvvv){
 // scanf("argc = %d\n", argc);
    
    int i=0;
    while(i < ggg){
        printf("argv[%d] = %s\n", i, vvvv[i]);
        i++;
    }
}
