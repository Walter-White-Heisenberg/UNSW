#include<stdio.h>
#include<stdlib.h>
int main(int argc,char **argv){
    if(argc >= 2){
        FILE *myfile = fopen(argv[1],"w");
        for(int i = 3; i <= argc; i++){
            fputc(atoi(argv[i-1]), myfile);
        }
        fclose(myfile);
    }
}
