#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main(int argc, char **argv){
    if(argc > 1){
        char *E = getenv("HOME");
        strcat(E,"/.diary");
        FILE *file = fopen(E,"a");
        for(int i = 1; i < argc; i++){
            fputs(argv[i],file);
            if(i != argc - 1) fputc(' ',file);    
        }
        fputc('\n',file);
    }
}

