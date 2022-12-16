//-----------------------------------------------------------------------------
// Kunal Shah, kgshah
// 2022 Spring CSE101 PA3
// Graph.c
// Implementation file for Graph ADT
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include "List.h"
#include "Graph.h"

// structs --------------------------------------------------------------------

// private Node type
typedef struct GraphObj* Graph;

// private NodeObj type
typedef struct GraphObj{
    int vertcount;
    int edgecount;
    int source;
    List* edges;
    int* vert_type;
    int* vert_parent;
    int* finish_time;
    int* discover_time;
    int* distance2source;
} GraphObj;

// Exported types -------------------------------------------------------------
typedef struct GraphObj* Graph;

/*** Constructors-Destructors ***/
// Creats new Graph item using Graph struct
Graph newGraph(int n){
    Graph NG = calloc(1,sizeof(GraphObj));
    NG->edges = calloc(n+1,sizeof(List));
    for(int i = 1;i<=n;i++){
        NG->edges[i] = newList();
    }
    NG->source = NIL;
    NG->vertcount = n;
    NG->vert_type = calloc(n+1,sizeof(int));
    NG->vert_parent = calloc(n+1,sizeof(int));
    NG->finish_time = calloc(n+1,sizeof(int));
    NG->discover_time = calloc(n+1,sizeof(int));
    NG->distance2source = calloc(n+1,sizeof(int));

    for (int i = 1;NG->vertcount>=i;i++){//may need offsett to clear last list
        NG->vert_type[i] = white;
        NG->distance2source[i] = INF;
        NG->vert_parent[i] = NIL;
        NG->discover_time[i] = UNDEF;
        NG->finish_time[i] = UNDEF;
    }

    return NG;
}

// Frees Graph item
void freeGraph(Graph* pG){
    if( pG!=NULL && *pG!=NULL ){
        for(int i=0;i<=((*pG)->vertcount);i++){
            freeList(&((*pG)->edges[i]));
        }
        free((*pG)->edges);
        free((*pG)->vert_type);
        free((*pG)->vert_parent);
        free((*pG)->finish_time);
        free((*pG)->discover_time);
        free((*pG)->distance2source);
        free(*pG);
    }
    *pG = NULL;
}
/*** Access functions ***/
//returns number of verticies
int getOrder(Graph G){
    return G->vertcount;
}
//returns number of edges(1 way and 2 way egges count for 1 each)
int getSize(Graph G){
    return G->edgecount;
}
//returns source given when running mapping
int getSource(Graph G){
    return G->source;
}
//returns parent of given child
int getParent(Graph G, int u){
    if((G->vertcount<u)||(u<1)){
        printf("Graph Error: calling getParent() with bad u(%d)\n",u);
        exit(EXIT_FAILURE);
    }
    return G->vert_parent[u];
}
int getDiscover(Graph G, int u){
    if((G->vertcount<u)||(u<1)){
        printf("Graph Error: calling getParent() with bad u(%d)\n",u);
        exit(EXIT_FAILURE);
    }
    return G->discover_time[u];
}
int getFinish(Graph G, int u){
    if((G->vertcount<u)||(u<1)){
        printf("Graph Error: calling getParent() with bad u(%d)\n",u);
        exit(EXIT_FAILURE);
    }
    return G->finish_time[u];
}
//returns distance to source given starting vertex
int getDist(Graph G, int u){
    if((G->vertcount<u)||(u<1)){
        printf("Graph Error: calling getDist() with bad u(%d)\n",u);
        exit(EXIT_FAILURE);
    }
    return G->distance2source[u];
}
//calculates the path 
void getPath(List L, Graph G, int u){
    if((G->vertcount<u)||(u<1)){
        printf("Graph Error: calling getPath() with bad u(%d)\n",u);
        exit(EXIT_FAILURE);
    }
    if (G->source==NIL){
        printf("Graph Error: calling getPath() on a non BFS Graph\n");
        exit(EXIT_FAILURE);

    }
    if(G->distance2source[u]==INF){
        append(L,NIL);
        return;
    }
    prepend(L,u);
    while(front(L)!=G->source){
        prepend(L,G->vert_parent[front(L)]);
    }
    if (u==G->source){
        deleteFront(L);
        append(L,G->source);
    }
}
/*** Manipulation procedures ***/
//reset graph obj to original state
void makeNull(Graph G){
    for (int i = 1;G->vertcount>i;i++){//may need offsett to clear last list
        clear(G->edges[i]);
    }
    G->source = NIL;
    for (int i = 1;G->vertcount>=i;i++){//may need offsett to clear last list
        G->vert_type[i] = white;
        G->distance2source[i] = INF;
        G->vert_parent[i] = NIL;
    }
}
//add 2 arcs to make a edge
void addEdge(Graph G, int u, int v){
    if((G->vertcount<u)||(u<1)){
        printf("Graph Error: calling addEdge() with bad u(%d)\n",u);
        exit(EXIT_FAILURE);
    }
    if((G->vertcount<v)||(v<1)){
        printf("Graph Error: calling addEdge() with bad v(%d)\n",u);
        exit(EXIT_FAILURE);
    }
    int tempcount = G->edgecount;
    addArc(G,u,v);
    addArc(G,v,u);
    if (G->edgecount - tempcount == 2){
        G->edgecount--;
    }else if(G->edgecount - tempcount == 1){
        G->edgecount--;
    }
}
//add a path to travel over
void addArc(Graph G, int u, int v){
    if((G->vertcount<u)||(u<1)){
        printf("Graph Error: calling addArc() with bad u(%d)\n",u);
        exit(EXIT_FAILURE);
    }
    if((G->vertcount<v)||(v<1)){
        printf("Graph Error: calling addArc() with bad v(%d)\n",u);
        exit(EXIT_FAILURE);
    }
    G->edgecount++;
    if (isEmpty(G->edges[u])){
        append(G->edges[u],v);
    }else{
        moveFront(G->edges[u]);
        while(get(G->edges[u])<=v){
            if (get(G->edges[u])==v){
                G->edgecount--;
                return;
            }
            moveNext(G->edges[u]);
            if(index(G->edges[u])==-1){
                append(G->edges[u],v);
                for(moveFront(G->edges[v]);index(G->edges[v])!=-1;moveNext(G->edges[v])){
                    if(get(G->edges[v])==u){
                        G->edgecount--;
                    }
                }
                return;
            }
        }
        insertBefore(G->edges[u],v);
    }
}

