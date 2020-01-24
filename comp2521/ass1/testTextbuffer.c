// testTextbuffer.c
// A stub file for you to test your textbuffer implementation.
// Note that you will NOT be submitting this - this is simply for you to
// test  your  functions as you go. We will have our own testTexbuffer.c
// for testing your submission.

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "textbuffer.h"

static void testNewTB(void);

static void test1(void) {
	printf("-----------------------------------------\n"
	       "                1                        \n"
	       "-----------------------------------------\n");
	
	TB tb1 = newTB("hello there,\nhow\nare\nthings\n");
	assert(linesTB(tb1) == 4);
	char *text1 = dumpTB(tb1, 0); // Don't show line numbers
	assert(strcmp("hello there,\nhow\nare\nthings\n", text1) == 0);
	free(text1);
	releaseTB(tb1);
	
	
	
	printf("newTB tests passed!\n");
}
static void test2(void){
    printf("-----------------------------------------\n"
	       "                2                        \n"
	       "-----------------------------------------\n");
    TB tb1 = newTB("");
    for(textnode *n = tb1->first; n != NULL; n = n->next){
        printf("***%s\n",n->text);
    }
    char *x = dumpTB(tb1,0);
    assert(strcmp(x,"") == 0);
    assert(linesTB(tb1) == 0);
    free(x);
    releaseTB(tb1);
	printf("newTB tests passed!\n");
}

static void test3(void){
    printf("-----------------------------------------\n"
	       "                3                        \n"
	       "-----------------------------------------\n");
    TB tb1 = newTB("\n\n\n\n\nhello there,\nhow\nare\nthings\n");
	assert(linesTB(tb1) == 9);
	char *text1 = dumpTB(tb1, 0); // Don't show line numbers
	assert(strcmp("\n\n\n\n\nhello there,\nhow\nare\nthings\n", text1) == 0);
	free(text1);
	releaseTB(tb1);
	printf("newTB tests passed!\n");
}
static void test4(void){
    printf("-----------------------------------------\n"
	       "                4                        \n"
	       "-----------------------------------------\n");
    TB tb1 = newTB("hello world\namazing\n");
	assert(linesTB(tb1) == 2);
	char *text1 = dumpTB(tb1, 1); // Don't show line numbers
	assert(strcmp("1. hello world\n2. amazing\n", text1) == 0);
	free(text1);
	releaseTB(tb1);
	printf("newTB tests passed!\n");
}

static void test5(void){
    printf("-----------------------------------------\n"
	       "                5                        \n"
	       "-----------------------------------------\n");
    TB tb1 = newTB("\nhello world\namazing\n\n\n");
	assert(linesTB(tb1) == 5);
	char *text1 = dumpTB(tb1, 1); // Don't show line numbers
	assert(strcmp("1. \n2. hello world\n3. amazing\n4. \n5. \n", text1) == 0);
	free(text1);
	releaseTB(tb1);
	printf("newTB and dumpTB tests passed!\n");
}
static void test6(void){
    printf("-----------------------------------------\n"
	       "                6                        \n"
	       "-----------------------------------------\n");
    TB tb1 = newTB("\n\n\n\n\n\n\n\n\n\n");
    assert(linesTB(tb1) == 10);
    char *text1 = dumpTB(tb1, 1);
    assert(strcmp(text1,"1. \n2. \n3. \n4. \n5. \n6. \n7. \n8. \n9. \n10. \n") == 0);
    free(text1);
    text1 = dumpTB(tb1, 0);
    assert(strcmp(text1,"\n\n\n\n\n\n\n\n\n\n") == 0);
    free(text1);
    for(textnode *n = tb1->first; n != NULL; n = n->next)
        printf("%s\n",n->text);
    printf("lalalalalala\n");
    addPrefixTB(tb1,1,1,"first time");
    for(textnode *n = tb1->first; n != NULL; n = n->next)
        printf("%s\n",n->text);
    printf("lalalalalala\n");
    addPrefixTB(tb1,linesTB(tb1),linesTB(tb1),"second time");
    for(textnode *n = tb1->first; n != NULL; n = n->next)
        printf("%s\n",n->text);
    printf("lalalalalala\n");
    addPrefixTB(tb1,1,linesTB(tb1),"third time");
    for(textnode *n = tb1->first; n != NULL; n = n->next)
        printf("%s\n",n->text);
    printf("lalalalalala\n");
	releaseTB(tb1);
	printf("test for prefix passed?????????\n");
}

