#include "list.h"
void listReverse(List l) {
	if(l->head == NULL || l->head->next == NULL) return;
    Node last = l->head, tmp = last, first = last, second = last;
    if(l->head->next->next == NULL){
	    last->next->next = tmp;
	    tmp->next = NULL;
	    l->head = last;
	    return;
	}
	first = last;
	second = last->next;
	last = last->next->next;
	first->next = NULL;
    for(;last->next!= NULL;last = last->next){
        second->next = first;
        first = second;
        second = last;
    }
    second->next = first; 
    last->next = second;
    l->head = last;
}

