
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "Queue.h"

void breadthFirstSearch(Graph g, int src) {
	int *x = calloc(GraphNumVertices(g),4);
	Queue QQ = QueueNew();
	QueueEnqueue(QQ,src);
	x[src] = 1;
	printf("%d ",src);
	while(!QueueIsEmpty(QQ)){
	    int point = QueueDequeue(QQ);
	    for(int i = 0; i < GraphNumVertices(g); i++){
	        if(GraphIsAdjacent(g,i,point) && x[i] == 0){
	            QueueEnqueue(QQ,i);
	            x[i] = 1;
	            printf("%d ",i);
	        }
	    }  
	}
	free(x);
	QueueFree(QQ);
}