static void test7(void){
    printf("-----------------------------------------\n"
	       "                7                        \n"
	       "-----------------------------------------\n");
    TB tb1 = newTB("1. \n2. \n3. \n4. \n5. \n6. \n7. \n8. \n9. \n10. \n");
	assert(linesTB(tb1) == 10);
	for(textnode *n = tb1->first; n != NULL; n = n->next)
        printf("%s\n",n->text);
    printf("lalalalalala\n");
    for(textnode *n = tb1->last; n != NULL; n = n->prev)
        printf("%s\n",n->text);
    printf("lalalalalala\n");
	TB tb2 = newTB("**********\n())()()()()(())()()(\n");
	mergeTB(tb1,1,tb2);
	for(textnode *n = tb1->first; n != NULL; n = n->next){
        printf("%s\n",n->text);
    }    
    printf("lalalalalala\n");
    for(textnode *n = tb1->last; n != NULL; n = n->prev){
        printf("%s\n",n->text);
    }
	char *text1 = dumpTB(tb1, 0);
	assert(strcmp("**********\n())()()()()(())()()(\n1. \n2. \n3. \n4. \n5. \n6. \n7. \n8. \n9. \n10. \n",text1) == 0);
	free(text1);
	assert(linesTB(tb1) == 12);
	tb2 = newTB("**********\n())()()()()(())()()(\n");
	mergeTB(tb1,12,tb2);
	for(textnode *n = tb1->first; n != NULL; n = n->next){
        printf("%s\n",n->text);
    }    
    printf("lalalalalala\n");
    for(textnode *n = tb1->last; n != NULL; n = n->prev){
        printf("%s\n",n->text);
    }
	assert(linesTB(tb1) == 14);
	text1 = dumpTB(tb1, 0);
	assert(strcmp("**********\n())()()()()(())()()(\n1. \n2. \n3. \n4. \n5. \n6. \n7. \n8. \n9. \n**********\n())()()()()(())()()(\n10. \n",text1) == 0);
	free(text1);
	tb2 = newTB("**********\n())()()()()(())()()(\n");
	mergeTB(tb1,15,tb2);
	for(textnode *n = tb1->first; n != NULL; n = n->next){
        printf("%s\n",n->text);
    }    
    printf("lalalalalala\n");
    for(textnode *n = tb1->last; n != NULL; n = n->prev){
        printf("%s\n",n->text);
    }
	assert(linesTB(tb1) == 16);
	text1 = dumpTB(tb1, 0);
	assert(strcmp("**********\n())()()()()(())()()(\n1. \n2. \n3. \n4. \n5. \n6. \n7. \n8. \n9. \n**********\n())()()()()(())()()(\n10. \n**********\n())()()()()(())()()(\n",text1) == 0);
	free(text1);
	for(textnode *n = tb1->last; n != NULL; n = n->prev)
        printf("%s\n",n->text);
    printf("lalalalalala\n");
    for(textnode *n = tb1->first; n != NULL; n = n->next)
        printf("%s\n",n->text);
    printf("lalalalalala\n");
	releaseTB(tb1);
	tb1 = newTB("1. \n2. \n3. \n4. \n5. \n6. \n7. \n8. \n9. \n10. \n");
	tb2 = create_TB();
	mergeTB(tb1,10,tb2);
	for(textnode *n = tb1->first; n != NULL; n = n->next){
        printf("%s\n",n->text);
    }    
    printf("lalalalalala\n");
    for(textnode *n = tb1->last; n != NULL; n = n->prev){
        printf("%s\n",n->text);
    }
	releaseTB(tb1);
	printf("mergeTB tests passed!\n");
}

