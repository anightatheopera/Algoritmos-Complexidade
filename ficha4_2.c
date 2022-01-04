#include"ficha4.c"

int len[4] = {0,1,1,1};

GrafoM norient = {
    {0, 11, 12, 13},
    {11, 0, 16, 17},
    {12, 16, 0, 20},
    {13, 17, 20, 0}
               };

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


int BF(GrafoL g, int or, int v[], int p[], int l[]){
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
        for (a=g[x]; a!=NULL; a=a->prox){
            if (v[a->dest]){
                i++;
                v[a->dest]=1;
                p[a->dest]=x;
                l[a->dest]=1+l[x];
                q[end++]=a->dest; //enqueue
            }
        }
    }
    return i;
}

int maisLonga(GrafoL g, int or, int p[]) {
    int d, v, i, vis[NV], pai[NV], l[NV];
    BF(g, or, vis, pai, l);
    // encontrar (um dos) vertices mais distantes 
    d = 0; v = or; 
    for (i=0; i<NV; i++) 
        if (l[i]>d) { d=l[i]; v=i; }
    // preencher array do caminho
    i = d;
    p[i--] = v;
    while (pai[v]>=0) {
        v = pai[v];
        p[i--] = v;
    }
    return d;
}

int componentes (GrafoL g, int c[]) {
    int comp, orig, i, v[NV], p[NV], l[NV];
    // primeira componente: usa c[] como array visitados...
    DF(g, 0, c, p, l);
    comp = 1;
    do {
        for (orig=0; c[orig] && orig < NV; orig++); // primeiro 0 em c[]
        if (orig < NV) {
            DF(g, orig, v, p, l);
            comp++;
            for (i=0; i<NV; i++)
                if (v[i]) c[i]=comp;
        }
    } while (orig < NV);
    return comp;
}

int main(){
    GrafoL yuh = {};
    int p[NV];
    //int v[NV];
    fromMat(norient,yuh);
    componentes(yuh,p);
    //fromMat(teste,yuh);
    //printf("%d mais longa \n", BF(yuh,0,v,p,len));
    //printf("%d mais longa \n", BF(yuh,3,v,p,len));
    return 0;
}