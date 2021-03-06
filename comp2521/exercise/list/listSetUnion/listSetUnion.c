#include "list.h"
List listSetUnion(List s1, List s2) {
	List new = malloc(sizeof(struct list));
	new->head = NULL;
	Node tmp = NULL;
	int i = 0;
	for(Node n1 = s1->head;n1 != NULL;n1 = n1->next){
	    Node newNode = newNode(n1->value);
        if (i == 0) {new->head = newNode;tmp = new->head;i++;}
	    else {tmp->next = newNode;tmp = tmp->next;}  
	}  
	for(Node n2 = s2->head;n2 != NULL;n2 = n2->next){
	    if(new->head == NULL){
	        Node newNode = newNode(n2->value);
            new->head = newNode;
            tmp = new->head;
            i++;
	    }else{
	        i = 0;
	        for(Node n3 = new->head;n3 != NULL;n3 = n3->next){
	            if (n3->value == n2->value) i = 1;
	            if (i == 0 && tmp->value == n3->value){
                    Node newNode = newNode(n2->value);
                    tmp->next = newNode;
                    tmp = tmp->next;
                    break;
	            }
	        }
	    }
	}
	return new;
}
