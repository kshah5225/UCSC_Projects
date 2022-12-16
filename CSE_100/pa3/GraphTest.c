//-----------------------------------------------------------------------------
// Kunal Shah, kgshah
// 2022 Spring CSE101 PA3
// Graph.c
// Implementation file for Graph ADT
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"
#include"List.h"
//add tests for getdiscover,getfinish,dfs,transpose,copygraph
int main(){
    Graph G = newGraph(10);
    List S = newList();

    addEdge(G,1,2);
    addEdge(G,3,8);
    addArc(G,6,9);
    addEdge(G,8,3);
    addEdge(G,4,2);
    addArc(G,1,4);
    addEdge(G,5,4);
    addEdge(G,5,6);
    addEdge(G,6,3);
    addEdge(G,7,4);


    for (int i = 1;getOrder(G)>=i;i++){
        append(S,i);
    }
    DFS(G,S);

    printGraph(stdout,G);
    printf("\n");

    printList(stdout,S);
    printf("\n%d %d %d %d %d %d\n",getOrder(G),getSize(G),getFinish(G,2),getDiscover(G,2),getParent(G,8),getDist(G,8));
    
    makeNull(G);
    printGraph(stdout,G);

    freeGraph(&G);
    freeList(&S);
    printf("\n");
}
/*
Expected Output:
1: 2 4
2: 1 4
3: 6 8
4: 2 5 7
5: 4 6
6: 3 5 9
7: 4
8: 3
9: 
10: 

10 1 2 4 7 5 6 9 3 8
10 6 17 2 3 -1
1: 
2: 
3: 
4: 
5: 
6: 
7: 
8: 
9: 
10:
*/