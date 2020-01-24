#include<stdio.h>
int main(void)
{
int x;
int y;
printf("Enter the total number of marks in the exam: ");
scanf("%d",&x);
printf("Enter the number of marks the student was awarded: ");
scanf("%d",&y);
if (y*100/x==66){printf("The student scored %d%% in this exam.\n",y*100/x+1);}
else if (y*100>x){printf("The student scored %d%% in this exam.\n",y*100/x);}
else if(y==0){printf("The student scored %d%% in this exam.\n",y*100/x);}
else {printf("The student scored %d%% in this exam.\n",y*100/x+1);}
return 0;
}
