#include <stdio.h>


int main(void) {
    int c,x,y,z;//we can have an address as soon as we create them, doesn't matter they have value or not
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
    //&m = &y; this is not available, which means it's impossible to have two variable have same address, but it's possible to have two address ssaving same adderess.
    m = *ady;
    *ady = *adx;
    *adx = m;
    printf("x: %p %p %d\n",adx,&x,x);
    printf("y: %p %p %d\n",ady,&y,y);           
    printf("%p %d\n",ada,*ada);
    //*ada means the value pointer ada pointing at, when the variable pointer pointing doen't have a value, it will point at a random value
    int nums[7] = {5,6,7,8,9,10,11};

    int *n = &nums[3];
    printf("n[0]=%d n[1]=%d n[2]=%d \n", n[0], n[1], n[2]);

    char string[12] = "Hello World";
    char *s = &string[6];
    printf("string = %s\n", string);
    printf("s = %s\n", s);
    printf("&string[9] = %s\n", &string[9]);
    char *l = &string[6];
    //char **w = &s;
    //*w[0] = s;
    //*w[1] = l;
    s = &string[0];
    s[5] = '\0';     // equivalent to string[5] = '\0'
    printf("string = %s\n", string);
    printf("s = %s\n", s);
    //printf("%s\n", w);
    char **a = 1;
    int *b; 
    printf("%p %p %p %p\n", a,a+1,a+2,a+3);
    printf("%p %p %p %p\n", b,b+1,b+2,b+3);
    printf("nums = %d \n", nums);
    return 0;
}
