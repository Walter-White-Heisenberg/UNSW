
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "Queue.h"

int shortestDistance(Graph g, int src, int dest) {
	int *x = calloc(GraphNumVertices(g),4);
	int *path =calloc(GraphNumVertices(g),4);
	for(int i = 0; i < GraphNumVertices(g); i++)
	    path[i] = (i != src) * (GraphNumVertices(g) + 1);
	x[src] = 1;
	Queue QQ = QueueNew();
	QueueEnqueue(QQ,src);
	while(QueueIsEmpty(QQ) == 0){
	    int point = QueueDequeue(QQ);
	    for (int i = 0; i < GraphNumVertices(g); i++){
	        if(GraphIsAdjacent(g,point,i) && !x[i]){
	            if(path[i] > path[point] + 1) {
	                path[i] = path[point] + 1;
	            }
	            QueueEnqueue(QQ,i);
	            x[i] = 1;
	        }
	    }
	}
	int count = (path[dest] == GraphNumVertices(g) + 1) ? -1 : path[dest];
	free(x);
	free(path);
	QueueFree(QQ);
	return count;
}

