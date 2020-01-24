#include<stdio.h>
#include <ctype.h>
int main(int argc, char **argv){
    if(argc > 1){
        FILE *file = fopen(argv[1],"r");
        int tmp[5] = {0};
        for(tmp[4] = fgetc(file);tmp[4] != EOF;tmp[4] = fgetc(file)){
            if (isprint(tmp[4]) != 0){
                if(tmp[4] != 0){
                    if(tmp[0] == 0) tmp[0] = tmp[4];
                    else if(tmp[1] == 0) tmp[1] = tmp[4];
                    else if(tmp[2] == 0) tmp[2] = tmp[4];
                    else if(tmp[3] == 0) tmp[3] = tmp[4];
                    else{
                        printf("%c",tmp[0]);
                        for(int i = 0; i < 4; i++)
                            tmp[i] = tmp[i+1];
                    }
                }
            }else{
                if(tmp[3] != 0) printf("%c%c%c%c\n",tmp[0],tmp[1],tmp[2],tmp[3]);
                tmp[0] = tmp[1] = tmp[2] = 0;
                tmp[3] = 0;
            }
        }
        if(tmp[3] != 0) printf("%c%c%c%c\n",tmp[0],tmp[1],tmp[2],tmp[3]);
        fclose(file);
    }   
}
