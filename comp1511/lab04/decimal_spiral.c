#include<stdio.h>
int main(void)
{   int r;
    int f=1;
    int y;
    int q;
    int total;
    
    printf("Enter size: ");
    scanf("%d",&r);
    y=(r+1)/2-1;
    
    total=(r+1)*(r+1)/2;
    first=total % 10 
    while(f<(r+1)/2+1)
    {int a=0;
    
        if(f % 2==1){while(a<r){a++;
        q=(total-a-f) % 10;
            if((a % 2 == 0)&&(a<f-1||a>r-f)){printf("-");
            }
        else{if(a>f-1||a<r-f){printf("%d",q-first*4+2-);}}
        }
        }else{
        while(a<r){a++;
        q=(total-a-f) % 10;
            if((a % 2 == 1)&&(a<f-1||a>r-f)){printf("%d",q);
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
                q=(total+2-(r+1)/2+x+y) % 10;
                if((x % 2 == 0)&&(x < y+1 || x >r-y )){printf("-");}
                else{printf("%d",q);}
                }
            printf("\n");}
       else{while(x<r)
                {
                x++;
                q=(total+2-(r+1)/2+x+y) % 10;
                if((x % 2 == 0)||(x >= y+1 && x <=r-y )){printf("-");}
                else{printf("%d",q);}
                } 
      
       printf("\n");} 
       y--;
    }
    
    return 0;
}
