#include<stdio.h>
int main(void){
    printf("How many boxes: \n");
    int x,r,i,j; 
    scanf("%d",&x);
    r=4*x-1;
    i=1;
    while(i<=2*x){
        j=1;
        if(i % 2 == 1){
            while(j<=r){
                if(j % 2 == 0 && (j<=i||j>r-i)){
                    printf("0");
                }else{
                    printf("1");
                }
                j++;
            }   
        }else{
            while(j<=r){
                if(j % 2 ==1 && (j<=i||j>r-i)){
                    printf("1");
                }else{
                    printf("0");
                }
                j++;
            }
        }
        printf("\n");
        i++;
    }
    while(0<i){
        j=1;
        if(i % 2 == 1){
            while(j<=r){
                if(j % 2 == 0 && (j<=i||j>r-i)){
                    printf("0");
                }else{
                    printf("1");
                }
                j++;
            }   
        }else{
            while(j<=r){
                if(j % 2 ==1 && (j<=i||j>r-i)){
                    printf("1");
                }else{
                    printf("0");
                }
                j++;
            }
        }
        printf("\n");
        i--;
    }
    return 0;
}
