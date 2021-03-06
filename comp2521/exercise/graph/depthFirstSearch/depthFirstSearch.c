
#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"


void keepfinding(Graph g, int src, int *x, int n){
    for(int i = 0; i < n; i++){
        if(GraphIsAdjacent(g,i,src) && !x[i]){
            printf("%d ",i);
            x[i] = 1;
            keepfinding(g, i, x, n);
        }
    }
}
void depthFirstSearch(Graph g, int src){
    int *x = calloc(GraphNumVertices(g),4);
    x[src] = 1;
    printf("%d ",src);
    keepfinding(g,src,x,GraphNumVertices(g));
    free(x);
}