static void test8(void){
    printf("-----------------------------------------\n"
	       "                8                        \n"
	       "-----------------------------------------\n");
    TB tb1 = newTB("1. \n2. \n3. \n4. \n5. \n6. \n7. \n8. \n9. \n10. \n");
	assert(linesTB(tb1) == 10);
	for(textnode *n = tb1->first; n != NULL; n = n->next)
        printf("%s\n",n->text);
    printf("lalalalalala\n");
    for(textnode *n = tb1->last; n != NULL; n = n->prev)
        printf("%s\n",n->text);
    printf("lalalalalala\n");
	TB tb2 = newTB("**********\n())()()()()(())()()(\n");
	pasteTB(tb1,1,tb2);
	for(textnode *n = tb1->first; n != NULL; n = n->next){
        printf("%s\n",n->text);
    }    
    printf("lalalalalala\n");
    for(textnode *n = tb1->last; n != NULL; n = n->prev){
        printf("%s\n",n->text);
    }
	char *text1 = dumpTB(tb1, 0);
	assert(strcmp("**********\n())()()()()(())()()(\n1. \n2. \n3. \n4. \n5. \n6. \n7. \n8. \n9. \n10. \n",text1) == 0);
	free(text1);
	assert(linesTB(tb1) == 12);
	pasteTB(tb1,12,tb2);
	for(textnode *n = tb1->first; n != NULL; n = n->next){
        printf("%s\n",n->text);
    }    
    printf("lalalalalala\n");
    for(textnode *n = tb1->last; n != NULL; n = n->prev){
        printf("%s\n",n->text);
    }
	assert(linesTB(tb1) == 14);
	text1 = dumpTB(tb1, 0);
	assert(strcmp("**********\n())()()()()(())()()(\n1. \n2. \n3. \n4. \n5. \n6. \n7. \n8. \n9. \n**********\n())()()()()(())()()(\n10. \n",text1) == 0);
	free(text1);
	pasteTB(tb1,15,tb2);
	for(textnode *n = tb1->first; n != NULL; n = n->next){
        printf("%s\n",n->text);
    }    
    printf("lalalalalala\n");
    for(textnode *n = tb1->last; n != NULL; n = n->prev){
        printf("%s\n",n->text);
    }
	assert(linesTB(tb1) == 16);
	text1 = dumpTB(tb1, 0);
	assert(strcmp("**********\n())()()()()(())()()(\n1. \n2. \n3. \n4. \n5. \n6. \n7. \n8. \n9. \n**********\n())()()()()(())()()(\n10. \n**********\n())()()()()(())()()(\n",text1) == 0);
	free(text1);
	for(textnode *n = tb1->last; n != NULL; n = n->prev)
        printf("%s\n",n->text);
    printf("lalalalalala\n");
    for(textnode *n = tb1->first; n != NULL; n = n->next)
        printf("%s\n",n->text);
    printf("lalalalalala\n");
	releaseTB(tb1);
	releaseTB(tb2);
	tb1 = newTB("1. \n2. \n3. \n4. \n5. \n6. \n7. \n8. \n9. \n10. \n");
	tb2 = create_TB();
	pasteTB(tb1,10,tb2);
	for(textnode *n = tb1->first; n != NULL; n = n->next){
        printf("%s\n",n->text);
    }    
    printf("lalalalalala\n");
    for(textnode *n = tb1->last; n != NULL; n = n->prev){
        printf("%s\n",n->text);
    }
	releaseTB(tb1);
	releaseTB(tb2);
	printf("pasteTB tests passed!\n");
}

