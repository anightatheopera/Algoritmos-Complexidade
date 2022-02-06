typedef struct aresta {
    int dest;
    int peso;
    struct aresta *prox;
} *Grafo [N];

int pesoC (Grafo g, int V[], int k){
    int peso = 0;
    for(int i = 0; i < k; i++){
        for(struct aresta* a = g[i]; a != NULL; a = a->prox){
            if(V[i+1] == a->dest)
                peso += a->peso;
        }
    }
    return peso;
}