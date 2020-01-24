
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"

void howmany(Graph g, int src,int *x){
    for(int i = 0; i < GraphNumVertices(g);i++){
        if(GraphIsAdjacent(g,i,src) && !x[i]){
            x[i] = 1;
            howmany(g, i, x);
        }
    }
}

int numReachable(Graph g, int src) {
	int *x = calloc(GraphNumVertices(g),4);
	x[src] = 1;
	howmany(g, src, x);
	int count = 0;
	for(int i = 0; i < GraphNumVertices(g);i++){
	    count += x[i];
	}
	free(x);
	return count;
}

