#include <stdio.h>
int main(void)
{
int num;
scanf("%d", &num);
if( num > 0 ){printf("You have entered a positive number.\n");}
else if (num == 0){printf("You have entered zero.\n");}
else {printf("Don't be so negative!\n");}
return 0;
}
