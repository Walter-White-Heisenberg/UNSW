
#include <stdlib.h>

#include "tree.h"

int TreeSumOdds(Tree t) {
	return (t == NULL) ? 0 : (t->value % 2 == 1) * (t->value) + TreeSumOdds(t->left) + TreeSumOdds(t->right);
}

