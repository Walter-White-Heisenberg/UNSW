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
	newTB->number = 0;
	return newTB;
}

static TB copyTB(TB tb){
    char *x = dumpTB(tb);
    TB tb1 = newTB(x);
    free(x);
    return tb1;
}

static void insertTB(TB tb, TB tb2){
    TB closest = tb->close;
    if(closest != NULL){
       tb2->close = closest;
       closest->far = tb2;
    }
    tb->close = tb2;
    tb2->far = tb;
}

static void moveOld(TB tb){
    TB tmp = tb;
    if(tb->close != NULL) return moveOld(tb->close);
    textnode* n = tb->close->first;
    textnode* tmp = NULL;
    while(n != NULL){
        tmp = n;
        n = n->next;
        free(node->text);
        free(node);
    }
    free(tb->close);
    tb->close = NULL;
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
    
    textnode *n = NULL;
    textnode *tmp = NULL;
    TB tb1 = NULL;
    while (tb != NULL){
        tb1 = tb;        
        tb = tb->far;
        n = tb1->first;
        while(n != NULL){
            tmp = n;
            n = n->next;
            free(node->text);
            free(node);
        }
        free(tb1);
    }   
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
    TB closest = copyTB(tb1);
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
    if(tb1->number == 10) moveOld(tb1);
    else tb1->number++;
    insertTB(tb1,closest);
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
    TB closest = copyTB(tb1);
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
    if(tb1->number == 10) moveOld(tb1);
    else tb1->number++;
    insertTB(tb1,closest);
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
    TB closest = copyTB(tb1);
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
    if(tb1->number == 10) moveOld(tb1);
    else tb1->number++;
    insertTB(tb1,closest);
	return tb1;
}

