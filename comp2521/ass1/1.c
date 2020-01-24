#include<assert.h>
#include <stdlib.h>
#include "textbuffer.h"
#include<string.h>
#include<stdio.h>
struct textbuffer{
      struct textbuffer *close;
      struct textbuffer *far;
      struct textnode* first;
      struct textnode* last;
      int n_line;
      int number;
};

typedef struct textnode{
      char *text;
      struct textnode* next;
      struct textnode* prev;
}textnode;

static TB create_TB(void){
    TB newTB = malloc(sizeof(struct textbuffer));
    if (newTB == NULL){
        printf("malloc fail");
        exit(1);
    }
	newTB->first = newTB->last = NULL;
	newTB->close = newTB->far = NULL;
	newTB->n_line = 0;
	return newTB;
}

static textnode *newnode (void){
    textnode *new = malloc (sizeof *new);
	if (new == NULL){
        printf("malloc fail");
        exit(1);
    }
	new->text = NULL;
	new->prev = new->next = NULL;
	return new;
}

static void freenode(textnode *node){
    free(node->text);
    free(node);
}
/**
 * Allocate a new textbuffer whose contents is initialised with the text
 * in the given string.
 */
TB newTB (char text[]) {
	TB buffer = create_TB();
	if(text == NULL){
	    fprintf(stderr, "The text is empty text"); 
	    abort();
	}else if(strlen(text) > 0){
	    int i = 0;
	    while(i != -1){
	        char *tmp = NULL;
	        int m = 0,size = 0;
	        while (m == 0){
	            size++;
	            tmp = realloc(tmp,size);
	            tmp[size-1] = (text[i] == '\n') ? 0 : text[i];
	            m = (text[i] == '\n');
	            i++;
	        }
	        textnode *node = newnode();
	        node->text = tmp;
	        if(buffer->first == NULL) 
	            buffer->first = buffer->last = node;
	        else{
	            buffer->last->next = node;
	            node->prev = buffer->last;
	            buffer->last = node;
	        } 
	        buffer->n_line++;
	        if(text[i] == 0)
	            i = -1;
	    }
	}
	return buffer;
}

/**
 * Free  the  memory occupied by the given textbuffer. It is an error to
 * access the buffer afterwards.
 */
void releaseTB (TB tb) {
    if(tb == NULL) return;
    
    textnode *n = tb->first;
    while(n != NULL){
        textnode *tmp = n;
        n = n->next;
        freenode(tmp);
    }
    free(tb);
}

/**
 * Allocate  and return a string containing all of the text in the given
 * textbuffer. If showLineNumbers is true, add a prefix corresponding to
 * the line number.
 */
char *dumpTB (TB tb, int showLineNumbers){
    if(tb->n_line == 0){
        char *t = malloc(sizeof(char));
        strcpy(t,"");
        return t;
    }
	textnode *n = tb->first;
	char *text = NULL;
	int i = 1, lines = 0;
	while(n != NULL){
	    lines++;
	    if(showLineNumbers){
	        int length = snprintf( NULL, 0, "%d", lines );
	        int m = i;
	        i = i + strlen(n->text) + 3 + length;
	        text = realloc(text, i);
	        if(lines == 1) text[0] = 0;
            char* str = malloc( length + 1 );
            snprintf(str, length + 1, "%d", lines);
	        strcat(text,str);
	        text[m+length-1] = '.';
	        text[m+length] = ' ';
	        text[m+length+1] = 0;
            strcat(text,n->text);
            free(str);
	    }else{
	        i = i + strlen(n->text) + 1;
	        text = realloc(text,i);
	        if(lines == 1) text[0] = 0;
            strcat(text,n->text);
        }
        text[i-2] = '\n';
        text[i-1] = 0;
	    n = n->next;
	}
	return text;
}

/* Return the number of lines of the given textbuffer.
 */
int linesTB (TB tb){
	return tb->n_line;
}

/**
 * Add a given prefix to all lines between 'from' and 'to', inclusive.
 * - The  program  should abort() wih an error message if 'from' or 'to'
 *   is out of range. The first line of a textbuffer is at position 1.
 */
