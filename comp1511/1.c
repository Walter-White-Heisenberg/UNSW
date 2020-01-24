#include<stdio.h>
int main(void)
{
    int i;
    i=0;
    int array[10];
    scanf("%d",&array[0]);
    while(array[i] != EOF){
        scanf("%d",&array[i]);
        i++;       
    }
    i=0;
    printf("Odd numbers were: ");
    while(i<10){
        if(array[i] % 2 == 1){
        printf("%d ",array[i]);
        }
        i++;       
    }
    printf("\n");
    i=0;
    printf("Even numbers were: ");
    while(i<10){
        if(array[i] % 2 == 0){
        printf("%d ",array[i]);
        }
        i++;       
    }
    printf("\n");
    return 0;
}
