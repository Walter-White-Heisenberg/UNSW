#include<stdio.h>
#include <stdlib.h>
#include<string.h>
int main(int argc, char **argv){
    if(argc == 1) printf("0\n");
    else {
        char *x = getenv(argv[1]);
        if (x == NULL || strlen(x) == 0) printf("0\n");
        else printf("1\n");
    }
}