void deleteTB (TB tb, int from, int to) {
    TB closest = copyTB(tb1);
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
    if(tb1->number == 10) moveOld(tb1);
    else tb1->number++;
    insertTB(tb1,closest);
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

static void free_match(Match first){
    if (first == NULL) return;
    Match tmp = first->next;
    free(first);
    return free_match(tmp);
}

static char *starANDline(char *x){
    int firstStar = -1, firstLine = -1, secondStar = -1, secondLine = -1,starN = 0,lineN = 0;
    for(int i = 0; x[i] != 0; i++){
        if(secondStar != -1 && secondLine != -1){
            i = strlen(x)-1;
        }else if(x[i] == '*' ){
            if(firstStar != -1 && starN == 1){
                secondStar = i;
                starN++;
            }else if(x[i + 1] != '*' && starN == 0){
                firstStar = i;
                starN++;
            }    
        }else if(x[i] == '_'){
            if(firstLine != -1 && lineN == 1){
                secondLine = i;
                lineN++;
            }else if(x[i + 1] != '_' && lineN == 0){
                firstLine = i;
                lineN++;   
            }     
        }
    }
    if(secondStar != -1 || secondLine != -1){
        int smaller = (secondLine == -1 ||(( firstStar < firstLine ) && (secondStar != -1))) ? firstStar : firstLine;
        int bigger = (smaller == firstStar) ? secondStar :secondLine; 
        char *final = malloc(strlen(x) + 6);
        int m = 0;
        for(int i = 0; x[i] != 0; i++){
            if(i == smaller){
                final[m] = '<';
                final[m+1] = (smaller == firstStar) ? 'b':'i';
                final[m+2] = '>';
                m = m + 3;
            }else if(i == bigger){
                final[m] = '<';
                final[m+1] = 47;
                final[m+2] = (smaller == firstStar) ? 'b':'i';
                final[m+3] = '>';
                m = m + 4;
                if(secondStar != -1 && secondLine != -1 && (bigger < firstStar + firstLine - smaller)){
                    final = realloc(final,strlen(x) + 11);
                    smaller = firstStar + firstLine - smaller;
                    bigger = secondStar +secondLine - bigger;
                }                      
            }else{
                final[m] = x[i];
                m++;
            }
        }
        free(x);
        final[m] = 0;
        x = final;
        return starANDline(x);
    }else{
        return x;
    } 
}

void formRichText (TB tb) {
    char *x = NULL;
    for(textnode *n = tb->first; n != NULL; n = n->next){
        x = n->text;
        if(x[0] == '#' && strlen(x) > 1){
            char *end = "</h1>";
            char *start = "<h1";
            char *tmp = NULL;
            tmp = realloc(tmp,strlen(x) + strlen(start) + strlen(end) + 1);
            strcpy(tmp,start);
            strcat(tmp,x);
            tmp[3] = '>';
            strcat(tmp,end);
            n->text = tmp;
            free(x);
        }else{
            n->text = starANDline(x);
        }       
    }   
}
/*
void DIFFhelper(char *diff,char *str, int length, int line, int is_plus,int textlength){
    diff = realloc(diff, strlen(diff) + 4 + textlength + length + is_plus);
    str = malloc(length + is_plus + 3);
    if(is_plus == 1)
        snprintf(str, length + 4, "+,%d,", line);
    else
        snprintf(str, length + 3, "-,%d", line);
    strcat(diff,str);
    free(str);
}

char *diffTB (TB tb1, TB tb2) {
    int line = 1,length = 0;
    char *diff = malloc(1);
    char *str = NULL;
    strcpy(diff, "");
    textnode *original = tb1->first;
    textnode *final = tb2->first;
    while(original != NULL || final != NULL){
        length = snprintf( NULL, 0, "%d", line);
        if(original == NULL){
            DIFFhelper(diff,str,length,line,1,strlen(final->text));
            strcat(diff,final->text);
            final = final->next;
            line = line + 1;
            strcat(diff,"\n");
        }else if(final == NULL){
            DIFFhelper(diff,str,length,line,0,0);
            original = original->next;
            strcat(diff,"\n");
        }else{ 
            if(strcmp(original->text,final->text) != 0){
                DIFFhelper(diff,str,length,line,0,0);
                strcat(diff,"\n");
                DIFFhelper(diff,str,length,line,1,strlen(final->text));
                strcat(diff,final->text);
                line = line + 1;
            }
            original = original->next;
            final = final->next;
            strcat(diff,"\n");
        }
    }
	return diff;
}*/
/*
void mergeNum_Symbol_and_text(char *diff,char *text,int aORd, int line){
    printf("%s\n",text);
    int length = snprintf( NULL, 0, "%d", line);
    diff = (aORd == 1) ? realloc(diff, strlen(diff) + 5 + length + strlen(text)) : realloc(diff, strlen(diff) + 4 + length);
    printf("%d",strlen(diff));    
    char *str = malloc(length + 3 + aORd);
    if(aORd == 1){
        snprintf(str, length + 4, "+,%d,", line);
        strcat(diff,str);
        strcat(diff,text);
    }else{
        snprintf(str, length + 3, "-,%d", line);
        strcat(diff,str);
    }
    printf("%s",str);
    free(str);
    strcat(diff,"\n");
}
char *diffTB (TB tb1, TB tb2) {
    int line = 1;    
    textnode *original = tb1->first;
    textnode *final = tb2->first;
    char *diff = malloc(1);
    strcpy(diff, "");
    while(original != NULL || final != NULL){        
        if(original == NULL){
            mergeNum_Symbol_and_text(diff,final->text,1,line);
            final = final->next;
            line = line + 1;
            printf("1111\n");
        }else if(final == NULL){
            mergeNum_Symbol_and_text(diff,"",0,line);
            original = original->next;
            printf("3333\n"); 
        }else{
            if(strcmp(original->text,final->text) != 0){
                mergeNum_Symbol_and_text(diff,final->text,1,line);                
                mergeNum_Symbol_and_text(diff,"",0,line);
            }
            original = original->next;
            final = final->next;
            line = line + 1;
            printf("2222\n"); 
        }    
    }
	return diff;
}*/

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
    if(tb->close != NULL){
        tb->close->number = tb->number;
        tb = tb->close;
    }
}

void redoTB (TB tb) {
    if(tb->far != NULL){
    
    }
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

