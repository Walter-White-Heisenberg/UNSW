#include<stdio.h>
int main(void)
{
    int x;
    int size;
    int y=0;
    int total;
    
    printf("Enter vector length: ");
    scanf("%d",&size);

    int array[size];
    printf("Enter vector: ");
    x=0;
    total=(size) * (size-1)/2;
    while(x<size)
    {
        scanf("%d", &array[x]);

        x++;
    }
    printf("Enter permutation: ");
    int array1[size];
    x = 0;
    while (x < size)
    {
       scanf("%d", &array1[x]);
        x++;
    }

    x = 0;
    while (x<size)
    {
        y = y + array1[x];
        x++;
    }
    x = 0;
    if (y == total )
    {
        while (x<size)
        {
             printf("%d ", array[ array1[x] ]);
             x++;
        }
    }
    else {
        printf("Invalid permutation");
    }
printf("\n");

    return 0;
}
