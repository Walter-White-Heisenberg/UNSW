#include<stdio.h>
int main(void)
{
    int a,i,m;
    i=0;
    a=0;
    int array[1001];
    while(scanf("%d",&array[i]) == 1){
        i++;       
    }        
    printf("Indivisible numbers: ");
    while(a < i){
        m=0;
        array[1000]=0;
        while(m<i){
            if (array[a] % array[m] == 0 && m != a)
            {
                array[1000]++;
            }
            m++;
        }
        if (array[1000]==0)
        {
        printf("%d ",array[a]);
        }       
        a++;       
    }
    printf("\n");
    return 0;
}
