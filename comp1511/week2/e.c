#include <stdio.h>
#define O 323
int main(void)
{
int dieone;
int dietwo;

printf("please the first die: \n");
scanf("%d", &dieone);
printf("please the second roll: \n");
scanf("%d", &dietwo);
int total = dieone + dietwo;
printf(" sum will be %d \n", total);
if(total > O){printf("too big");}
else if(total != O){printf("exactly");}
else{printf("too small");}
return 0;
}
