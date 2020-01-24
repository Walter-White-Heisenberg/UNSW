#include <stdio.h>
       #include <ctype.h>
int main(int argc, char ** argv){
    if(argc == 2){
        FILE *file = fopen(argv[1], "r");
        int c = fgetc(file), i = 0;
        while(c != EOF){
            if (isprint(c)) printf("byte %4d: %3d 0x%02x '%c'\n", i, c, c, c);
            else printf("byte %4d: %3d 0x%02x\n", i, c, c);
            c = fgetc(file);
            i++;
        }
    }
}
