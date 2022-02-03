typedef int GraphM[MAX][MAX];
struct edge {
    int dest;
    struct edge *next;
};
typedef struct edge *GraphL[MAX];

int DFSRec(GraphL g, int or, int vis[], int n){
    if(vis[or]) return 0;
    vis[or] = 1;
    int a = 1;
    for(struct edge aux = g[or]; aux!=NULL; aux=aux->prox)
        a+=DFSRec(g,a->dest,vis,n);
    return a;
}

int DFS(GrafoL g, int or, int n){
    int vis[n] = {0};
    return DFSRec(g,or,vis,n);
}

int stronglyConnected(GraphL g, int n){
    for(int i = 0; i < n; i++)
        if(DFS(g,i,n)!=n)
            return 0;
    return 1;
}