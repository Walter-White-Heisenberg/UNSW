// COMP1521 19T3 ... lab 1
// cat4: Copy input to output

#include <stdio.h>
#include <stdlib.h>


static void copy(FILE *, FILE *);

int main(int argc, char **argv) {
    if (argc == 1) copy (stdin, stdout);
    else {
        FILE *f = fopen(argv[1],"r");
        if(f == NULL) printf("Can't read name-of-file\n");
        else {
            copy(f,stdout);
            fclose(f);
        }
    }
    return EXIT_SUCCESS;
}


// Copy contents of input to output, char-by-char
// Assumes both files open in appropriate mode
static void copy (FILE *input, FILE *output) {
    char x[BUFSIZ];
    while(fgets(x,BUFSIZ,input)){    
        fputs(x,output);
    }

}
