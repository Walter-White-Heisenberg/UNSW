#include <stdio.h>
#include <stdlib.h>
int main(void){
    FILE *file = fopen("11","r");
    int c = fgetc(file), i = 1, j = 2, total = 1;
    char **product = NULL;
    char *tmp = NULL;
    while (c != EOF) {
        if(c != '\n') {
            tmp = realloc(tmp, j);
            tmp[j-2] = c;
            j++;
        } else {
            tmp = realloc(tmp, j);
            
            tmp[j-2] = 0;
            product = realloc(product, i * sizeof(char *));
            product[i-1] = tmp;
            j = 2;
            tmp = NULL;
            i++;
        }
        total++;
        c = fgetc(file); 
    }
    product = realloc(product, i * sizeof(char *));
    product[i-1] = NULL;
    printf("%d\n",i);
    for(i = 0; product[i] != NULL; i++)
        printf("%d %s\n",i,product[i]);  
    printf("%d\n",i);
}
