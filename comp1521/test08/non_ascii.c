#include<stdio.h>
#include<stdlib.h>
int main(int argc, char ** argv){
    if(argc == 2){
        FILE *file = fopen(argv[1],"r");
        int c = fgetc(file),i = 0;
        while(c != EOF){
            if(c >= 128 && c <= 255){
                printf("%s: byte %d is non-ASCII\n",argv[1],i);
                fclose(file);
                return 0;
            }
            i++;
            c = fgetc(file);
        }
        printf("%s is all ASCII\n",argv[1]);
        fclose(file);
    }
}