void addPrefixTB (TB tb, int pos1/*from*/, int pos2/*to*/, char* prefix){
    if(pos1 < 1 || pos2 > tb->n_line){
        fprintf(stderr, "the position given is out of range\n");
        abort();
    }else if(pos1 > pos2){
        fprintf(stderr, "second given number need to bigger than first\n");
        abort();
    }else{
        textnode *n = tb->first;
        for(int i = 1; i <= pos2 ; i++){
            if(i >= pos1){
                char *x = malloc(strlen(prefix) + strlen(n->text) + 1);
                x[0] = 0;
                strcat(x,prefix);
                strcat(x,n->text);
                free(n->text);
                n->text = x;
            }
            n = n->next;
        }
    }
}
/**
 * Merge 'tb2' into 'tb1' at line 'pos'.
 * - After this operation:
 *   - What was at line 1 of 'tb2' will now be at line 'pos' of 'tb1'.
 *   - Line  'pos' of 'tb1' will moved to line ('pos' + linesTB('tb2')),
 *     after the merged-in lines from 'tb2'.
 *   - 'tb2' can't be used anymore (as if we had used releaseTB() on it)
 * - The program should abort() with an error message if 'pos' is out of
 *   range.
 */
void mergeTB (TB tb1, int pos, TB tb2){
    if(tb2->n_line != 0){    
        if(pos < 1 || pos > tb1->n_line + 1){
            fprintf(stderr, "the position given is out of range\n");
            abort();
        }else{
            textnode *start = tb2->first;
            textnode *end =  tb2->last;
            if(tb1->n_line == 0){
                tb1->first = start;
                tb1->last = end;
            }else if(pos == (tb1->n_line + 1)){
                tb1->last->next = start;
                start->prev = tb1->last;
                tb1->last = end;
            }else if(pos == 1){
                end->next = tb1->first;
                tb1->first->prev = end;
                tb1->first = start;
            }else{
                textnode *n = tb1->first;
                textnode *m = n;
                for(int i = 1; i < pos ; i++){        
                    m = n;
                    n = n->next;
                }
                m->next = start;
                start->prev = m;
                end->next = n;
                n->prev = end;
            }
            tb1->n_line = tb1->n_line + tb2->n_line;
            tb2->first = tb2->last = NULL;
        }
    }
    free(tb2);
}

/**
 * Copy 'tb2' into 'tb1' at line 'pos'.
 * - After this operation:
 *   - What was at line 1 of 'tb2' will now be at line 'pos' of 'tb1'.
 *   - Line  'pos' of 'tb1' will moved to line ('pos' + linesTB('tb2')),
 *     after the pasted-in lines from 'tb2'.
 *   - 'tb2' is unmodified and remains usable independent of tb1.
 * - The program should abort() with an error message if 'pos' is out of
 *   range.
 */
void pasteTB (TB tb1, int pos, TB tb2) {
    if(tb2->n_line != 0){ 
        char *x = dumpTB(tb2,0);
        TB tb3 = newTB(x);
        free(x);   
        if(pos < 1 || pos > tb1->n_line + 1){
            fprintf(stderr, "the position given is out of range\n");
            abort();
        }else{
            textnode *start = tb3->first;
            textnode *end =  tb3->last;
            if(tb1->n_line == 0){
                tb1->first = start;
                tb1->last = end;
            }else if(pos == (tb1->n_line + 1)){
                tb1->last->next = start;
                start->prev = tb1->last;
                tb1->last = end;
            }else if(pos == 1){
                end->next = tb1->first;
                tb1->first->prev = end;
                tb1->first = start;
            }else{
                textnode *n = tb1->first;
                textnode * m = n;
                for(int i = 1; i < pos ; i++){        
                    m = n;
                    n = n->next;
                }
                m->next = start;
                start->prev = m;
                end->next = n;
                n->prev = end;
            }
            tb1->n_line = tb1->n_line + tb3->n_line;
            tb3->first = tb3->last = NULL;
            free(tb3);
        }
    }
}

