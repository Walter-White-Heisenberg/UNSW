// COMP1521 19T3 ... lab 1
// cat4: Copy input to output

#include <stdio.h>
#include <stdlib.h>


static void copy(FILE *, FILE *);

int main(int argc, char **argv) {
    if (argc == 1){
        copy(stdin,stdout);
    }
    else{
        for(int i = 1; i < argc; i++){
        FILE *x = fopen(argv[i],"r+"); 
            if(x == NULL){ 
                printf("Can't read name-of-file");
            }else{
                copy(x,stdout);
                fclose(x);
            }
        }
    }    
    return EXIT_SUCCESS;
}


// Copy contents of input to output, char-by-char
// Assumes both files open in appropriate mode
static void copy (FILE *input, FILE *output) {
    char x[BUFSIZ];
    while(fgets(x, BUFSIZ, input) != NULL){
        fputs(x,output);
    }
}
