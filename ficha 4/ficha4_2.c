#include <stdlib.h>
#include <stdio.h>

#define NV 6
typedef struct aresta {
    int dest; 
    int custo;
    struct aresta *prox;
} *LAdj, *GrafoL [NV];

typedef int GrafoM [NV][NV];

//matrizes de teste
GrafoM teste = {
    {0, 2, 7, 0, 0, 0},
    {0, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 0, 1},
    {5, 0, 0, 0, 8, 0},
    {3, 0, 0, 0, 0, 0},
    {4, 0, 0, 3, 2, 0}
               };

GrafoM norient = {
    {0, 0, 0, 5, 3, 0},
    {0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 1},
    {5, 0, 0, 0, 8, 0},
    {3, 0, 0, 8, 0, 0},
    {0, 0, 1, 0, 0, 0}
               };

GrafoM acic = {
    {0, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 1},
    {0, 0, 0, 0, 8, 0},
    {3, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0}
               };
///////////////////

//funçoes de procura
int DFRec(GrafoL g, int or, int v[], int p[], int l[]){
    int i = 1; LAdj a;
    v[or]=-1;
    for (a=g[or]; a!=NULL; a=a->prox){
        if (!v[a->dest]){
            p[a->dest] = or;
            l[a->dest] = 1+l[or];
            i+=DFRec(g,a->dest,v,p,l);
        }
    }
    v[or]=1;
    return i;
}

int DF(GrafoL g, int or, int v[], int p[], int l[]){
    int i;
    for (i=0; i<NV; i++) {
        v[i]=0;
        p[i] = -1;
        l[i] = -1;
    }
    p[or] = -1; l[or] = 0;
    return DFRec (g,or,v,p,l);
}


int BF (GrafoL g, int or, int v[], int p[], int l[]){
    int i, x; LAdj a;
    int q[NV], front, end;
    for (i=0; i<NV; i++) {
        v[i]=0;
        p[i] = -1;
        l[i] = -1;
    }
    front = end = 0;
    q[end++] = or; //enqueue
    v[or] = 1; p[or]=-1;l[or]=0;
    i=1;
    while (front != end){
        x = q[front++]; //dequeue
        for (a=g[x]; a!=NULL; a=a->prox)
            if (!v[a->dest]) {
	            i++;
	            v[a->dest]=1;
	            p[a->dest]=x;
	            l[a->dest]=1+l[x];
	            q[end++]=a->dest; //enqueue
            }
  }
  return i;
}
////////////////////               

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

//funçoes auxiliares
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

int maxInd(int arr[], int n){
    int i, ind = 0;
    int max = arr[0];
    for (i = 1; i < n; i++)
        if (arr[i] > max){
            max = arr[i];
            ind = i;
        }
    return ind;
}

void fromMat(GrafoM in, GrafoL out){
    initGrafoL(out);
    for(int i = 0; i < NV; i++){
        for(int j = 0; j < NV; j++){
            if(in[i][j] > 0)
                out[i] = append(j,in[i][j],out[i]);
        }
    }
}

int elem(int arr[], int x, int n){
    for(int i = 0; i < n; i++){
        if(arr[i] == x) return 0;
    }
    return 1;
}

int root(GrafoL g, int v, int vis[NV]){
    for(LAdj a = g[v]; a != NULL; a = a->prox){
        if(!vis[a->dest]){
            return 0;
        }
    }
    return 1;
}
////////////////////

int maisLonga(GrafoL g, int or, int p[]){
    int pai[NV], len[NV], vis[NV];
    for(int i = 0; i<NV; i++) p[i] = -1;
    BF(g,or,vis,pai,len);
    int ind = maxInd(len,NV);
    int dist = maxInArray(len,NV);
    int a = dist;
    p[a--] = ind;
    while (pai[ind]>=0) {
        ind = pai[ind];
        p[a--] = ind;
    }
    return dist;
}

int componentes (GrafoL g, int c[]) {
    int comp, orig = 0, i, v[NV], p[NV], l[NV];
    DF(g, 0, c, p, l);
    comp = 1; 
    while (orig < NV){
        for (orig=0; c[orig] && orig < NV; orig++);
        if  (orig < NV) {
            DF(g, orig, v, p, l); 
            comp++; 
            for (i=0; i<NV; i++)
                if (v[i]) c[i]=comp;
        }
    } 
    return comp;
}

int ordTop(GrafoL g, int ord[]){
    int vis[NV] = {0};
    int ord_i = NV-1;
    while(ord_i >= 0){
        for(int i=0; i<NV; i++){
            if(!vis[i] && root(g, i, vis)){
                vis[i] = 1;
                ord[ord_i--] = i;
            }
        }
    }
    return ord_i;
}


int main(){
    GrafoL g;
    int c[NV] = {0};
    fromMat(acic,g);
    printf("%d\n",ordTop(g,c));
    printArray(c,NV);
    return 0;
}