/**
 * Cut  the lines between and including 'from' and 'to' out of the given
 * textbuffer 'tb' into a new textbuffer.
 * - The result is a new textbuffer (much as one created with newTB()).
 * - The cut lines will be deleted from 'tb'.
 * - The  program should abort() with an error message if 'from' or 'to'
 *   is out of range.
 */
TB cutTB (TB tb, int from, int to) {
	if(from < 1 || to > tb->n_line){
        fprintf(stderr, "the position given is out of range\n");
        abort();
    }else if(from > to){
        fprintf(stderr, "second given number need to bigger than first\n");
        abort();
    }
    int n = to - from + 1;
    TB tb1 = create_TB();
    if(tb->n_line == n){
        tb1->first = tb->first;
        tb1->last = tb->last;
        tb->first = tb->last = NULL;
    }else{
        textnode *start = tb->first;
        for(int i = 1; i < from; i++)
            start = start->next;
            
        textnode *end = tb->first;
        for(int i = 1; i < to; i++)
            end = end->next;
            
        tb1->first = start;
        tb1->last = end;
        
        if(start == tb->first)
            tb->first = end->next;
        else if(end == tb->last)
            tb->last = start->prev;
        else{
            start->prev->next = end->next;
            end->next->prev = start->prev;
        }     
        tb->last->next = tb->first->prev = NULL;
        start->prev = end->next = NULL;       
    }
    tb1->n_line = n;
    tb->n_line = tb->n_line - n;
	return tb1;
}

void deleteTB (TB tb, int from, int to) {
	if(from < 1 || to > tb->n_line){
        fprintf(stderr, "the position given is out of range\n");
        abort();
    }else if(from > to){
        fprintf(stderr, "second given number need to bigger than first\n");
        abort();
    }
    int n = to - from + 1;
    TB tb1 = create_TB();
    if(tb->n_line == n){
        tb1->first = tb->first;
        tb1->last = tb->last;
        tb->first = tb->last = NULL;
    }else{
        textnode *start = tb->first;
        for(int i = 1; i < from; i++)
            start = start->next;
            
        textnode *end = tb->first;
        for(int i = 1; i < to; i++)
            end = end->next;
            
        tb1->first = start;
        tb1->last = end;
        
        if(start == tb->first)
            tb->first = end->next;
        else if(end == tb->last)
            tb->last = start->prev;
        else{
            start->prev->next = end->next;
            end->next->prev = start->prev;
        }     
        tb->last->next = tb->first->prev = NULL;
        start->prev = end->next = NULL;       
    }
    releaseTB(tb1);
    tb->n_line = tb->n_line - n;
}
# if 0

typedef struct matchNode {
      int lineNumber;
      int charIndex;
      struct matchNode* next;
} matchNode;

#endif
Match searchTB (TB tb, char *search) {
	if(tb->n_line == 0) return NULL;  
	int line = 1, is = 0, index = 0,max = 0;
	Match first = NULL, curr = NULL;
	for(textnode *n = tb->first; n != NULL; n = n->next){
	    if(max < strlen(n->text))
	        max = strlen(n->text);
	}
	char *m = NULL;
	char  tmp[tb->n_line][max+1];
	for(textnode *n = tb->first; n != NULL; n = n->next){	    
	    strcpy(tmp[line - 1],n->text);
	    while(strstr(tmp[line - 1], search) != NULL){	        
	        Match node = malloc(sizeof(matchNode)); 
	        node->lineNumber = line;
	        m = strstr(tmp[line - 1], search);
	        index = (int)(m - tmp[line - 1]);
	        node->charIndex = index + 1;
	        tmp[line - 1][index] = '\n';          
	        if(is == 0){
	           curr = first = node;
	           is++; 
	        }else{
	            curr->next = node;
	            curr = node;
	        }
	    }
	    line++;
	}
	if(curr != NULL) curr->next = NULL;
	return first;
}
/*
static void free_match(Match first){
    if (first == NULL) return;
    Match tmp = first->next;
    free(first);
    return free_match(tmp);
}*/

