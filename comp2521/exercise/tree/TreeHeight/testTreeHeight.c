
#include <stdio.h>
#include <stdlib.h>

#include "tree.h"

int TreeHeight(Tree t);
bool isTreeSame(Tree t1, Tree t2);

int main(void) {
	Tree t = readTree(0);
	printf("Tree:\n");
	printTree(t);
	
	int height = TreeHeight(t);
	printf("TreeHeight returned: %d\n", height);
	freeTree(t);
}

