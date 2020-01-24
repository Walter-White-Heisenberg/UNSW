//the dice checker V2
//allow the user to set dice
//dice the die in two roll against a target number
//able o deal with the user reported rolls outside the range
//will report back to success
#include <stdio.h>
//target value of dice size
#define Target_value7

int main(void)
{
int diceSize;//number of size
int dieOne;//value of first die
int dieTwo;//value of second 
int total;//sum of both
printf("please enter how many sides are on your dice: ");
scanf("%d", &diceSize);
printf("please enter the value of the first die: ");
scanf("%d",&dieOne);
if(dieOne<1|| dieOne>diceSize){printf("die roll value: %d is outside of the range 1-%d.\n", dieOne, diceSize);
dieOne= dieOne % diceSize;
if (dieOne ==0)
{dieOne = diceSize;}
}
printf("your roll is: %d\n", dieTwo);
printf("please enter the value of the second die: ");
scanf("%d",&dieTwo);
if(dieTwo<1|| dieTwo >diceSize){printf("die roll value: %d is outside of the range 1-%d.\n", dieTwo, diceSize);
dieOne= dieOne % diceSize;
if (dieTwo ==0)
{dieTwo = diceSize;}
}
printf("your roll is: %d\n", dieTwo);

return 0;}