static void test9(){
    printf("-----------------------------------------\n"
	       "                9                        \n"
	       "-----------------------------------------\n");
    TB tb1 = newTB("1. \n2. \n3. \n4. \n5. \n6. \n7. \n8. \n9. \n10. \n");
    TB tb2 = cutTB(tb1,5,9);
    for(textnode *n = tb1->first; n != NULL; n = n->next){
        printf("%s\n",n->text);
    }    
    for(textnode *n = tb1->last; n != NULL; n = n->prev){
        printf("%s\n",n->text);
    }
    for(textnode *n = tb2->first; n != NULL; n = n->next){
        printf("%s\n",n->text);
    }    
    for(textnode *n = tb2->last; n != NULL; n = n->prev){
        printf("%s\n",n->text);
    }
        printf("lalalalalala\n");
    releaseTB(tb1);
    releaseTB(tb2);
    tb1 = newTB("1. \n2. \n3. \n4. \n5. \n6. \n7. \n8. \n9. \n10. \n");
    tb2 = cutTB(tb1,5,10);
    for(textnode *n = tb1->first; n != NULL; n = n->next){
        printf("%s\n",n->text);
    }    
    for(textnode *n = tb1->last; n != NULL; n = n->prev){
        printf("%s\n",n->text);
    }
    for(textnode *n = tb2->first; n != NULL; n = n->next){
        printf("%s\n",n->text);
    }    
    for(textnode *n = tb2->last; n != NULL; n = n->prev){
        printf("%s\n",n->text);
    }
        printf("lalalalalala\n");
    releaseTB(tb1);
    releaseTB(tb2);
    tb1 = newTB("1. \n2. \n3. \n4. \n5. \n6. \n7. \n8. \n9. \n10. \n");
    tb2 = cutTB(tb1,1,9);
    for(textnode *n = tb1->first; n != NULL; n = n->next){
        printf("%s\n",n->text);
    }    

    for(textnode *n = tb1->last; n != NULL; n = n->prev){
        printf("%s\n",n->text);
    }
    for(textnode *n = tb2->first; n != NULL; n = n->next){
        printf("%s\n",n->text);
    }    
    for(textnode *n = tb2->last; n != NULL; n = n->prev){
        printf("%s\n",n->text);
    }
    printf("lalalalalala\n");
    releaseTB(tb1);
    releaseTB(tb2);
    tb1 = newTB("1. \n2. \n3. \n4. \n5. \n6. \n7. \n8. \n9. \n10. \n");
    tb2 = cutTB(tb1,1,10);
    for(textnode *n = tb1->first; n != NULL; n = n->next){
        printf("%s\n",n->text);
    }    

    for(textnode *n = tb1->last; n != NULL; n = n->prev){
        printf("%s\n",n->text);
    }
    for(textnode *n = tb2->first; n != NULL; n = n->next){
        printf("%s\n",n->text);
    }    
    for(textnode *n = tb2->last; n != NULL; n = n->prev){
        printf("%s\n",n->text);
    }
    printf("lalalalalala\n");
    releaseTB(tb1);
    releaseTB(tb2);
    tb1 = newTB("1. \n2. \n3. \n4. \n5. \n6. \n7. \n8. \n9. \n10. \n");
    tb2 = cutTB(tb1,5,5);
    for(textnode *n = tb1->first; n != NULL; n = n->next){
        printf("%s\n",n->text);
    }    

    for(textnode *n = tb1->last; n != NULL; n = n->prev){
        printf("%s\n",n->text);
    }
    for(textnode *n = tb2->first; n != NULL; n = n->next){
        printf("%s\n",n->text);
    }    
    for(textnode *n = tb2->last; n != NULL; n = n->prev){
        printf("%s\n",n->text);
    }
    printf("lalalalalala\n");
    releaseTB(tb1);
    releaseTB(tb2);
    printf("cutTB tests passed!\n");
}

