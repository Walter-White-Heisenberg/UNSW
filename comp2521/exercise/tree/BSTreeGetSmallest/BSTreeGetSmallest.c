
#include "BSTree.h"

#include <stdlib.h>

BSTree BSTreeGetSmallest(BSTree t) {
	if(t == NULL || t->left == NULL) return t;
    return BSTreeGetSmallest(t->left);
}

