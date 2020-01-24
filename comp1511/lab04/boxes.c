#include<stdio.h>
int main(void)
{
    int n;
    int y=1;
    printf("How many boxes: ");
    scanf("%d",&n);
    int r=4*n-1;
    if(n!=0){while(2*y<=r)
    {int x=0;
     
       if(y % 2 == 1)
            {while(x<=r)
                {
                x++;
                if((x % 2 == 0)&&(x < y+1 || x >r-y )){printf(" ");}
                else{printf("#");}
                }
            printf("\n");}
       else{while(x<=r)
                {
                x++;
                if((x % 2 ==0)(x >= y+1 && x <=r-y )){printf(" ");}
                else{printf("#");}
                } 
      
       printf("\n");} 
       y++;
    }
    
    
    
           
    while(y>0){int x=0;
     
       if(y % 2 == 1)
            {while(x<=r)
                {
                x++;
                if((x % 2 == 0)&&(x < y+1 || x >r-y )){printf(" ");}
                else{printf("#");}
                }
            printf("\n");}
       else{while(x<=r)
                {
                x++;
                if((x % 2 == 0)||(x >= y+1 && x <=r-y )){printf(" ");}
                else{printf("#");}
                } 
      
       printf("\n");} 
       y--;
    }
    }
    return 0;
}
