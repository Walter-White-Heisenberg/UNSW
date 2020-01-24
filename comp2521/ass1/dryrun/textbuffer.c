#include <stdlib.h>
#include "textbuffer.h"
#include<string.h>
#include<stdio.h>
#include<assert.h>
struct textbuffer{
      struct textnode* first;
      struct textnode* last;
      int n_line;
};

typedef struct textnode{
      char* text;
      struct textnode* next;
      struct textnode* prev;
}textnode;
//create a non-empty textnode
static TB create_TB(void) {
    TB newTB = malloc(sizeof(struct textbuffer));
    if (newTB == NULL) {
        printf("malloc fail");
        exit(1);
    }
	newTB->first = newTB->last = NULL;
	newTB->n_line = 0;
	return newTB;
}
//create a empty textnode
static textnode *newnode (void) {
    textnode *new = malloc (sizeof *new);
	if (new == NULL) {
        printf("malloc fail");
        exit(1);
    }
	new->text = NULL;
	new->prev = new->next = NULL;
	return new;
}
//totally free a node
static void freenode(textnode *node) {
    free(node->text);
    free(node);
}
/**
 * Allocate a new textbuffer whose contents is initialised with the text
 * in the given string.
 */
TB newTB (char text[]) {
	TB buffer = create_TB();
	if (text == NULL) {
	    fprintf(stderr, "The text is empty text"); 
	    abort();
	} else if (strlen(text) > 0) {//if the text is "", the empty TB wil be returned
	    int i = 0;// i is the indicator to stop a loop
	    while (i != -1) {
	        char *tmp = NULL;//purpose of tmp is to         
	        int m = 0,size = 0;//save the text for a single node
	        
	        while (m == 0) {
	            size++;
	            tmp = realloc(tmp,size);
	            tmp[size-1] = (text[i] == '\n') ? 0 : text[i];//when
	            m = (text[i] == '\n');
	            i++;
	        }
	        
	        textnode *node = newnode();//initializing a node
	        node->text = tmp;//initializing a node
	        
	        if (buffer->first == NULL)               //from line67 to line73 is
	            buffer->first = buffer->last = node;//the process for insertion
	        else{
	            buffer->last->next = node;
	            node->prev = buffer->last;
	            buffer->last = node;
	        } 
	        
	        buffer->n_line++;
	        if (text[i] == 0)//when text[i] is '\0', the loop will stop
	            i = -1;     //however, i don't want i++ for every loop
	    }                   //which is the reason why I use it this way
	}
	return buffer;
}

/**
 * Free  the  memory occupied by the given textbuffer. It is an error to
 * access the buffer afterwards.
 */
