#include<stdio.h>
#include<stdlib.h>
int main(int argc, char **argv){
    if (argc < 4) return 0;
    FILE *myfile = fopen(argv[1], "w");
    if (myfile == NULL) {
        perror(argv[1]);
        return 1;
    }
    for(int i = atoi(argv[2]);i <= atoi(argv[3]);i++){
        fprintf(myfile, "%d\n", i);
    }
    fclose(myfile);
    return 0;
}
