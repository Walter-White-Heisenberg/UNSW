
#include <stdlib.h>

#include "tree.h"

int height(Tree t){
    return (t == NULL) ? 0 : 1 + height(t->right) + height(t->left);
}

bool TreeIsPerfectlyBalanced(Tree t) {
    if(t == NULL) return true;
    int r = height(t->right);
    int l = height(t->left);
    if((r-l)*(r-l) > 1) return false;
    else if(TreeIsPerfectlyBalanced(t->left) == true && TreeIsPerfectlyBalanced(t->right) == true) return true;
    return false;
}
