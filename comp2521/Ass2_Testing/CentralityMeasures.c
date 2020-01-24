// Centrality Measures ADT implementation
// COMP2521 Assignment 2

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "CentralityMeasures.h"
#include "Dijkstra.h"
#include "PQ.h"

//create nodevalus contain allocated array for each vertices
static NodeValues createNodeValues(int numV){
    NodeValues new;
    new.values = calloc(numV, sizeof(double));
    new.numNodes = numV;
    return new;
}

//find closeness for every point of g
NodeValues closenessCentrality(Graph g){
    assert(g != NULL);    
    int numV = GraphNumVertices(g);
    NodeValues close = createNodeValues(numV);
    
    for(int i = 0; i < numV; i++){
        ShortestPaths tmp = dijkstra(g, i);
        //always intialized the total distance and rechable
        int total = 0, reachable  = 1;
        
        for(int j = 0; j < numV; j++){
            //only count reachable point
            reachable += (tmp.pred[j] != NULL);
            //if there is no connection between two point the dist[i] will be zero so doesn't affect the total
            total = total + tmp.dist[j];
        }  
        printf("%d %d %d %d\n",i,reachable,numV,total);     
        //if number of point is 1 or reachable point is one then htere is no point to do the calculation 
        close.values[i] = (reachable == 1 || numV == 1) ? 
        0 : ((double)(reachable-1)*(double)(reachable-1)/((double)(numV-1)*(double)total));
        freeShortestPaths(tmp);
    }
    
    return close;
}


//find out how many shortest path there is between two point
static int HowManySht(Graph g, Vertex orig, Vertex dest, ShortestPaths from){
    //using numV*numV to make surei is always bigger than zero after lot of decrement 
    int howMany = 0, numV = GraphNumVertices(g), i = numV * numV;
    PQ Q = PQNew();
    ItemPQ start;
    
    //adding variable i to prevent the updating of same edge which will cause the ignore of some shortest path
    start.key = dest + i * numV;
    start.value = i;
    PQAdd(Q,start);
    
    while(!PQIsEmpty(Q)){
        ItemPQ new = PQDequeue(Q);
        
        //keep adding prednode until the original is reached
        for(struct PredNode *curr = from.pred[new.key % numV]; curr != NULL; curr = curr->next){
        
            if(curr->v == orig){
                howMany++;//everytime origi is reached means there is a possible shortest path
            }else{
                i--;//once a prednode is added, i will change
                ItemPQ add;
                
                //the current point (the pred point of the point saved in add.value)
                //the later a point is added, the value will be smaller
                //and the most recent edge added into the queue will be dequeue first so that no edge will be updated(overwritten)
                add.value = i;
                //no egde will share same value and key              
                add.key = curr->v + i * numV;
                
                //adding prednode into Queue
                PQAdd(Q,add);
            }
        }
    }
    PQFree(Q);
    return howMany;
}

//find normalised betweennessCentrality for each point in graph g
NodeValues betweennessCentrality(Graph g){
    assert(g != NULL);
    int numV = GraphNumVertices(g);
    NodeValues between = createNodeValues(numV);
    //no point doing calculation there are less than three points
    if(numV < 3) return between;
    for(int passed = 0; passed< numV; passed++){
        ShortestPaths pass = dijkstra(g,passed);
        for(int start = 0; start < numV; start++){
            ShortestPaths from = dijkstra(g,start);
            
            //only do calculation when passed point is reachable from starting point and they are not same point
            if(from.pred[passed] != NULL && passed != start){  
            
            //only do calculation when end point is reachable from starting point and they are not same point, 
            //also only if the distance form staring point to passed point plus distance from passed point to end points
            //is equal to the distance from staring point to end point can means passed point is on the sht                
                for(int end = 0; end < numV; end++){
                    if(from.pred[end] != NULL && pass.pred[end] != NULL && end != start && 
                    end != passed && from.dist[end] == from.dist[passed] + pass.dist[end]){
                    
                    //uses the number of sht from starting point to the passed point times that of sht from passed point to end point 
                    //then divide by that of sht from starting point to end point
                        between.values[passed] += 
                        (double)HowManySht(g, start, passed, from) * 
                        (double)HowManySht(g, passed, end, pass) 
                        / (double)HowManySht(g, start, end, from);
                    }
                }
            }
            freeShortestPaths(from);
        }
        freeShortestPaths(pass);
    }
    return between;
}

//not much difference between Normalized one and the original one
NodeValues betweennessCentralityNormalised(Graph g) {
	assert(g != NULL);
    int numV = GraphNumVertices(g);
    NodeValues normal = betweennessCentrality(g);
    
    //no point doing calculation when there is less than 3 vertices
    if(numV > 2)
        for(int i = 0;i<numV;i++)
            normal.values[i] = normal.values[i] 
            / (double)(numV - 1) / (double)(numV - 2);
    return normal;
}


void showNodeValues(NodeValues nvs) {
    for (int i = 0; i < nvs.numNodes; i++)
        printf("%d: %f\n",i,nvs.values[i]);
}

//free the nodevalues
void freeNodeValues(NodeValues nvs) {
    free(nvs.values);
}

