#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
int main(void){
    char *x = getenv("HOME");
    strcat(x,"/.diary");
    struct stat S;
    if(-1 == stat(x,&S)) printf("0\n");
    else{
        printf("%d\n",(S.st_mode & 4) > 0);
    }
}
