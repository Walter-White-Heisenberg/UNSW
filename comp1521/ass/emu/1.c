#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

   int
   main(void)
   {
       char *a[] = {"a", "b", "c", "d"}; 
       for(int i = 0;i < 10;i++){
            char *buf = malloc(1000);
            fgets(buf,1000,stdin);
            a[i] = buf;
            for(int j = 0; j <= i; j++){
                printf("a[%d] %s",j,a[j]);
            }
       }
   }
   
