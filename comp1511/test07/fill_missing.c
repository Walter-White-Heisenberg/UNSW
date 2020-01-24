#include<stdio.h>
#include<stdlib.h>
int main(void){
    int min,max,i,argv[10000];
    i = 1;
    while(scanf("%d",&argv[i]) == 1){
        i++;
    }
    int s = 0;
    max = argv[0];
    while(s < i-1){
        if(max < argv[s]){
            max = argv[s];
        }
        s++;
    }
    i = 1;    
    while(i <= max){
        int counter = 0;
        int a = 1;
        while(a < argc){
            if(i == argv[a]){
                counter++;
            }
            a++;
        }if(counter == 0){
            printf("%d ",i);
        }
        i++;
    }
    printf("\n");
} 
