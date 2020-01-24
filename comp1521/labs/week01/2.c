#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#define ss 34343
int main(void) {
    FILE *file = fopen("1.c","r");
   printf("%d\n", file == NULL); 
}
