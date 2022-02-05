#include <stdlib.h>
#include <stdio.h>

#define NV 3
typedef struct aresta {
    int dest; 
    int custo;
    struct aresta *prox;
} *LAdj, *GrafoL [NV];

int DFSRec(GrafoL g, int or, int vis[]){
    if(vis[or]) return 0;
    vis[or] = 1;
    int i = 1;
    for(LAdj a = g[or]; a!=NULL; a = a->prox)
        i += DFSRec(g,a->dest,vis);
    return i;
}

int DFS(GrafoL g, int or){
    int vis[NV] = {0};
    return (NV == DFSRec(g,or,vis)); // 1 se for ciclico 
}

//outra opçao

int BFS(GrafoL g, int or, int vis[]){
    for(int i = 0; i < NV; vis[i]=0, i++);
    int i = 1, x;
    int front = 0, end = 0;
    int queue[NV] = {0};
    queue[end++] = or;
    while(front!=end){
        x = queue[front++];
        for(LAdj a = g[x]; a!=NULL; a=a->prox){
            vis[a->dest] = 1;
            queue[front++] = a->dest;
            i++;
        }
    }
    return (i==NV);
}