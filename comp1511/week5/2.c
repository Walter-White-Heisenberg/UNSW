#include<stdio.h>
#define Max 80
int main(void)
{
    char line[Max];
    while(fgets(line,Max,stdin)!= NULL){
    fputs(line, stdout);
    }

    return 0;
}
