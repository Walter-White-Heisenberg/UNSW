#include "list.h"
List listSetIntersection(List s1, List s2) {
    List new = malloc(sizeof(struct list));
    new->head = NULL;
    Node tmp = NULL;
    int i = 0;
    for(Node n1 = s1->head;n1 != NULL;n1 = n1->next)
        for(Node n2 = s2->head;n2 != NULL;n2 = n2->next){
            if (n1->value == n2->value){
                Node newNode = malloc(sizeof(struct node));
                newNode->value = n1->value;
                newNode->next = NULL;
                if (i == 0) {new->head = newNode;tmp = new->head;i++;}
                else {tmp->next = newNode;tmp = tmp->next;}
            }
        }
    return new;
}
