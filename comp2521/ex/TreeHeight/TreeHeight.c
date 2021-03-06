
#include <stdlib.h>

#include "tree.h"

int TreeHeight(Tree t) {
    if(t == NULL) return -1;
    if(t->left == NULL && t->right == NULL) return 0;
    return TreeHeight(t->left) > TreeHeight(t->right) ? TreeHeight(t->left) + 1: TreeHeight(t->right) + 1;    
}

