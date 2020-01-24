/*linux command: ls -l
 ls -a (can show all) 
 ls -t (rearrange by modified time)
 cd move back to home directory
 cd .. move back to last one (parent one) 
 mkdir*/
#include<stdio.h>
int main(void){
    //int and double
    int x = 2147483647;//upper bound 2^32-1,why 32? depends on computer is 16 or 32
    int y = -2147483648;//lower bound same as above
    printf("overflow %d, underflow %d",x-y,y-x);
    double x1 = 3;
    double y1 = 3.1982691826734;
    printf("%d %d %f %f %lf %lf\n",x1,y1,x1,y1,x1,y1);
    return 0;
}