/**
 * Search  every  line of the given textbuffer for every occurrence of a
 * set of specified substitutions and alter them accordingly.
 * - Refer to the spec for details.
 */
 /*
static char *starANDline(char *original){
    int firstStar = -1, firstLine = -1, secondStar = -1, secondLine = -1;
    char *BetweenStar = NULL;
    char *BetweenLine = NULL;
    char *final = NULL;
    char html[][] = {"<b>", "</b>", "<i>", "</i>"}
    for(int i = 0; original[i] != 0; i++){
        if(x[i] == '*'){
            if(firstStar != -1){
                secondStar = i;
            }else if(original[i + 1] != '*'){
                firstStar = i;
            }    
        }else if(original[i] == '_'){
            if(firstLine != -1){
                secondLine = i;
            }else if(original[i + 1] != '_'){
                firstLine = i;
            }     
        }
        if(secondStar != -1 || secondLine != -1){
                final = realloc(final,strlen(final) + strlen(BetweenLine) + 7 + 1));
                strcpy(final,html[0 + 2 * (secondLine == -1)]);
                strcpy(final,BetweenStar);
                strcpy(final,html[1 + 2 * (secondLine == -1)]);
                firstStar = firstLine = -1;
                secondStar = secondLine = -1;
                free(BetweenStar);
                free(BetweenLine);
                BetweenStar = BetweenLine = NULL;
        }else if(firstStar != -1 && secondStar == -1 && original[i] != '*') {
             BetweenStar = realloc(BetweenStar,strlen(BetweenStar) + 1);
             BetweenStar[strlen(BetweenStar) - 1] = original[i]; 
             BetweenStar[strlen(BetweenStar)] = 0;               
        }else if(firstLine != -1 && secondLine == -1 && original[i] != '_'){
            BetweenLine = realloc(BetweenLine,strlen(BetweenLine) + 1);
            BetweenLine[strlen(BetweenLine) - 1] = original[i];
            BetweenLine[strlen(BetweenLine)] = 0;                               
        }else if(firstLine == -1 && firstStar == -1){
            final = realloc(final,strlen(final) + 1);
            final[strlen(final) - 1] = original[i];
            final[strlen(final)] = 0;
        }
    }     
}
*/
void formRichText (TB tb) {
    char *original = NULL;
    for(textnode *n = tb->first; n != NULL; n = n->next){
        original = n->text;
        if(original[0] == '#' && strlen(original) > 1){
            char *end = "</h1>";
            char *start = "<h1";
            char *tmp = NULL;
            tmp = realloc(tmp,strlen(original) + strlen(start) + strlen(end) + 1);
            strcpy(tmp,start);
            strcat(tmp,original);
            tmp[3] = '>';
            strcat(tmp,end);
            n->text = tmp;
            free(original);
        }else{
            if((strchr(original,'*') != NULL && strrchr(original,'*') != NULL &&
            strrchr(original,'*') > strchr(original,'*')) 
            ||(strchr(original,'_') != NULL && strrchr(original,'_') != NULL &&
            strrchr(original,'_') > strchr(original,'_'))){
                int firstStar = -1, firstLine = -1, secondStar = -1, secondLine = -1;
                char *BetweenStar = malloc(1);
                    strcpy(BetweenStar,"");
                char *BetweenLine = malloc(1);
                    strcpy(BetweenLine,"");
                char *final = malloc(1);
                    strcpy(final,"");
                int lengthStar = 1, lengthLine = 1, lengthFinal = 1;
                for(int i = 0; original[i] != 0; i++){
                    if((strchr(original,'*') != NULL && strrchr(original,'*') != NULL &&
                    strrchr(original,'*') == strchr(original,'*'))
                    if(original[i] == '*'){
                        if(firstStar != -1)
                            secondStar = i;
                        else if(original[i + 1] != '*')
                            firstStar = i;
                    }else if(original[i] == '_'){
                        if(firstLine != -1)
                            secondLine = i;
                        else if(original[i + 1] != '_')
                            firstLine = i;     
                    }if(secondStar != -1 && secondLine != -1){
                        final = realloc(final,lengthFinal + 
                         (firstStar < firstLine) * lengthStar + 
                         (firstStar > firstLine) * lengthLine + 7 + 1);
                        lengthFinal = lengthFinal + (firstStar < firstLine) * lengthStar + 
                         (firstStar > firstLine) * lengthLine + 7;
                        if(firstLine < firstStar){
                            strcat(final,"<b>");
                            strcat(final,BetweenStar);
                            strcat(final,"</b>");
                        }else{
                            strcat(final,"<i>");
                            strcat(final,BetweenStar);
                            strcat(final,"</b>");
                        }
                         lengthStar = lengthLine = 1;
                         firstStar = firstLine = -1;
                         secondStar = secondLine = -1;
                         if(BetweenStar != NULL) free(BetweenStar);
                         if(BetweenLine != NULL) free(BetweenLine);
                         BetweenStar = BetweenLine = NULL;
                    }else if((secondStar != -1 && firstLine == -1) || (secondLine != -1 && firstStar == -1)){
                         final = realloc(final,lengthFinal + 
                         (secondStar != -1) * lengthStar + 
                         (secondLine != -1) * lengthLine + 7 + 1);
                         lengthFinal = lengthFinal + (secondStar != -1) * lengthStar + 
                         (secondLine != -1) * lengthLine + 7;
                         if (secondStar != -1) strcat(final,"<b>");
                         else strcat(final,"<i>");
                         if (secondStar != -1) strcat(final,BetweenStar);
                         else strcat(final,BetweenLine);
                         if (secondStar != -1) strcat(final,"</b>");
                         else strcat(final,"</i>");
                         lengthStar = lengthLine = 1;
                         firstStar = firstLine = -1;
                         secondStar = secondLine = -1;
                         if(BetweenStar != NULL) free(BetweenStar);
                         if(BetweenLine != NULL) free(BetweenLine);
                         BetweenStar = BetweenLine = NULL;
                    }else if(firstStar != -1 && secondStar == -1 && original[i] != '*') {
                         BetweenStar = realloc(BetweenStar,lengthStar + 1);
                         BetweenStar[lengthStar - 1] = original[i]; 
                         BetweenStar[lengthStar] = 0; 
                         lengthStar++;       
                    }else if(firstLine != -1 && secondLine == -1 && original[i] != '_'){
                         BetweenLine = realloc(BetweenLine,lengthLine + 1);
                         BetweenLine[lengthLine - 1] = original[i];
                         BetweenLine[lengthLine] = 0;
                         lengthLine++;
                    }else if(firstLine == -1 && firstStar == -1){
                        final = realloc(final,lengthFinal + 1);
                        final[lengthFinal - 1] = original[i];
                        final[lengthFinal] = 0;
                        lengthFinal++;
                    }
                }
            free(original);
            n->text = final;
            }
        }       
    }   
}


char *diffTB (TB tb1, TB tb2) {
    int line = 1,length = 0;    
    textnode *original = tb1->first;
    textnode *final = tb2->first;
    char *diff = malloc(1);
    char *str = NULL;
    strcpy(diff, "");
    while(original != NULL || final != NULL){
        length = snprintf( NULL, 0, "%d", line);
        if(original == NULL){
            diff = realloc(diff, strlen(diff) + 5 + strlen(final->text) + length);
            str = malloc(length + 1 + 3);
            snprintf(str, length + 4, "+,%d,", line);
            strcat(diff,str);
            strcat(diff,final->text);
            final = final->next;
            line = line + 1;
            strcat(diff,"\n");
            free(str);
        }else if(final == NULL){
            diff = realloc(diff, strlen(diff) + 4 + length);
            str = malloc(length + 1 + 2);
            snprintf(str, length + 3, "-,%d", line);
            strcat(diff,str);
            original = original->next;
            strcat(diff,"\n");
            free(str);
        }else{
            if(strcmp(original->text,final->text) != 0){
                if(final->next != NULL && strcmp(final->next->text, original->text) == 0){
                    diff = realloc(diff, strlen(diff) + 4 + length);
                    str = malloc(length + 3);
                    snprintf(str, length + 3, "-,%d", line);
                    strcat(diff,str);
                    strcat(diff,"\n");
                    free(str); 
                    final = final->next;
                }else if(original->next != NULL && strcmp(original->next->text, final->text) == 0){
                    diff = realloc(diff, strlen(diff) + 5 + strlen(final->text) + length);
                    str = malloc(length + 1 + 3);
                    snprintf(str, length + 4, "+,%d,", line);
                    strcat(diff,str);
                    strcat(diff,final->text);
                    strcat(diff,"\n");
                    free(str);
                    original = original->next;
                }else{
                    diff = realloc(diff, strlen(diff) + 4 + length);
                    str = malloc(length + 3);
                    snprintf(str, length + 3, "-,%d", line);
                    strcat(diff,str);
                    strcat(diff,"\n");
                    free(str);                
                    diff = realloc(diff, strlen(diff) + 5 + strlen(final->text) + length);
                    str = malloc(length + 1 + 3);
                    snprintf(str, length + 4, "+,%d,", line);
                    strcat(diff,str);
                    strcat(diff,final->text);
                    strcat(diff,"\n");
                    free(str);
                }    
            }
            original = original->next;
            final = final->next;
            line = line + 1;
        }    
    }
	return diff;
}

void undoTB (TB tb) {
    
}

void redoTB (TB tb) {

}
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
} */ 
static void test12(){
     printf("-----------------------------------------\n"
	        "                12                       \n"
	        "-----------------------------------------\n");
	 TB tb1 = newTB("_string_*some_string_\n");
	 formRichText(tb1);
	 char *x = dumpTB(tb1,0);
	 printf("%s\n",tb1->first->text);
	 free(x);
	 releaseTB(tb1);      
}/*
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
	TB tb2 = newTB("2. \n3. \n4. \n5. \n6. \n7. \n8. \n9. \n10. \n11\n"); 
	char *x = diffTB(tb1, tb2); 
	printf("%s",x);
	free(x);
	releaseTB(tb1);
	releaseTB(tb2);       
}

static void test15(){
    printf("-----------------------------------------\n"
	       "                15                       \n"
	       "-----------------------------------------\n");
	TB tb1 = newTB("1. \n2. \n3. \n4. \n5. \n6. \n7. \n9. \n10. \n11\n");
	TB tb2 = newTB("1. \n2. \n3. \n4. \n5. \n6. \n"); 
	char *x = diffTB(tb1, tb2); 
	printf("%s",x);
	free(x);
	releaseTB(tb1);
	releaseTB(tb2);       
}  

static void test16(){
    printf("-----------------------------------------\n"
	       "                16                       \n"
	       "-----------------------------------------\n");
	TB tb1 = newTB("1. \n2. \n3. \n5. \n6. \n7. \n9. \n10. \n11\n");
	TB tb2 = newTB("2. \n3. \n4. \n5. \n6. \n"); 
    char *x = diffTB(tb1, tb2); 
	printf("%s",x);
	free(x);
	releaseTB(tb1);
	releaseTB(tb2);       
}

static void test17(){
    printf("-----------------------------------------\n"
	       "                17                       \n"
	       "-----------------------------------------\n");
	TB tb1 = newTB("2. \n3. \n5. \n6. \n");
	TB tb2 = newTB("2. \n3. \n5. \n6. \n"); 
	char *x = diffTB(tb1, tb2); 
	printf("%s",x);
	free(x);
	releaseTB(tb1);
	releaseTB(tb2);       
} 

static void test18(){
    printf("-----------------------------------------\n"
	       "                18                       \n"
	       "-----------------------------------------\n");
	TB tb2 = newTB("1. \n2. \n3. \n4. \n5. \n6. \n7. \n8. \n9. \n10. \n11\n");
	TB tb1 = newTB("2. \n3. \n4. \n5. \n6. \n7. \n8. \n9. \n10. \n11\n"); 
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
    test15();
    test16();
    test17();
    test18();
}

