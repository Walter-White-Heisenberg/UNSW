#include<stdio.h>
#include<stdlib.h>
int main(void) {
int x, y, z;
printf("Please enter two integers: ");
scanf("%d %d",&x,&y);
z=x+y;
if (x<0 && -10 <x) printf("negative "); 
if (abs(x)==1 ){printf("one");}
else if (abs(x)==2){printf("two");}
else if (abs(x)==3){printf("three");}
else if (abs(x)==4){printf("four");}
else if (abs(x)==5){printf("five");}
else if (abs(x)==6){printf("six");}
else if (abs(x)==7){printf("seven");}
else if (abs(x)==8){printf("eight");}
else if (abs(x)==9){printf("nine");}
else if (abs(x)==10){printf("ten");}
else if (abs(x)==0){printf("zero");}
else {printf("%d",x);}
printf(" + ");
if (y<0 && -10 <y) printf("negative "); 
if (abs(y)==1){printf("one");}
else if (abs(y)==2){printf("two");}
else if (abs(y)==3){printf("three");}
else if (abs(y)==4){printf("four");}
else if (abs(y)==5){printf("five");}
else if (abs(y)==6){printf("six");}
else if (abs(y)==7){printf("seven");}
else if (abs(y)==8){printf("eight");}
else if (abs(y)==9){printf("nine");}
else if (abs(y)==10){printf("ten");}
else if (abs(y)==0){printf("zero");}
else {printf("%d",y);}
printf(" = ");
if (z<0 && -10 <z) printf("negative "); 
if (abs(z)==1){printf("one\n");}
else if (abs(z)==2){printf("two\n");}
else if (abs(z)==3){printf("three\n");}
else if (abs(z)==4){printf("four\n");}
else if (abs(z)==5){printf("five\n");}
else if (abs(z)==6){printf("six\n");}
else if (abs(z)==7){printf("seven\n");}
else if (abs(z)==8){printf("eight\n");}
else if (abs(z)==9){printf("nine\n");}
else if (abs(z)==10){printf("ten\n");}
else if (abs(z)==0){printf("zero\n");}
else {printf("%d\n",x+y);}
return 0;}
