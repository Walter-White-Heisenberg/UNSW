#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include<pwd.h>
void print_mode(char *file){
    struct stat info;
    if(stat(file,&info) != 0)
        exit(1);
    char final[11] = {0};         
    char *str = "-xw-r", *str2 = "-ic-d-b---r-l";
    for(int j = 0; j < 3; j++){
        for(int i = 0; i < 3; i++)
            final[9 - (i + 3 * j)] = str[(info.st_mode & (1 << i))];
        info.st_mode = info.st_mode >> 3;
    }
    final[0] = str2[info.st_mode >> 3];
    printf("%s %s\n",final,file);
}
int main(int argc, char **argv){
    if(argc > 1){
        for(int m = 1;m < argc;m++)
            print_mode(argv[m]);
    }
}

























/*
S_IFLNK 1010000000000000 12 symbolic link
S_IFREG 1000000000000000 10 regular file
S_IFBLK 0110000000000000 6 block device
S_IFDIR 0100000000000000 4 directory
S_IFCHR 0010000000000000 2 character device
S_IFIFO 0001000000000000 1 FIFO
S_IRUSR 0000000100000000 owner has read permission
S_IWUSR 0000000010000000 owner has write permission
S_IXUSR 0000000001000000 owner has execute permission
S_IRGRP 0000000000100000 group has read permission
S_IWGRP 0000000000010000 group has write permission
S_IXGRP 0000000000001000 group has execute permission
S_IROTH 0000000000000100 others have read permission
S_IWOTH 0000000000000010 others have write permission
S_IXOTH 0000000000000001 others have execute permission
*/