void releaseTB (TB tb) {
    if (tb == NULL) return;
    
    textnode *n = tb->first;
    while (n != NULL) {
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
char *dumpTB (TB tb, bool showLineNumbers) {
    if (tb->n_line == 0) {
        char *t = malloc(sizeof(char));
        strcpy(t,"");
        return t;
    }
	textnode *n = tb->first;
	char *text = NULL;
	int i = 1, lines = 0;
	while (n != NULL) {
	    lines++;
	    if (showLineNumbers) {
	        int length = snprintf( NULL, 0, "%d", lines );//get the length for 
	        i = i + strlen(n->text) + 3 + length;
	        text = realloc(text, i);
	        if (lines == 1) text[0] = 0;
            char* str = malloc( length + 1 );//I need to malloc before snprintf
            snprintf(str, length + 1, "%d", lines);
	        strcat(text,str);
	        strcat(text,". ");//set to zero for the follwoing strcat
            strcat(text,n->text);
            free(str);
	    } else{
	        i = i + strlen(n->text) + 1;
	        text = realloc(text,i);
	        if (lines == 1) text[0] = 0;
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
int linesTB (TB tb) {
	return tb->n_line;
}

/**
 * Add a given prefix to all lines between 'from' and 'to', inclusive.
 * - The  program  should abort() wih an error message if 'from' or 'to'
 *   is out of range. The first line of a textbuffer is at position 1.
 */
void addPrefixTB (TB tb, int pos1/*from*/, int pos2/*to*/, char* prefix) {
    if (pos1 < 1 || pos2 > tb->n_line) {
        fprintf(stderr, "the position given is out of range\n");
        abort();
    } else if (pos1 > pos2) {
        fprintf(stderr, "second given number need to bigger than first\n");
        abort();
    } else{
        textnode *n = tb->first;
        for(int i = 1; i <= pos2 ; i++) {
            if (i >= pos1) {
                char *newVersion = malloc(strlen(prefix) + strlen(n->text) + 1);
                newVersion[0] = 0;
                strcat(newVersion,prefix);
                strcat(newVersion,n->text);
                free(n->text);
                n->text = newVersion;
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
void mergeTB (TB tb1, int pos, TB tb2) {
    if (tb2->n_line != 0) {    
        if (pos < 1 || pos > tb1->n_line + 1) {
            fprintf(stderr, "the position given is out of range\n");
            abort();
        } else{
            textnode *start = tb2->first;
            textnode *end =  tb2->last;
            if (tb1->n_line == 0) {//when tb1 is empty
                tb1->first = start;
                tb1->last = end;
            } else if (pos == (tb1->n_line + 1)) {//merge at the end
                tb1->last->next = start;
                start->prev = tb1->last;
                tb1->last = end;
            } else if (pos == 1) {//merge at the beginning
                end->next = tb1->first;
                tb1->first->prev = end;
                tb1->first = start;
            } else{//nornal case
                textnode *n = tb1->first;
                textnode *m = n;
                for(int i = 1; i < pos ; i++) {//find the correct line to insert      
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
    if (tb2->n_line != 0) { 
        char *x = dumpTB(tb2,0);
        TB tb3 = newTB(x); // copy tb2 for convenience
        free(x);   
        if (pos < 1 || pos > tb1->n_line + 1) {
            fprintf(stderr, "the position given is out of range\n");
            abort();
        } else{
            textnode *start = tb3->first;
            textnode *end =  tb3->last;
            if (tb1->n_line == 0) {//when tb1 is empty
                tb1->first = start;
                tb1->last = end;
            } else if (pos == (tb1->n_line + 1)) {//paste in the end
                tb1->last->next = start;
                start->prev = tb1->last;
                tb1->last = end;
            } else if (pos == 1) {//paste at the beginnning 
                end->next = tb1->first;
                tb1->first->prev = end;
                tb1->first = start;
            } else{//normal case
                textnode *n = tb1->first;
                textnode * m = n;
                for(int i = 1; i < pos ; i++) {//find the correct line to paste        
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
            free(tb3);//free the structure of tb3 after used
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
	if (from < 1 || to > tb->n_line) {
        fprintf(stderr, "the position given is out of range\n");
        abort();
    } else if (from > to) {
        return NULL;
    }
    int n = to - from + 1;//n for the number of lines need to be cut
    TB tb1 = create_TB();
    if (tb->n_line == n) {//cut all of node
        tb1->first = tb->first;
        tb1->last = tb->last;
        tb->first = tb->last = NULL;
    } else{
        textnode *start = tb->first;//find position of starting line
        for(int i = 1; i < from; i++)
            start = start->next;
            
        textnode *end = tb->first;
        for(int i = 1; i < to; i++)//find position of ending line
            end = end->next;
            
        tb1->first = start;
        tb1->last = end;
        
        if (start == tb->first)//cut from beginning
            tb->first = end->next;
        else if (end == tb->last)//cut until the last node
            tb->last = start->prev;
        else{//normal case
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

/**
 * Return  a  linked list of match nodes containing the positions of all
 * of the matches of string 'search' in 'tb'.
 * - The textbuffer 'tb' should remain unmodified.
 * - The user is responsible for freeing the returned list.
 */
 
Match searchTB (TB tb, char *search) {
	if (tb->n_line == 0 || strlen(search) == 0) return NULL;  
	int line = 1, is = 0, index = 0,max = 0;
	Match first = NULL, curr = NULL;
	for(textnode *n = tb->first; n != NULL; n = n->next) {//from line337 to line240
	    if (max < strlen(n->text))  //the purpose is to find 
	        max = strlen(n->text);//the maximum length of a line
	}
	char *m = NULL;
	char  tmp[tb->n_line][max+1];//in this form, tmp can be change by using index
	for(textnode *n = tb->first; n != NULL; n = n->next) {	    
	    strcpy(tmp[line - 1],n->text);
	    while (strstr(tmp[line - 1], search) != NULL) {	        
	        Match node = malloc(sizeof(matchNode)); 
	        node->lineNumber = line;
	        m = strstr(tmp[line - 1], search);
	        index = (int)(m - tmp[line - 1]);
	        node->columnNumber = index + 1;
	        tmp[line - 1][index] = '\n'; //change the array to get next index by using strstr   
	        if (is == 0) {                //line 352 to line 358 is for the insertion
	           curr = first = node;
	           is++; 
	        } else{
	            curr->next = node;
	            curr = node;
	        }
	    }
	    line++;
	}
	if (curr != NULL) curr->next = NULL;
	return first;
}


/**
 * Remove  the  lines between 'from' and 'to' (inclusive) from the given
 * textbuffer 'tb'.
 * - The  program should abort() with an error message if 'from' or 'to'
 *   is out of range.
 */
void deleteTB (TB tb, int from, int to) {
	if (from < 1 || to > tb->n_line) {
        fprintf(stderr, "the position given is out of range\n");
        abort();
    } else if (from > to) {
        fprintf(stderr, "second given number need to bigger than first\n");
        abort();
    }
    int n = to - from + 1;//n for the number of lines need to be cut
    TB tb1 = create_TB();//I put the deleted node into a empty buffer then release the buffer
    if (tb->n_line == n) {  //when all of nodes shoudl be deleted
        tb1->first = tb->first;
        tb1->last = tb->last;
        tb->first = tb->last = NULL;
    } else{
        textnode *start = tb->first;//find position of starting line
        for(int i = 1; i < from; i++)
            start = start->next;
            
        textnode *end = tb->first;//find position of ending line
        for(int i = 1; i < to; i++)
            end = end->next;
            
        tb1->first = start;
        tb1->last = end;
        
        if (start == tb->first)//delete from beginning
            tb->first = end->next;
        else if (end == tb->last)//delete until the last node
            tb->last = start->prev;
        else{//normal case
            start->prev->next = end->next;
            end->next->prev = start->prev;
        }     
        tb->last->next = tb->first->prev = NULL;
        start->prev = end->next = NULL;       
    }
    releaseTB(tb1);//release the buffer to free them all
    tb->n_line = tb->n_line - n;
}


/**
 * Search  every  line of the given textbuffer for every occurrence of a
 * set of specified substitutions and alter them accordingly.
 * - Refer to the spec for details.
 */
static char *starANDline(char *original,int from) {
    int firstStar = -1, firstLine = -1, secondStar = -1, secondLine = -1,starN = 0,lineN = 0;
    for(int i = from; original[i] != 0; i++) {//loop to get the position of first pair, and only count for from index 'from' to save time
        if (secondStar != -1 && secondLine != -1) {//quit when there are already pairs of * and _
            i = strlen(original)-1;//jump to the last one
        } else if (original[i] == '*') {
            if (firstStar != -1 && starN == 1) {
                secondStar = i;
                starN++;
            } else if (original[i + 1] != '*' && starN == 0) {
                firstStar = i;
                starN++;
            }    
        } else if (original[i] == '_') {
            if (firstLine != -1 && lineN == 1) {
                secondLine = i;
                lineN++;
            } else if (original[i + 1] != '_' && lineN == 0) {
                firstLine = i;
                lineN++;   
            }     
        }
    }
    
    if (secondStar != -1 || secondLine != -1) {
        int smaller = (secondLine == -1 ||(( firstStar < firstLine ) && (secondStar != -1))) ? firstStar : firstLine;
        int bigger = (smaller == firstStar) ? secondStar :secondLine; 
        char *final = malloc(strlen(original) + 6);
        strncpy(final,original,from);
        int m = from;
        for(int i = from; original[i] != 0; i++) {//loop to get the position of first pair, and only count for from index 'from' to save time
            if (i == smaller) {//replace first * or _ into html form 
                final[m] = '<';
                final[m+1] = (smaller == firstStar) ? 'b':'i';
                final[m+2] = '>';
                m = m + 3;
            } else if (i == bigger) {//replace second * or _ into html form
                final[m] = '<';
                final[m+1] = 47;
                final[m+2] = (smaller == firstStar) ? 'b':'i';
                final[m+3] = '>';
                m = m + 4;
                if (secondStar != -1 && secondLine != -1 
                && (bigger < firstStar + firstLine - smaller)) {//when both pair of * and _ are qualified
                    final = realloc(final,strlen(original) + 11);
                    smaller = firstStar + firstLine - smaller;
                    bigger = secondStar +secondLine - bigger;
                }                      
            } else{
                final[m] = original[i];//normal case
                m++;
            }
        }
        from = bigger;//to save the time
        free(original);
        final[m] = 0;
        return starANDline(final,from);//the new string will be returned until all qualified * and _ is replaced
    } else{
        return original;// once there are no qualified * and _, the final version is returned
    } 
}

static void free_match(Match first){
    if (first == NULL) return;
    Match tmp = first->next;
    free(first);
    return free_match(tmp);
}

void formRichText (TB tb) {
    char *original = NULL;
    for(textnode *n = tb->first; n != NULL; n = n->next) {
        original = n->text;
        if (original[0] == '#' && strlen(original) > 1) {//when '#' is at beginning 
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
        } else{
            n->text = starANDline(original,0);//when # is not at beginning
        }       
    }   
}

//turn tb1 into tb2, my idea is to compare line by line and decide the what operation to do
char *diffTB (TB tb1, TB tb2) {
    int line = 1,length = 0;        
    textnode *original = tb1->first;//turn original into final
    textnode *final = tb2->first;
    char *diff = malloc(1);
    char *str = NULL;
    strcpy(diff, "");
    while (original != NULL || final != NULL) {
        length = snprintf( NULL, 0, "%d", line);
        if (original == NULL) {//add line from finish when original is NULL
            diff = realloc(diff, strlen(diff) + 5 + strlen(final->text) + length);
            str = malloc(length + 1 + 3);
            snprintf(str, length + 4, "+,%d,", line);
            strcat(diff,str);
            strcat(diff,final->text);
            final = final->next;
            line = line + 1;
            strcat(diff,"\n");
            free(str);
        } else if (final == NULL) {//delete from original when final is NULL
            diff = realloc(diff, strlen(diff) + 4 + length);
            str = malloc(length + 1 + 2);
            snprintf(str, length + 3, "-,%d", line);
            strcat(diff,str);
            original = original->next;
            strcat(diff,"\n");
            free(str);
        } else{
            if (strcmp(original->text,final->text) != 0) {
                if (final->next != NULL && strcmp(final->next->text, original->text) == 0) {//if final's line is same as the next line of original
                    diff = realloc(diff, strlen(diff) + 4 + length);//then I only need to delete the current original line
                    str = malloc(length + 3);
                    snprintf(str, length + 3, "-,%d", line);
                    strcat(diff,str);
                    strcat(diff,"\n");
                    free(str); 
                    final = final->next;
                } else if (original->next != NULL && strcmp(original->next->text, final->text) == 0) {//if original's line is same as the next line of final
                    diff = realloc(diff, strlen(diff) + 5 + strlen(final->text) + length);//then I only need to add the current final line
                    str = malloc(length + 1 + 3);
                    snprintf(str, length + 4, "+,%d,", line);
                    strcat(diff,str);
                    strcat(diff,final->text);
                    strcat(diff,"\n");
                    free(str);
                    original = original->next;
                } else{//normal case, totally different line
                    diff = realloc(diff, strlen(diff) + 4 + length);
                    str = malloc(length + 3);//normal case, delete current original and add current final line
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
            final = final->next;//if line from original and line from final are same, then ther is no operation done 
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
        printf("%d %d\n",n->lineNumber,n->columnNumber);
        n = n->next;
    }
    free_match(m);
    releaseTB(tb1);
}  
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
}
static void test13(){
    printf("-----------------------------------------\n"
	       "                13                       \n"
	       "-----------------------------------------\n");
    TB tb1 = newTB("asdffsdffsdf\naaassd\ndf\nasdf\nsdfsdf\nsdfsdfsdf\n7. \n8. \n9. \n10. \n11\n");
    Match n = searchTB(tb1,"sdf");
    Match m = n;
    while(n != NULL){
        printf("%d %d\n",n->lineNumber,n->columnNumber);
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
