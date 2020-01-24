#include<stdio.h>
#include <stdlib.h>
#include <sys/types.h>
       #include <sys/stat.h>
       #include <unistd.h>
#include<stdint.h>
void print_size(char *name, uint64_t *total){
    struct stat S;
    if(stat(name, &S) == -1) exit(1);
    *total+=S.st_size;
    printf("%s: %lu bytes\n",name,S.st_size);
}
int main(int argc, char ** argv){
    if (argc == 1) return 0;
    uint64_t total = 0;
    for(int i = 1; i < argc; i++)
        print_size(argv[i], &total);
    printf("Total: %lu bytes\n",total);
}
