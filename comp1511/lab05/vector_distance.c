#include<stdio.h>
#include<math.h>
int main(void)
{   int x;
    int size;
    printf("Enter vector length: ");
    scanf("%d",&size);  
    int array1[size];
    int array2[size];
    printf("Enter vector 1: ");
    x=0;
    while(x<size){
        scanf("%d", &array1[x]);
        x++;
        }
    printf("Enter vector 2: ");
    while(x<size){
        scanf("%d", &array2[x]);
        x++;
    }
    int d=0;
    x=0;
    while(x<size){
        d= d + (array1[x]-array2[x])*(array1[x]-array2[x]);
        x++;
        }
    printf("Euclidean distance = %f\n", sqrt(d));
    return 0;
}

