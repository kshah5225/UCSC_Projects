//-----------------------------------------------------------------------------
// Kunal Shah, kgshah
// 2022 Spring CSE101 PA2
// Graph.c
// Implementation file for Graph ADT
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"
#include"List.h"

int main(){
    Graph G = newGraph(10);

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




    BFS(G,2);

    printGraph(stdout,G);
    printGraphdebugg(stdout,G);
    printf("\n");

    List L = newList();
    getPath(L,G,8);
    printList(stdout,L);
    printf("\n%d %d %d %d %d\n",getOrder(G),getSize(G),getSource(G),getParent(G,8),getDist(G,8));

    makeNull(G);
    printGraphdebugg(stdout,G);

    freeGraph(&G);
    freeList(&L);
    printf("\n");
}
/*
Expected Output:
1: 2 4
2: 1 4
3: 6 8 8
4: 2 5 7
5: 4 6
6: 3 5 9
7: 4
8: 3 3
9: 
10: 1: 2 4   Color:-1    Parents:2    distance2source:1
2: 1 4   Color:-1    Parents:0    distance2source:0
3: 6 8 8   Color:-1    Parents:6    distance2source:4
4: 2 5 7   Color:-1    Parents:2    distance2source:1
5: 4 6   Color:-1    Parents:4    distance2source:2
6: 3 5 9   Color:-1    Parents:5    distance2source:3
7: 4   Color:-1    Parents:4    distance2source:2
8: 3 3   Color:-1    Parents:3    distance2source:5
9:    Color:-1    Parents:6    distance2source:4
10:    Color:1    Parents:0    distance2source:-1
2 4 5 6 3 8
10 10 2 3 5
1:    Color:1    Parents:0    distance2source:-1
2:    Color:1    Parents:0    distance2source:-1
3:    Color:1    Parents:0    distance2source:-1
4:    Color:1    Parents:0    distance2source:-1
5:    Color:1    Parents:0    distance2source:-1
6:    Color:1    Parents:0    distance2source:-1
7:    Color:1    Parents:0    distance2source:-1
8:    Color:1    Parents:0    distance2source:-1
9:    Color:1    Parents:0    distance2source:-1
10:    Color:1    Parents:0    distance2source:-1
*/