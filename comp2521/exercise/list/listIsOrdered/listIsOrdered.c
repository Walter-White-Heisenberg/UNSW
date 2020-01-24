
#include "list.h"

bool listIsOrdered(List l) {
	if(l->head == NULL || l->head->next == NULL) return true;
	int sb = 0, bs = 0;
	for(Node n = l->head;n->next != NULL;n = n->next){
	    if(n->value > n->next->value) bs++;
	    else if(n->value < n->next->value) sb++;
	}
	if(sb * bs == 0) return true;
	return false;
}

