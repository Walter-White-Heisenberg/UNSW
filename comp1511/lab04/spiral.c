#include<stdio.h>
int main(void)
{   int r;
    int f=1;
    int y;
    printf("Enter size: ");
    scanf("%d",&r);
    y=(r+1)/2-1;
    while(f<(r+1)/2+1)
    {int a=0;
        if(f % 2==1){while(a<r){a++;
            if((a % 2 == 0)&&(a<f-1||a>r-f)){printf("-");
            }
        else{printf("*");}
        }
        }else{
        while(a<r){a++;
            if((a % 2 == 1)&&(a<f-1||a>r-f)){printf("*");
            }
        else{printf("-");}}
   }printf("\n");
   f++;
   }
             
    while(y>0){int x=0;
     
       if(y % 2 == 1)
            {while(x<r)
                {
                x++;
                if((x % 2 == 0)&&(x < y+1 || x >r-y )){printf("-");}
                else{printf("*");}
                }
            printf("\n");}
       else{while(x<r)
                {
                x++;
                if((x % 2 == 0)||(x >= y+1 && x <=r-y )){printf("-");}
                else{printf("*");}
                } 
      
       printf("\n");} 
       y--;
    }
    
    return 0;
}