int Visit(Graph G,List S,int x,int time){
    G->discover_time[x] = ++time;
    G->vert_type[x] = gray;
    moveFront(G->edges[x]);
    while(index(G->edges[x])!=-1){
        //printf("rep:%d,%d\n",x,get(G->edges[x]));
        if((G->vert_type[get(G->edges[x])])==white){
            G->vert_parent[get(G->edges[x])] = x;
            time = Visit(G,S,get(G->edges[x]),time);
        }
        moveNext(G->edges[x]);
    }
    G->vert_type[x] = black;
    G->finish_time[x] = ++time;
    prepend(S,x);
    return time;
}

void DFS(Graph G, List S){
    //clear(S);
    moveFront(S);
    List N = newList();
    for (int i = 1;G->vertcount>=i;i++){//may need offsett to clear last list
        //append(S,i);
        G->vert_type[get(S)] = white;
        G->vert_parent[get(S)] = NIL;
        moveNext(S);
    }
    moveFront(S);
    int time = 0;
    for (int i = 1;G->vertcount>=i;i++){
        if (G->vert_type[get(S)]==white){
            time = Visit(G,N,get(S),time);
        }
        moveNext(S);
    }
    //for (int i = 1;G->vertcount>=i;i++){
    //    deleteFront(S);
    //}
    clear(S);
    for(moveFront(N); index(N)!=-1; moveNext(N)){
      append(S,get(N));
    }
    freeList(&N);
}

//Bredth first search alg and store data
void BFS(Graph G, int s){
    G->source = s;
    for (int i = 1;G->vertcount>=i;i++){//may need offsett to clear last list
        G->vert_type[i] = white;
        G->distance2source[i] = INF;
        G->vert_parent[i] = NIL;
    }
    G->vert_type[G->source] = gray;
    G->distance2source[G->source] = 0;
    G->vert_parent[G->source] = NIL;//dont really understand why I have to do this unless this is keeping other structs in mind delete
    List Q = newList();
    append(Q,G->source);
    while(length(Q)!=0){//dont know if this is correct
        int x = front(Q);
        deleteFront(Q);
        moveFront(G->edges[x]);
        while(index(G->edges[x])!=-1){
            if((G->vert_type[get(G->edges[x])])==white){
                G->vert_type[get(G->edges[x])] = gray;
                G->distance2source[get(G->edges[x])] = G->distance2source[x] + 1;
                G->vert_parent[get(G->edges[x])] = x;
                append(Q,get(G->edges[x]));
            }
            moveNext(G->edges[x]);
        }
        G->vert_type[x] = black;
    }
    freeList(&Q);
}

/*** Other operations ***/
//print adjacency list representation
Graph copyGraph(Graph G){
    Graph N = newGraph(G->vertcount);
    N->edgecount = G->edgecount;
    N->source = G->source;
    for (int i = 1;G->vertcount>=i;i++){
        freeList(&(N->edges[i]));
        N->edges[i] = copyList(G->edges[i]);
        N->vert_type[i] = G->vert_type[i];
        N->vert_parent[i] = G->vert_parent[i];
        N->finish_time[i] = G->finish_time[i];
        N->discover_time[i] = G->discover_time[i];
        N->distance2source[i] = G->distance2source[i];
    }
    return N;
}

Graph transpose(Graph G){
    Graph N = newGraph(G->vertcount);
    for (int i = 1;G->vertcount>=i;i++){
        for(moveFront(G->edges[i]); index(G->edges[i]) != -1; moveNext(G->edges[i])){
            addArc(N,get(G->edges[i]),i);
        }
    }
    return N;
}

void printGraph(FILE* out, Graph G){
    for (int i = 1;G->vertcount+1>i;i++){//may need offsett to clear last list
        fprintf(out,"%d: ",i);
        printList(out,G->edges[i]);
        //if (G->vertcount>i){
            fprintf(out,"\n");
        //}
    }
}

void printGraphdebugg(FILE* out, Graph G){
    for (int i = 1;G->vertcount+1>i;i++){//may need offsett to clear last list
        fprintf(out,"%d: ",i);
        printList(out,G->edges[i]);
        fprintf(out,"   Color:%d    Parents:%d    distance2source:%d",G->vert_type[i],G->vert_parent[i],G->distance2source[i]);//debugging purposes only so delete
        if (G->vertcount>i){
            fprintf(out,"\n");
        }
    }
}