static void test10(){
    printf("-----------------------------------------\n"
	       "                10                       \n"
	       "-----------------------------------------\n");
    TB tb1 = newTB("1. \n2. \n3. \n4. \n5. \n6. \n7. \n8. \n9. \n10. \n");
    deleteTB(tb1,5,9);
    for(textnode *n = tb1->first; n != NULL; n = n->next){
        printf("%s\n",n->text);
    }    
    for(textnode *n = tb1->last; n != NULL; n = n->prev){
        printf("%s\n",n->text);
    }
        printf("lalalalalala\n");
    releaseTB(tb1);
    tb1 = newTB("1. \n2. \n3. \n4. \n5. \n6. \n7. \n8. \n9. \n10. \n");
    deleteTB(tb1,5,10);
    for(textnode *n = tb1->first; n != NULL; n = n->next){
        printf("%s\n",n->text);
    }    
    for(textnode *n = tb1->last; n != NULL; n = n->prev){
        printf("%s\n",n->text);
    }
        printf("lalalalalala\n");
    releaseTB(tb1);
    tb1 = newTB("1. \n2. \n3. \n4. \n5. \n6. \n7. \n8. \n9. \n10. \n");
    deleteTB(tb1,1,9);
    for(textnode *n = tb1->first; n != NULL; n = n->next){
        printf("%s\n",n->text);
    }    

    for(textnode *n = tb1->last; n != NULL; n = n->prev){
        printf("%s\n",n->text);
    }
    printf("lalalalalala\n");
    releaseTB(tb1);
    tb1 = newTB("1. \n2. \n3. \n4. \n5. \n6. \n7. \n8. \n9. \n10. \n");
    deleteTB(tb1,1,10);
    for(textnode *n = tb1->first; n != NULL; n = n->next){
        printf("%s\n",n->text);
    }    

    for(textnode *n = tb1->last; n != NULL; n = n->prev){
        printf("%s\n",n->text);
    }
    printf("lalalalalala\n");
    releaseTB(tb1);
    tb1 = newTB("1. \n2. \n3. \n4. \n5. \n6. \n7. \n8. \n9. \n10. \n");
    deleteTB(tb1,5,5);
    for(textnode *n = tb1->first; n != NULL; n = n->next){
        printf("%s\n",n->text);
    }    

    for(textnode *n = tb1->last; n != NULL; n = n->prev){
        printf("%s\n",n->text);
    }
    printf("lalalalalala\n");
    releaseTB(tb1);
    printf("deleteTB tests passed!\n");
}
static void test11(){
    printf("-----------------------------------------\n"
	       "                11                       \n"
	       "-----------------------------------------\n");
    TB tb1 = newTB("1. . . . . . .  .\n2. \n3. \n4. \n5. \n6. \n7. \n8. \n9. \n10. \n11\n");
    Match n = searchTB(tb1,".");
    Match m = n;
    while(n != NULL){
        printf("%d %d\n",n->lineNumber,n->charIndex);
        n = n->next;
    }
    free_match(m);
    releaseTB(tb1);
}  
static void test12(){
     printf("-----------------------------------------\n"
	        "                12                       \n"
	        "-----------------------------------------\n");
	 TB tb1 = newTB("*some* _string_*some* _string_*some* _string_\n");
	 formRichText(tb1);
	 char *x = dumpTB(tb1,0);
	 printf("%s\n",tb1->first->text);
	 free(x);
	 releaseTB(tb1);      
}
static void test13(){
    printf("-----------------------------------------\n"
	       "                13                       \n"
	       "-----------------------------------------\n");
    TB tb1 = newTB("asdffsdffsdf\naaassd\ndf\nasdf\nsdfsdf\nsdfsdfsdf\n7. \n8. \n9. \n10. \n11\n");
    Match n = searchTB(tb1,"sdf");
    Match m = n;
    while(n != NULL){
        printf("%d %d\n",n->lineNumber,n->charIndex);
        n = n->next;
    }
    free_match(m);
    releaseTB(tb1);
} 

static void test14(){
    printf("-----------------------------------------\n"
	       "                14                       \n"
	       "-----------------------------------------\n");
	TB tb1 = newTB("1. \n2. \n3. \n4. \n5. \n6. \n7. \n8. \n9. \n10. \n11\n");
	TB tb2 = newTB("1. \n2. \n3. \n4. \n5. \n6. \n");     
	char *x = diffTB(tb1, tb2); 
	printf("%s",x);
	free(x);
	releaseTB(tb1);
	releaseTB(tb2);       
}  
int main(void){
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    test7();
    test8();
    test9();
    test10();
    test11();
    test12();
    test13();
    test14();
}


