
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "Queue.h"

int numWithin(Graph g, int src, int dist) {
	int *x = calloc(GraphNumVertices(g),4);
	int *path = calloc(GraphNumVertices(g),4);
	for(int i = 0; i < GraphNumVertices(g);i++)
	    path[i] = (i != src) * (GraphNumVertices(g) + 1);
	Queue QQ = QueueNew();
	QueueEnqueue(QQ,src);
	x[src] = 1;
	while(!QueueIsEmpty(QQ)){
	    int point = QueueDequeue(QQ);
	    for(int i = 0; i < GraphNumVertices(g);i++){
	        if(GraphIsAdjacent(g,i,point) && x[i] == 0){
	            if(path[point] + 1 < path[i]) path[i] = path[point] + 1;
	            QueueEnqueue(QQ,i);
	            x[i] = 1;
	        }
	        
	    }
	}
	int count = 0;
	for(int i = 0; i < GraphNumVertices(g); i++)
	    if(dist >= path[i]) count++;
	free(path);
		free(x);
		QueueFree(QQ);
	return count;
}

