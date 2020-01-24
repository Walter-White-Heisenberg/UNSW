#include<stdio.h>
int main(void){
    int input,h,w,i,j;
    scanf("%d",&input);
    h=input*2-1;
    w=9*input;
    i=0;
    while(i<h){
        j=1;
        while(j<=w){
            if((j-3*input)*(j-3*input-1)==0){
                printf(" ");
            }else{
                printf("#");
            }
            j++;
        }
        printf("\n");
        i++;
    }
    printf("\n\n");
    i=0;
    while(i<h){
        j=1;
        while(j<=w){
            if((j-3*input)*(j-3*input-1)==0){
                printf(" ");
            }else{
                printf("#");
            }
            j++;
        }
        printf("\n");
        i++;
    }
}
