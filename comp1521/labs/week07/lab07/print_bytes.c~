#include<stdio.h>
#include <ctype.h>
int main(int argc, char **argv) {
    if(argc > 0){
        FILE *myfile = fopen(argv[1], "r");
        int i = 0;
        for(int x = fgetc(myfile);x != EOF;x = fgetc(myfile)){
            printf("byte %4ld: %3d 0x%02x",(long int)i, x, x);
            if (isprint(x) != 0) printf(" '%c'",x);
            printf("\n");
            i++;
        }
        fclose(myfile);
    }
} 
