
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "Stack.h"

void dfs(Graph g, int src, int dest, int *x, bool *cycle) {
    for(int i = 0; i < GraphNumVertices(g); i++){
        if(i != src && i != dest && GraphIsAdjacent(g,i,src)){
            if(x[i] == 1){
                *cycle = true;
                return;
            }else{
                x[i] = 1;
                dfs(g,i,src,x,cycle);
            }
        }
    }
}

bool hasCycle(Graph g) {
    bool cycle = false;
    for(int i = 0; i < GraphNumVertices(g); i++){
        int *x = calloc(GraphNumVertices(g),4);
        x[i] = 1;
        dfs(g,i,i,x,&cycle);
        free(x);
        if(cycle) break;    
    }
    return cycle;
}

