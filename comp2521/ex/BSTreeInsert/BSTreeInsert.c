
#include <stdio.h>
#include <stdlib.h>

#include "BSTree.h"

BSTree BSTreeInsert(BSTree t, int val) {
	if(t == NULL){
	    t = malloc(sizeof(struct BSTNode));
	    t->value = val;
	    t->right = t->left = NULL;
	}
	else if(val > t->value) t->right = BSTreeInsert(t->right,val);
	else if(val < t->value) t->left =  BSTreeInsert(t->left,val);
	return t;
}

