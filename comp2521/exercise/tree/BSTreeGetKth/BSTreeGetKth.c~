#include <stdlib.h>
#include "BSTree.h"
int size(BSTree t){
    return (t == NULL) ? 0 : 1 + size(t->left) + size(t->right);
}

int BSTreeGetKth(BSTree t, int k) {
	if(t == NULL) return 0;
	int l = size(t->left);
	if(l > k) return BSTreeGetKth(t->left, k);
	else if(l < k) return BSTreeGetKth(t->right, k-l-1);
	return t->value;
}

