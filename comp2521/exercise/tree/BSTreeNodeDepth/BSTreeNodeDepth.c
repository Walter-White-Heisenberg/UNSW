
#include <stdlib.h>

#include "BSTree.h"

int BSTreeNodeDepth(BSTree t, int key) {
    if(t == NULL) return -1;
    else if(t->value == key) return 0;
    int depth = 0;
    if(t->value > key) depth = BSTreeNodeDepth(t->left,key);
    else if(t->value < key) depth = BSTreeNodeDepth(t->right,key);
    if(depth != -1) depth++;
    return depth;
}

