#define N ...
typedef struct edge {
    int dest;
    struct edge *next;
} *Adjlist;
typedef AdjList Graph [N];

int DFS(Graph g, int or, int vis){
    if(v[or]) return 0;
    v[or] = 1;
    int a = 1;
    for(AdjList aux = g[or]; aux != NULL; aux = aux->next)
        a+=DFS(g,aux->dest,vis);
    return a;
}

int maxcomp(Graph g, int or){
    int vis[N] = {0};
    int max = 0;
    for(int i = 0; i < N; i++){
        int a = 0;
        a = DFS(g,i,vis);
        if(a>max) max = aux;
    }
    return max;
}