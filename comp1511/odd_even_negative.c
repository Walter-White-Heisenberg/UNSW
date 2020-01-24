#include<stdio.h>
int main(void)
{
    int a,i;
    i=0;
    int array[1001]={0};
    while(array[1000] >= 0){
        scanf("%d",&array[i]);
        if(array[i] < 0){
            array[1000] = -1;
        }
        i++;       
    }
    a=0;
    printf("Odd numbers were: ");
    while(a < i - 1){
        if(array[a] % 2 == 1){
        printf("%d ",array[a]);
        }
        a++;       
    }
    printf("\n");
    a=0;
    printf("Even numbers were: ");
    while(a < i - 1){
        if(array[a] % 2 == 0){
        printf("%d ",array[a]);
        }
        a++;       
    }
    printf("\n");
    return 0;
}
