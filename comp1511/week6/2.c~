#include<stdio.h>
int main(void){
    int i = 42;
    
    printf("i = %d\n",i);
    printf("i is at %p\n", &i);
    //* means we are refrencing from a thing
    int *ip = &i;
    
    printf("ip=%p\n",ip);
    printf("the value at ip(%p) is %d\n",ip,*ip);
    
    int j = i;
    
    printf("j = %d\n",j);
    printf("j is at %p\n",&j);
    i = 54;
    printf("i=%d\n",i);
    printf("j=%d\n",j);
    printf("*ip = %d\n",*ip);
    
    *ip = 72;
    
    printf("i=%d\n",i);
    printf("j=%d\n",j);
    printf("*ip = %d\n",*ip);
    
    printf("\n");
    
    int array[12];
    
    double k=3.1415926;
    
    printf("i is %zu bytes\n", sizeof(i));
    printf("int is %zu bytes\n", sizeof(int));
    printf("ip is %zu bytes\n", sizeof(ip));
    printf("int * is %zu bytes\n", sizeof(int *));
    printf("double * is %zu bytes\n", sizeof(double *));
    printf("k is %zu bytes\n", sizeof(k));
    printf("float is %zu bytes\n", sizeof(float));
    printf("double is %zu bytes\n", sizeof(double));
    printf("array[] is %zu bytes\n", sizeof(array[]));
    return 0;
}
