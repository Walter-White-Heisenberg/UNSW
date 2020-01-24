#include<stdio.h>
#include<stdlib.h>
int main(int argc, char **argv){
    int min,max,i;
    i = 1;
    while(i < argc){
        if(min > argv[i]){
            min = argv[i];
        }
        if(max < argv[i]){
            max = argv[i];
        }
        i++;
    }
    i = min;    
    while(i < max){
        int counter = 0;
        int a = 1;
        while(a < argc){
            if(i = argv[a]){
                counter++
            }
            a++;
        }if(counter = 0){
            printf("%d",i);
        }
        i++;
    }

} 
