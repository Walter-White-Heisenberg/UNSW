#include<stdio.h>
int main(void)
{
int x,y,z;
printf("Enter integer: ");
scanf("%d",&x);
printf("Enter integer: ");
scanf("%d",&y);
printf("Enter integer: ");
scanf("%d",&z);
printf("The integers in order are: %d %d %d\n",
((y/x)*(z/x)*x+(z/y)*(x/y)*y+(x/z)*(y/z)*z)/((y/z)*(x/z)+(z/x)*(y/x)+(x/y)*(z/y)),x+y+z-((y/x)*(z/x)*x+(z/y)*(x/y)*y+(x/z)*(y/z)*z)/((y/z)*(x/z)+(z/x)*(y/x)+(x/y)*(z/y))-((x/y)*(x/z)*x+(y/z)*(y/x)*y+(z/x)*(z/y)*z)/((z/y)*(z/x)+(x/z)*(x/y)+(y/z)*(y/x)),((x/y)*(x/z)*x+(y/z)*(y/x)*y+(z/x)*(z/y)*z)/((z/y)*(z/x)+(x/z)*(x/y)+(y/z)*(y/x)));
//smallest=((x/y)*(x/z)*x+(y/z)*(y/x)*y+(z/x)*(z/y)*z)/((z/y)*(z/x)+(x/z)*(x/y)+(y/z)*(y/x))//x*y*z//largest=((y/x)*(z/x)*x+(z/y)*(x/y)*y+(x/z)*(y/z)*z)/((y/z)*(x/z)+(z/x)*(y/x)+(x/y)*(z/y))//x*y*z/(((x/y)*(x/z)*x+(y/z)*(y/x)*y+(z/x)*(z/y)*z)/((z/y)*(z/x)+(x/z)*(x/y)+(y/z)*(y/x)))*(((y/x)*(z/x)*x+(z/y)*(x/y)*y+(x/z)*(y/z)*z)/((y/z)*(x/z)+(z/x)*(y/x)+(x/y)*(z/y)))
return 0;
}

