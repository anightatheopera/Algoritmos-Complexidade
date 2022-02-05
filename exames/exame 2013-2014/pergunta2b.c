#include <stdlib.h>
#include <stdio.h>

#define NV 3
typedef struct aresta {
    int dest; 
    int custo;
    struct aresta *prox;
} *LAdj, *GrafoL [NV];

int checkAdj(GrafoL g, int or, int dest){
    LAdj a = g[dest];
    while(a!=NULL){
        if(a->dest == or) return 1;
        else a = a->prox;
    }
    return 0;
}

int undirected(GrafoL g){
    for(int i = 0; i<NV; i++){
        for(LAdj a = g[i]; a != NULL; a = a->prox){
            int dest = a->dest;
            if(checkAdj(g,i,dest)== 0) return 0;
        }
    }
    return 1;
}
