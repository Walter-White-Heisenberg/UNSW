#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include<stdint.h>
void print_size(char *file, uint64_t *total){
    struct stat info;
    if(stat(file,&info) != 0){
        perror(file);
        exit(1);
    }
    printf("%s: %lu bytes\n",file,info.st_size);
    *total += info.st_size;
}

int main(int argc, char **argv){
    if(argc > 1){
        uint64_t total = 0;
        for(int i = 1;i < argc;i++){
            print_size(argv[i], &total);
        }
        printf("Total: %lu bytes\n",total);
    }
}
