// A program thta shows me all the possible rolls of a pair of dice
//compare them against a target number 
//it will display the odds of rolling that target number
#include<stdio.h>

int main(void)
{
int a,b,target;
int roll=0;
double coroll=0;
// take user input for th edice sizes;
printf("Please enter the sizse of the first die: ");
scanf("%d",&a);
printf("Please enter the sizse of the second die: ");
scanf("%d",&b);
printf("Please enter the sizse of the target value: ");
scanf("%d",&target); 
    int acounter = 1;
    while( acounter <= a ){
    int bcounter = 1;
    while(bcounter <= b ){roll++;
        if (acounter+bcounter==target)
            {coroll++;
            printf("Die one: %d, Die two : %d, Total: %d\n",acounter,bcounter,acounter+bcounter);}
        bcounter=bcounter+1;
        }
    acounter=acounter+1;
    }
    printf("We rolled %d times and got our raget numbe %lf time.\nPercentage chance of rolliing is %lf.\n",roll,coroll,coroll/roll*100);
return 0;
}
