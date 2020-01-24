#include <stdio.h>
int main(void)
{
int dieone;
int dietwo;
printf("please enter the result of the first die: ");
scanf("%d", &dieone);
//check input against correct value
if (1 <=dieone && dieone <6)
//the corresct input
{}
else
//the wrong value
{printf("incorrect input");
return 1;}
return 0;
}
