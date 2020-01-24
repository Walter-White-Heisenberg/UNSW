#include<stdio.h>
#include<math.h>
int main(void)
{
    int x;
    int size;
    int y=0;
    
    printf("Enter vector length: ");
    scanf("%d",&size);

    int arraya[size];
    int arraya1[size];
    int arraya2[size];
    int arrayb[size];
    int arrayb1[size];
    int arrayb2[size];
    printf("Enter vector1: ");
    x=0;

    while(x<size)
    {
        scanf("%d", &arraya[x]);
        x++;

    }
    printf("Enter vector2: ");
    x=0;

    while(x<size)
    {
        scanf("%d", &arrayb[x]);
        x++;
    }
    x=0;
    int i;
    int n;
    while(x<size){
        n=0;
        i=0;
        while(i<size){
        if(arraya[i]<arraya[x])
            {
            n++;
            }
        i++;
        }       
    arraya1[x]=n;
    arraya2[n]=arraya[x];
    x++;
    }
    x=0;
    while(x<size){
        n=0;
        i=0;
        while(i<size){
        if(arrayb[i]<arrayb[x])
            {
            n++;
            }
        i++;
        }       
    arrayb1[x]=n;//input order from small to big output no.x
    arrayb2[n]=x;//input order from small to big output no.x
    x++;
    }
    printf("Optimal permutation: ");
    x=0;
    while(x<size){
        y=0;
        while(y<size){
            if(arrayb1[x]==arraya1[y]){
                printf("%d ",y);
            }
            y++;
        }
        x++;
    }
    printf("\n");
    double t=0;
    x=0;
    while(x<size)
    {
    t=(arraya2[x]-arrayb[arrayb2[x]])*(arraya2[x]-arrayb[arrayb2[x]])+t;
    x++;
    }
    printf("Euclidean distance = %lf",sqrt(t));
    printf("\n");

    return 0;
}
