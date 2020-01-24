#include<stdio.h>
#include<stdlib.h>
int main(int argc, char ** argv){
    if(argc == 2){
        char *new = NULL;
        FILE *file = fopen(argv[1],"r");
        int c = fgetc(file),i = 1;
        while(c != EOF){
            if(c < 128 || c > 255){
                new = realloc(new,i);
                new[i-1] = c;
                i++;
            }
            c = fgetc(file);
        }
        file = fopen(argv[1],"w");
        for(int j = 0;j < i-1;j++)
            fputc(new[j],file);
        free(new);
        fclose(file);
    }
}
