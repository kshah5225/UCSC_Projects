//-----------------------------------------------------------------------------
// Kunal Shah, kgshah
// 2022 Spring CSE101 PA3
// Graph.h
// Header file for Graph ADT
//-----------------------------------------------------------------------------
#ifndef Graph_H_INCLUDE_
#define Graph_H_INCLUDE_

#include<stdbool.h>
#include "List.h"

#define INF -1
#define NIL 0
#define UNDEF -1

#define white 1
#define gray 0
#define black -1

// Exported types -------------------------------------------------------------
typedef struct GraphObj* Graph;

/*** Constructors-Destructors ***/

// Creats new Graph item using Graph struct
Graph newGraph(int n);

// Frees Graph item
void freeGraph(Graph* pG);

/*** Access functions ***/

//returns number of verticies
int getOrder(Graph G);

//returns number of edges(1 way and 2 way egges count for 1 each)
int getSize(Graph G);

//returns source given when running mapping
int getSource(Graph G);

//returns parent of given child
int getParent(Graph G, int u);

//returns the next child
int getDiscover(Graph G, int u);// Pre: 1<=u<=n=getOrder(G)

//returns last child of childs
int getFinish(Graph G, int u);

//returns distance to source given starting vertex
int getDist(Graph G, int u);

//calculates the path
void getPath(List L, Graph G, int u);

/*** Manipulation procedures ***/

//reset graph obj to original state
void makeNull(Graph G);

//add 2 arcs to make a edge
void addEdge(Graph G, int u, int v);

//add a path to travel over
void addArc(Graph G, int u, int v);

//Bredth first search alg and store data
void BFS(Graph G, int s);

//Depth first search alg and store data
void DFS(Graph G,List S);

/*** Other operations ***/

//returns Graph pointer to a transposed graph
Graph transpose(Graph G);

//returns graph pointer to a copy of input graph
Graph copyGraph(Graph G);

//print adjacency list representation
void printGraph(FILE* out, Graph G);

void printGraphdebugg(FILE* out, Graph G);

#endif