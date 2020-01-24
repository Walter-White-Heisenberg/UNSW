
#include <stdlib.h>

#include "tree.h"

int TreeHeight(Tree t) {
    if(t == NULL) return -1;
    int r = 1 + TreeHeight(t->left);
    int l = 1 + TreeHeight(t->right);
    return (r > l) ? r : l;
}


bool isTreeSame(Tree t1, Tree t2){
    if(t1 == NULL && t2 == NULL) return true;
    else if((t1 != NULL && t2 == NULL) || (t1 == NULL && t2 != NULL)) return false;
    else {
        if(t1->value != t2->value) return false;
        return (isTreeSame(t1->left, t2->left) && isTreeSame(t1->right, t2->right));
    }
}

