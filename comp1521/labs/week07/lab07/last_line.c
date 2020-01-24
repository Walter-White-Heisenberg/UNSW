#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include <unistd.h>
int main(int argc,char **argv){
    if(argc == 2){
        FILE *file = fopen(argv[1],"r");
        int x = fgetc(file);
        int y = fgetc(file);
        if(x != EOF && y == EOF){
            printf("%c",x);
            return 0;
        }
        fseek(file, -1, SEEK_END);
        x = fgetc(file);
        int i = 0;  
        while(x != EOF){
            i = fseek(file, -2, SEEK_CUR);          
            x = fgetc(file);
            if(x == '\n' || i < 0) break;
        }
        if(i == -1) fseek(file, 0, SEEK_SET); 
        x = fgetc(file);    
        while(x != EOF){
            printf("%c",x);
            x = fgetc(file);
        }
        fclose(file);
    }
}

