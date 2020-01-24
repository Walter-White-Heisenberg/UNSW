
#include "BSTree.h"

#include <stdlib.h>

BSTree BSTreeGetSmallest(BSTree t) {
    if(t != NULL) return NULL;
    return (t->left == NULL) ? t : BSTreeGetSmallest(t->left);
}

