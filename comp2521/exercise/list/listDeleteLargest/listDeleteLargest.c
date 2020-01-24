
#include "list.h"

int listDeleteLargest(List l) {
	if(l->head == NULL) return -1;
	int m = l->head->value;
	if(l->head->next == NULL){    
	    
	}
	for(Node n = l->head;n != NULL; n = n->next){
	    if(m < n->value) m = n->value;
	}
	if(m == l->head->value){
	    Node tmp = l->head;	    
	    l->head = tmp->next; 
	    free(tmp);	       
	}else{
	    for(Node n = l->head;n != NULL; n = n->next){
	        if (n->next->value == m) {
	            Node tmp = n->next;
	            n->next = n->next->next;
	            free(tmp);
	            break;
	        }
	    } 
	}
    return m;
}

