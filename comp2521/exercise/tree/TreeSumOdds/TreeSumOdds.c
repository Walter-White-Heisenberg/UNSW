
#include <stdlib.h>

#include "tree.h"

int TreeSumOdds(Tree t) {
   return (t == NULL) ? 0 : (t->value % 2) * (t->value) + TreeSumOdds(t->right) + TreeSumOdds(t->left); 
}

