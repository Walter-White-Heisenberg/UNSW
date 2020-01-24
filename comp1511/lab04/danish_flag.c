#include<stdio.h>
int main(void)
{
    int n;
    int i=0;
    printf("Enter the flag size: ");
    scanf("%d",&n);
    while(i<2*n-1)
    {
    i++;
    int x=0;
          while( x<9*n )
          {x++;
          if( x==3*n+1 || x==3*n ){printf(" ");}
          else{printf("#");}
          }
    printf("\n");
    }
    printf("\n\n");
    int m=0;
    while(m<2*n-1)
    {
    m++;
    int x=0;
          while( x<9*n )
          {x++;
          if( x==3*n || x==3*n+1 ){printf(" ");}
          else{printf("#");}
          }
    printf("\n");
    }
    return 0;
}
