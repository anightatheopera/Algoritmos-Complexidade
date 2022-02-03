int BFS(Grafo g, int or, int vis[]){
    vis[NV] = {0};
    v[or] = 1;
    int i = 1, x, front = end = 0;
    int queue[NV] = {0};
    queue[end++] = or;
    while(front != end){
        x = queue[front++];
        for(Nodo a = g[or]; a!=NULL; a=a->prox){
            vis[a->dest] = 1;
            queue[end++] = a->dest;
            i++
        }
    }
    return i;
}

int travessias(Grafo g, int o, int v[]){
    return BFS(g,o,v);
}

void fechoT(Grafo g, int t[N][N]){
    int v[N] = {0};
    for(int i = 0; i<N; i++){
        travessia(g,i,v);
        for(Nodo a = g[i]; a!=NULL; a=a->prox)
            for(int j = 0; j<N; j++)
                t[i][j] = vis[i];
    }
}