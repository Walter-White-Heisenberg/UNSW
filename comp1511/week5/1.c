#include<stdio.h> 
int main(void)
{
int character;
printf("Please enter a character: ");
character = getchar();
printf("character %c has the ASSCII value %d.\n",character,character);
putchar(character);
int readchar;
readchar=getchar();
while(readchar != EOF)
{
    printf("The character %c has the ASCII code%d.\n",readchar,readchar);
    readchar=getchar();
}
return 0;
}
