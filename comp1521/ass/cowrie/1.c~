#include <unistd.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>

int main(void){
    while (1) {
        char pathname[1998];
        if (getcwd(pathname, sizeof pathname) == NULL) {
            perror("getcwd");
            break;
        }
        printf("getcwd() returned %s\n", pathname);

        if (strcmp(pathname, "/") == 0) break;

        if (chdir("..") != 0) {
            perror("chdir");
            break;
        }
    }
}
