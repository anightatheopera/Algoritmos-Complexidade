#include <stdlib.h>
#include <stdio.h>

#define NV 6
typedef struct aresta {
    int dest; 
    int custo;
    struct aresta *prox;
} *LAdj, *GrafoL [NV];

typedef int GrafoM [NV][NV];

GrafoM teste = {
    {0, 2, 7, 0, 0, 0},
    {0, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 0, 1},
    {5, 0, 0, 0, 8, 0},
    {3, 0, 0, 0, 0, 0},
    {4, 0, 0, 3, 2, 0}
               };

// funções de dar print
void printGrafoL(GrafoL g) {
    int i;
    LAdj aux;
    for (i=0; i<NV; i++) {
        printf("%d : ", i);
    for (aux = g[i]; aux != NULL; aux = aux->prox)
        printf("%d(%d), ", aux->dest, aux->custo);
    printf("\n");
    }
}

void printGrafoM(GrafoM g) {
    int i, j;
    printf("\t");
    for (j=0; j<NV; j++) printf("%d:\t", j);
    printf("\n");
    for (i=0; i<NV; i++) {
        printf("%d :\t", i);
        for (j=0; j<NV; j++) {
            printf("%d,\t", g[i][j]);
        }
        printf("\n");
    }
}

void printArray(int arr[], int n){
    for(int i = 0; i<n; i++){
        printf("%d ,",arr[i]);
    }
    printf("\n");
}
///////////////////////

//funçoes auxiliares///
void initGrafoL(GrafoL g) {
    int i;
    for (i=0; i<NV; i++)
        g[i] = NULL;
}

void initGrafoM(GrafoM g){
    for(int i = 0; i < NV; i++)
        g[i][i] = 0;
}

LAdj append(int dest, int custo, LAdj cauda){
    LAdj novo = malloc(sizeof(struct aresta));
    novo->dest = dest;
    novo->custo = custo;
    novo->prox = cauda;
    return novo;
}

int maxInArray(int arr[], int n){
    int i;
    int max = arr[0];
    for (i = 1; i < n; i++)
        if (arr[i] > max)
            max = arr[i];
    return max;
}

void color(GrafoL g, int cor[]){
    int c = 1;
    int vis[NV];
    for(int i = 0; i < NV; i++){ 
        cor[i]=0;
        vis[i]=0;
    }
    for(int i = 0; i < NV; i++){
        for(LAdj n = g[i]; n != NULL; n = n->prox){
            if(vis[i] != 1){
                cor[i] = c;
                vis[i] = 1;
            }
            if(vis[n->dest] != 1){
                cor[n->dest] = c+1;
                vis[n->dest] = 1;
            }
        }
        c++;
    }
    printArray(cor,NV);
} 
///////////////////////

void fromMat(GrafoM in, GrafoL out){
    initGrafoL(out);
    for(int i = 0; i < NV; i++){
        for(int j = 0; j < NV; j++){
            if(in[i][j] > 0)
                out[i] = append(j,in[i][j],out[i]);
        }
    }
}

void inverte(GrafoL in, GrafoL out){
    initGrafoL(out);
    for(int i=0; i<NV; i++){
        for(LAdj l = in[i]; l != NULL; l = l->prox)
            out[l->dest] = append(i, l->custo, out[l->dest]);
  }
}

int inDegree(GrafoL g){
    int vis[NV];
    for(int i = 0; i<NV; i++) vis[i] = 0;
    for(int i = 0; i<NV; i++){
        for(LAdj n = g[i]; n!=NULL; n=n->prox){
            vis[n->dest]++;
        }
    }
    return maxInArray(vis,NV);
}

int colorOK(GrafoL g, int cor[]){
    LAdj aux;
    for(int i = 0; i < NV; i++){
        for(aux = g[i]; aux != NULL; aux = aux->prox)
            if(cor[i] == cor[g[i]->dest])
                return -1;
    }
    printArray(cor,NV);  
    return 0;
}

int exists(GrafoL g, int from, int to){
    for(LAdj l = g[from]; l != NULL; l = l->prox){
        if(l->dest == to){
            return 1;
        }
    }
  return 0;
}

int homomorfOK (GrafoL g, GrafoL h, int f[]){
    for(int i=0; i<NV; i++){
        for(LAdj l = g[i]; l != NULL; l = l->prox){
            if(!exists(g, f[i], f[h[i]->dest])) return 0;
        }
    }
    return 1;
}

int main(){
    //printf("grafo em matriz \n");
    //printGrafoM(teste);
    //printf("\n");
    GrafoL g, g2;
    fromMat(teste,g);
    printGrafoL(g);
    //int aux[NV] = {1,2,2,3,4,5};
    //int a = colorOK(g,aux);
    //printf("as cores estao assim = %d",a);
    //inverte(g,g2);
    //printGrafoL(g2);
    return 0;
}
