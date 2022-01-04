#include <stdlib.h>
#include <stdio.h>

#define NV 4
typedef struct aresta {
    int dest; 
    int custo;
    struct aresta *prox;
} *LAdj, *GrafoL [NV];

typedef int GrafoM [NV][NV];

GrafoM teste = {
    {0, 11, 12, 13},
    {0, 0, 16, 17},
    {0, 0, 0, 32},
    {0, 0, 20, 0}
               };

GrafoM teste2 = {
    {1, 0, 1, 0},
    {1, 0, 1, 0},
    {1, 0, 1, 0},
    {1, 0, 1, 0}
               };

LAdj append(int dest, int custo, LAdj cauda){
    LAdj novo = malloc(sizeof(struct aresta));
    novo->dest = dest;
    novo->custo = custo;
    novo->prox = cauda;
    return novo;
}

void fromMat (GrafoM in, GrafoL out){
    for(int i = 0; i < NV; i++){
        for(int j = 0; j < NV; j++){
            if(in[i][j] != 0){
                out[i] = append(j, in[i][j], out[i]);
            }
        }
    }
}

void graphl_debug(GrafoL g){
  for(int i=0; i<NV; i++){
    for(LAdj l = g[i]; l != NULL; l = l->prox)
      printf("%d -> %d (%d)\n", i, l->dest, l->custo);
  }
}


void inverte(GrafoL in, GrafoL out){
  for(int i=0; i<NV; i++){
    for(LAdj l = out[i]; l != NULL; l = l->prox)
      in[l->dest] = append(i, l->custo, in[l->dest]);
  }
}

int inDegree (GrafoL g){
    int max = 0;
    for(int i = 0; i < NV; i++){
        int curr = 0;
        for(LAdj l = g[i]; l != NULL; l = l->prox)
            curr++;
        if(curr > max){
            max = curr;
        }
    }
    return max;
}

int colorOK (GrafoL g, int cor[]){
    int ncores = 0;
    for(int i=0; i<NV; i++){
        for(LAdj l = g[i]; l != NULL; l = l->prox){
            if(cor[i] != cor[l->dest]) ncores++;
            else return 0;
        }
    }
    return ncores;
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
    GrafoL yuh = {0};
    fromMat(teste,yuh);
    //graphl_debug(yuh);
    GrafoL yuh2 = {0};
    fromMat(teste2,yuh2);
    int f[4] = {1,0,1,0};
    int ola = homomorfOK(yuh,yuh2,f);
    printf("%d numero de coisas", ola);
    return 0;
}