#include <stdio.h>
#include <stdlib.h>

#define MaxVertices 10  /* maximum number of vertices */
typedef int Vertex;     /* vertices are numbered from 0 to MaxVertices-1 */
typedef struct VNode *PtrToVNode;
struct VNode {
    Vertex Vert;
    PtrToVNode Next;
};
typedef struct GNode *Graph;
struct GNode {
    int NumOfVertices;
    int NumOfEdges;
    PtrToVNode *Array;
};

Graph ReadG(); /* details omitted */

void PrintV( Vertex V )
{
   printf("%d ", V);
}

void StronglyConnectedComponents( Graph G, void (*visit)(Vertex V) );

int main()
{
    Graph G = ReadG();
    StronglyConnectedComponents( G, PrintV );
    return 0;
}

void DFS(Graph G, Vertex V, int * visited) {
    visited[V] = 1;
    PtrToVNode tempRoot = G->Array[V];
    while (tempRoot) {
        if(!visited[tempRoot->Vert]) {
        DFS(G, tempRoot->Vert, visited);
        }
        tempRoot = tempRoot->Next;
    }
}

int judgeConnect(int root, int dest, Graph G) {
    if (root == dest) {
        return 1;
    } else {
        int * visited = (int *)calloc(G->NumOfVertices, sizeof(int));
        DFS(G, root, visited);
        if (visited[dest]) {
            free(visited);
            return 1;
        } else {
            free(visited);
            return 0;
        }
    }
}

void findSCC(int root, Graph G, int * sccRef) {
    int * visited = (int *)calloc(G->NumOfVertices, sizeof(int));
    DFS(G, root, visited);
    for (int i = 0; i < G->NumOfVertices; i ++) {
        if (visited[i] && judgeConnect(i, root, G)) {
            sccRef[i] = 1;
        }
    }
    free(visited);
}

void StronglyConnectedComponents( Graph G, void (*visit)(Vertex V) ) {
    int vertexCnt = G->NumOfVertices;
    int * includeList = (int *)calloc(vertexCnt, sizeof(int));
    int * sccRef = (int *)calloc(vertexCnt, sizeof(int));
    for (int i = 0; i < vertexCnt; i ++) {
        if (!includeList[i]) {
            findSCC(i, G, sccRef);
            for (int i = 0; i < vertexCnt; i ++) {
                if (sccRef[i]) {
                    (*visit)(i);
                }
            }
            printf("\n");
            for (int i = 0; i < vertexCnt; i ++) {
                sccRef[i] = 0;
            }
        }
    }
    free(includeList);
    free(sccRef);
}