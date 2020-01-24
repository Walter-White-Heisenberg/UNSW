// testList.c - testing DLList data type
// Written by John Shepherd, March 2013

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "DLList.h"
#include <string.h>


int identical(char *, char *);


int identical(char* a, char *b){
    int i = 0;
    while(a[i] != '\0' || b[i] != '\0'){
        if(a[i] != b[i]){
            return 0;
        }
        i++;
    }
    return 1;
}

int main (void)
{
    printf("****************please enter word 'first' in the empty list end by ctrl-D:\n");
	DLList myList = getDLList (stdin);
    printf("################tests of DLListBefore start:\n");
	//1. test for insert before ( DLListBefore (DLList L, char *it) )
	    printf("//condition one: insert before the only one\n");
	    DLListBefore(myList, "Second");
	    assert(identical(myList->curr->value, "Second") == 1 );
	    assert( myList->first->next == myList->last);
	    assert( myList->first == myList->last->prev);
	    assert( myList->first == myList->curr );
	    assert(validDLList (myList));
	    printf("1.1\n");
	    putDLList (stdout, myList);
	    printf("//condition two: insert before the first items\n");
	    DLListBefore(myList, "Third");
	    assert( identical(myList->curr->value, "Third") == 1  );
	    assert( myList->first->next == myList->last->prev);
	    assert( myList->first == myList->curr );
	    assert(validDLList (myList));
	    printf("1.2\n");
	    putDLList (stdout, myList);
	    printf("//condition three: normall condition(insert between second and third)\n");
	    DLListMoveTo (myList, 2);
	    DLListBefore(myList, "middle");
	    assert( identical(myList->curr->value, "middle") == 1  );
	    assert( identical(myList->curr->next->value, "Second") == 1 );
	    assert( identical(myList->curr->prev->value, "Third") == 1 );
	    assert(validDLList (myList));
	    printf("1.3\n");
        putDLList (stdout, myList);
	    DLListDelete(myList);
	    DLListDelete(myList);
	    DLListDelete(myList);
	    printf("*****************all tests for DLListBefore are passed\n");
        printf("#################tests of DLListAfter start:\n");
	    myList->curr->value = "First";
	//2.test for insert after ( DLListAfter (DLList L, char *it) )
	    printf("//condition one: insert after the only one\n");
	    DLListAfter(myList, "Second");
	    assert(identical(myList->curr->value, "Second") == 1 );
	    assert( myList->first->next == myList->last);
	    assert( myList->first == myList->last->prev);
	    assert( myList->last == myList->curr );
	    assert(validDLList (myList));
	    printf("2.1\n");
	    putDLList (stdout, myList);
	    printf("//condition two: insert after the last items\n");
	    DLListAfter(myList, "Fourth");
	    assert(identical(myList->curr->value, "Fourth") == 1 );
	    assert( myList->first->next == myList->last->prev);
	    assert( myList->last == myList->curr );
	    assert(validDLList (myList));
	    printf("2.2\n");
	    putDLList (stdout, myList);
	    printf("//condition three: insert in the middle\n");
	    DLListMoveTo (myList, 2);
	    DLListAfter(myList, "Third");
	    assert(identical(myList->curr->value, "Third") == 1 );
	    putDLList (stdout, myList);
	    assert( identical(myList->curr->next->value, "Fourth") == 1 );
	    assert( identical(myList->curr->prev->value, "Second") == 1 );
	    assert(validDLList (myList));
	    printf("2.3\n"); 
	    putDLList (stdout, myList);
	//3.test for Dllistdelete ( DLListDelete (DLList L) )
	    printf("################Now start to test DLListDelete\n");
	    printf("//condition one: delete the second one when there are four items\n");
	    DLListMoveTo (myList, 2);
        DLListDelete(myList);
        assert( myList->first->next == myList->last->prev);
        assert( myList->curr->next == myList->last );
	    assert(validDLList (myList));
	    printf("3.1\n");
	    putDLList (stdout, myList);
	    printf("//condition two: the middle one when there is three\n");
	    DLListDelete(myList);
        assert( myList->first->next == myList->last);
        assert( myList->curr == myList->last );
	    assert(validDLList (myList));
	    printf("3.2\n");
	    putDLList (stdout, myList);
	    printf("//condition three: delete last one when there are two\n");
	    DLListDelete(myList);
        assert( myList->first == myList->last);
        assert( myList->curr == myList->last );
	    assert(validDLList (myList));
	    printf("3.3\n");
	    putDLList (stdout, myList);
	    printf("//condition four: delete the first one when there are two\n");
	    DLListBefore(myList,"Zero");
	    DLListDelete(myList);
        assert( myList->first == myList->last);
        assert( myList->curr == myList->last );
	    assert(validDLList (myList));
	    printf("3.4\n");
        putDLList (stdout, myList);
        freeDLList (myList);
        printf("all tests for DLListDelete are passed\nNow please type 'first' to name the first item in an empty list then press ctrl-D:\n");

	//freeDLList (myList);
	return EXIT_SUCCESS;
}
