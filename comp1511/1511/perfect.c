#include<stdio.h>
int main(void){
    printf("Enter number: ");
    int x,i,total;
    scanf("%d",&x);
    printf("The factors of %d are:\n",x);
    i = 1;
    total=0;
    while(i<=x){
        if(x % i == 0){
            printf("%d\n",i);
            total=total+i;
        }
        i++;
    }
    printf("Sum of factors = %d\n",total);
    if(total == 2*x){
        printf("%d is a perfect number\n",x);
    }else{
        printf("%d is not a perfect number\n",x);    
    }
}
