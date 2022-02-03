
typedef struct edge{
    int dest;
    struct edge *next;
​​} *LAdj;

typedef struct edge *GraphL[MAX];

int BFS(GraphL g, int or, int vis[]){
    int i, x;
    vis[MAX] = {0};
    int queue[MAX] = {0};
    int front = end = 0;
    q[end++] = or;
    i = 1;
    while(front != end){
        x = queue[front++];
        for(LAdj a = g[x]; a!=NULL; a = a->prox){
            i++;
            vis[a->dest] = 1;
            q[end++] = a->dest;
        }
    }
    return i;
}

int shortestBy(GraphL g, int s, int d, int i){
    int vis[MAX] = {0};
    BFS(g,s,vis);
    if(!vis[d]) return -1;
    if(vis[d] && !vis[i]) return 0;
    return 1;
}