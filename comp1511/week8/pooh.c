#include<stdio.h>
int main(void){
//pointer is a variable which representing memory address
    int a,b,c,x,y,z;//we can have an address as soon as we create them, doesn't matter they have value or not
    printf("x: %p y: %p\n",&x,&y);
    x = 2002;
    y = 1001;
    //with pointer, you can do things with variable without touching themselves
    int *adx;
    adx = &x;//now you naming the pointer in line 4 pointing at x
    int *ady;
    ady = &y;//same as above
    printf("x: %p %p %d\n",adx,&x,x);
    printf("y: %p %p %d\n",ady,&y,y);
    int *ada = &x;
    int m; 
    m = *ady;
    *ady = *adx;
    *adx = m;
    printf("x: %p %p %d\n",adx,&x,x);
    printf("y: %p %p %d\n",ady,&y,y);           
    printf("%p %d\n",ada,*ada);//*ada means the value pointer ada pointing at, when the variable pointer pointing doen't have a value, it will point at a random value
}
