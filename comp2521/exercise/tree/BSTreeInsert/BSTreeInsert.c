
#include <stdio.h>
#include <stdlib.h>

#include "BSTree.h"

BSTree BSTreeInsert(BSTree t, int val) {
	if(t == NULL){
	    t = malloc(sizeof(*t));
	    t->left = t->right = NULL;
	    t->value = val;
	}else if(t->value > val) t->left = BSTreeInsert(t->left,val);
	else if(t->value < val)t->right = BSTreeInsert(t->right,val);
	return t;
}

