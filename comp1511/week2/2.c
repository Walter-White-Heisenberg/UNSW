#include <stdio.h>
int main(void)
{
int dieone;
int dietwo;
printf("please enter the result of the first die: ");
scanf("%d", &dieone);
//check input against correct value
if (dieone < 1)
{dieone=1;}
else if (dieone > 6)
{dieone = 6;}
printf("you rolled %d", dieone);
return 0;
}
