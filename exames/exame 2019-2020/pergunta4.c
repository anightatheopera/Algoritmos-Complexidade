typedef int GraphM[MAX][MAX];
struct edge {
    int dest;
    struct edge *next;
};
typedef struct edge *GraphL[MAX];

int DFS(GrafoM g, int or, int vis[], int n){
    if(vir[or]) return 0;
    vis[or] = 1; int a = 1;
    for(int i = 0; i < n; i++){
        if(g[or][i]!=0)
            a+=DFS(g,i,vis,n);
    }
    return a;
}

int count_Reachable(GrafoM g, int or, int n){
    int vis[n] = {0};
    return DFS(g,or,vis,n) - 1;
}