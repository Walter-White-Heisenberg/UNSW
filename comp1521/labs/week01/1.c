#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

   int
   main(void)
   {    
       
       struct s {
           int a;
           double b;
           char c;
           int d;
           
       };
       

       /* Output is compiler dependent */

       printf("offsets: i=%ld; c=%ld; d=%ld a=%ld\n",
               (long) offsetof(struct s, a),
               (long) offsetof(struct s, b),
               (long) offsetof(struct s, c),
               (long) offsetof(struct s, d));
       printf("sizeof(struct s)=%ld\n", (long) sizeof(struct s));

       exit(EXIT_SUCCESS);
   }
