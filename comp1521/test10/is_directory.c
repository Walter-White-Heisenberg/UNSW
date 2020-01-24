#include<stdio.h>
#include <unistd.h>

int main(int argc, char **argv){
    if(argc == 1) printf("0\n");
    else {
        int x = chdir(argv[1]);
        if(x == -1) printf("0\n");
        else printf("1\n");
    }
}
