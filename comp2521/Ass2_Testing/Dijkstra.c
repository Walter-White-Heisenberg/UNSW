#include<stdio.h>
#include "Dijkstra.h"
#include<stdlib.h>
#include "PQ.h"

ShortestPaths dijkstra(Graph g, Vertex src);
void showShortestPaths(ShortestPaths sps);
void freeShortestPaths(ShortestPaths sps);

//initialize a new shortest path according to number of vertex and the starting point
static ShortestPaths createShortestPaths(int numV, Vertex origin){
    ShortestPaths new;
    new.numNodes = numV;
    new.src = origin;
    
    //initialize for array of distance
    new.dist = calloc(numV, sizeof(int));
    if (new.dist == NULL) {
		fprintf(stderr, "Couldn't allocate new node!\n");
		exit(EXIT_FAILURE);
	}
	
	// initialized the array of pointer
    new.pred = calloc(numV ,sizeof(struct PredNode *));
    if (new.pred == NULL) {
		fprintf(stderr, "Couldn't allocate new node!\n");
		exit(EXIT_FAILURE);
	}
	
	//initialize all of dist as the biggest int
    for(int i = 0; i < numV; i++){
        new.pred[i] = NULL;
        new.dist[i] = 0x7FFFFFFF;
    }
    return new; 
}


//helper function to create an prednode containing the certain value
static struct PredNode *createPredNode(Vertex predecessor){
    struct PredNode *Node = malloc(sizeof(PredNode));
    if (Node == NULL) {
		fprintf(stderr, "Couldn't allocate new node!\n");
		exit(EXIT_FAILURE);
	}
    Node->v = predecessor;
    Node->next = NULL;
    return Node;
}


//helper functino to free a link of prednodes
static void free_PredNode (struct PredNode *node){
    while(node != NULL){
        struct PredNode *tmp = node;
        node = node->next;
        free(tmp);
    }
}


// helper function to fill the pred part and dist part of a shprtest path for a given graph
// onnly dist + visited[] -> visited[i] contains the predecessor
static void append_SHTpath(Graph g, ShortestPaths original, int numV, int array[], PQ queue){    
    while(!PQIsEmpty(queue)){
        ItemPQ PQ_old = PQDequeue(queue);
        
        //only adding the point when is unvisited before
        if(array[PQ_old.key] == 0){
            for(AdjList outlink = GraphOutIncident(g,PQ_old.key);
            outlink != NULL; outlink = outlink->next){
            
                //if the sum of edge and current distance can be shorter than existing distance then relax the point
                if(outlink->weight + PQ_old.value < original.dist[outlink->v]){
                    original.dist[outlink->v] = outlink->weight + PQ_old.value;
                    
                    //adding the next point with its current shortest distance
                    ItemPQ PQ;
                    PQ.key = outlink->v;
                    PQ.value = original.dist[PQ.key];
                    PQAdd(queue,PQ); 
                    
                    //if there are prednode before, then free them all to avoid memory leak
                    if(original.pred[outlink->v] != NULL 
                    && PQ_old.key != outlink->v) free_PredNode(original.pred[outlink->v]);
                    original.pred[outlink->v] = createPredNode(PQ_old.key); 
                    
                }else if (outlink->weight + PQ_old.value == original.dist[outlink->v]) {
                    //if the distance is equal which means currently there are more than one shortest distance
                    //then create an prednode and append it into the existing corresponding pred list 
                    struct PredNode *insert = createPredNode(PQ_old.key);
                    insert->next = original.pred[outlink->v];
                    original.pred[outlink->v] = insert;
                }
            }
            //set point as visited after all the outlink is considered
            array[PQ_old.key] = 1;
        }
    }
}

ShortestPaths dijkstra(Graph g, Vertex src){
    int numV = GraphNumVertices(g);   
    ShortestPaths shortest = createShortestPaths(numV,src);
    shortest.dist[src] = 0;
    
    //this array indicated what point is visited
    int *array = calloc(numV, sizeof(int));
    
    //add the original point ot the queue for convinience
    PQ queue =  PQNew();
    ItemPQ start;
    start.key = src;
    start.value = 0;
    PQAdd(queue,start);
    append_SHTpath(g, shortest,numV, array, queue); 
     
    //free the throw away array and queue  
    PQFree(queue);
    free(array);
    
    //if a point is still infinity, ture it into zero
    for(int i = 0; i < numV; i++)
        shortest.dist[i] = shortest.dist[i] 
        - (0x7FFFFFFF - shortest.dist[i] < 1) * shortest.dist[i];
    return shortest;
}

/**
 * Frees all memory associated with the given ShortestPaths structure.
 */
void freeShortestPaths(ShortestPaths sps){
    free(sps.dist);
    
    //for every point free its prednode list
    for (int i = 0; i < sps.numNodes; i++)
        free_PredNode(sps.pred[i]);

    free(sps.pred);
}
