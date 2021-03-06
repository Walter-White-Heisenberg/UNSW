#include<stdio.h>
#include<stdlib.h>
int main(int argc, char ** argv){
    if(argc == 3){
        FILE *file1 = fopen(argv[1],"r");
        FILE *file2 = fopen(argv[2],"r");
        int c1 = fgetc(file1),c2 = fgetc(file2);
        int m = 0, i = 0;
        while(m != 3){
            m += (c1 == EOF)*(m != 1 && m != 3) + (m != 2 && m != 3)*(c2 == EOF)*2;
            if(m > 0 && m != 3){
                printf("EOF on %s\n",argv[m]);
                fclose(file1);
                fclose(file2);
                return 0;
            }
            if(c1 != c2){
                printf("Files differ at byte %d\n",i);
                fclose(file1);
                fclose(file2);
                return 0;
            }            
            if(m != 1 && m != 3) c1 = fgetc(file1);
            if(m != 2 && m != 3) c2 = fgetc(file2);
            i++;	
        }
        fclose(file1);
        fclose(file2);
        printf("Files are identical\n");
    }
}
