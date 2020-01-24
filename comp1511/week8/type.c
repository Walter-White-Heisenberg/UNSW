#include<stdio.h>
int main(void){
int i = 65;
char c = (char) i;
int *ip = (int *) i;
int nums[] = {64,65,66,67,68,69,'\0'};
printf("%c\n", (char) i);
printf("%s\n", (char *) &i);
printf("%d\n", nums);
}
