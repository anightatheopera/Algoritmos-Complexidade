int dijkstraSP (Grafo g, int v, int pesos[], int pais[]);

int aproxMeio(Grafo g, int o, int d){
    int pesos[NV] = {0};
    int pais[NV] = {0};
    dijkstra(g, o, pesos, pais);
    if(pais[d] == -1)
        return -1;
    int path[NV] = {0};
    int path_size = 0;
    for(int curr = d; curr != o; path[path_size++] = curr)
        curr = pais[curr];
    return path[path_size/2];
}