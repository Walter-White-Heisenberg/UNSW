
#include <stdlib.h>

#include "BSTree.h"

int BSTreeNodeDepth(BSTree t, int key) {
	int num = 
	if(t == NULL) return -1 ;
	if(t->value == key) return 0;
	return (key > t->value) ? BSTreeNodeDepth(t->right,key) + 1: BSTreeNodeDepth(t->left,key) + 1;
}

