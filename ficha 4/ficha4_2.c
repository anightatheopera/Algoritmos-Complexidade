#include"ficha4.c"

int len[4] = {0,1,1,1};

GrafoM norient = {
    {0, 11, 12, 13},
    {11, 0, 16, 17},
    {12, 16, 0, 20},
    {13, 17, 20, 0}
               };

GrafoM teste3 = {
//   a  b  c  d  e  f 
    {0, 1, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0},
    {1, 0, 0, 0, 1, 0},
    {1, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 1},
    {0, 0, 0, 1, 0, 0},
               };  

GrafoM teste4 = {
//   a  b  c  d  e  f 
    {0, 1, 1, 1, 1, 0},
    {1, 0, 0, 1, 0, 0},
    {1, 0, 0, 0, 1, 0},
    {1, 1, 0, 0, 0, 1},
    {1, 0, 1, 0, 0, 1},
    {0, 0, 0, 1, 1, 0},
               };              

GrafoM acicl = {
//   a  b  c  d  e  f 
    {0, 1, 0, 1, 1, 0},
    {0, 0, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 1},
    {0, 0, 1, 0, 0, 0},
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


int BF (GrafoL g, int or, int v[], int p[], int l[]){
    int i, x; LAdj a;
    int q[NV], front, end;
    for (i=0; i<NV; i++) {
        v[i]=0;
        p[i] = -10;
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

void test_BF(GrafoL g, GrafoM h) {
    int i, n, v[NV], p[NV], l[NV];
    printf("----------------------\nTESTE BF:\n=========\n");
    fromMat(h,g);
    n = BF(g, 0, v, p, l);
    printf("Visitados = %d\n", n);
    for (i=0; i<NV; i++)
        printf("v[%d] = %d\tp[%d] = %d\tl[%d] = %d\n", i, v[i], i, p[i], i, l[i]);
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
    int comp, orig = 0, i, v[NV], p[NV], l[NV];
    // primeira componente: usa c[] como array visitados (serve de inicialização)
    BF(g, 0, c, p, l);
    comp = 1; //componentes já processadas
    while (orig < NV){
        for (orig=0; c[orig] && orig < NV; orig++); // primeiro 0 em c[]
        if (orig < NV) {
            BF(g, orig, v, p, l); //obs: agora v[] já é um vector distinto de c[]
            comp++; 
            // copia informação dos visitados para array c[]
            for (i=0; i<NV; i++)
                if (v[i]) c[i]=comp;
        }
    } 
    return comp;
}


int OrdTopRec (GrafoL g, int n, int or, int v[], int ord[]) {
  LAdj a;
  v[or] = -1;
  for (a=g[or]; a; a=a->prox) {
    if (v[a->dest]==-1) 
        return -1;
    if (!v[a->dest]){
      n = OrdTopRec(g,n,a->dest,v,ord);
      if (n<0) return -1;
    }
  } 
  v[or] = 1;
  ord[n] = or;
  return n+1;
}

int ordTop (GrafoL g, int ord[]) {
    int v[NV], o, n, i;
    for (i=0; i<NV; i++) v[i]=0;
    n = 0;
    o = 0;
    do {
        n = OrdTopRec(g,n,o,v,ord);
        if (n < 0) return 1;
        if (n < NV)
            for (o=1; v[o] && o<NV; o++);
    } while (n < NV);
    return 0;
}

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


int main(){
    GrafoL yuh = {};
    //int p[NV];
    //int v[NV];
    fromMat(acicl,yuh);
    printGrafoL(yuh);
    test_BF(yuh,acicl);
    //int a = componentes(yuh,p);
    //printGrafoL(yuh);
    //componentes(yuh,p);
    //fromMat(teste,yuh);
    return 0;
}