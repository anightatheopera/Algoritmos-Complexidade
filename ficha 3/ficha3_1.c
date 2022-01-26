#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Max 10
typedef struct pQueue {
    int valores [Max];
    int tamanho;
} PriorityQueue;

int esq(int n){
    return 2*n+1;
}

int dir(int n){
    return 2*n+2;
}

int pai(int n){
    return (n-1)/2;
}

void swap(int h[], int xp, int yp){
    int temp = h[xp];
    h[xp] = h[yp];
    h[yp] = temp;
}

void bubbleUp(int i, int h[]){
    while(i>0 && h[i]<h[pai(i)]){
        swap(h,i,pai(i));
        i = pai(i);
    }
}

void bubbleDown(int i, int h[], int n){
    while( (esq(i) < n && h[i] > h[esq(i)]) 
            || (dir(i) < n && h[i] > h[dir(i)])){
        if(dir(i) >= n || h[esq(i)] < h[dir(i)]){
            swap(h, i, esq(i));
            i = esq(i);
        } else {
            swap(h, i, dir(i));
            i = dir(i);
        }
    }
}

void empty(PriorityQueue* pq){
    *pq = (PriorityQueue){0};
}

int isEmpty(PriorityQueue *q){
    return q->tamanho;
}

int add(int x, PriorityQueue *q){
    if(q->tamanho==Max) return 1;
    q->valores[q->tamanho] = x;
    q->tamanho++;
    return 0;
}

int remover(PriorityQueue *q, int *rem){
    if(isEmpty(q)) return 1;

    *rem = q->valores[0];
    q->valores[0] = q->valores[q->tamanho-1];
    q->tamanho--;
    bubbleDown(0,q->valores,q->tamanho);

    return 0;
}

void teste(PriorityQueue *q){
    add(1,q);
    add(2,q);
    add(3,q);
}

// top-down
void heapify1(int v[], int N){
    for (int i = 0; i < N; i++){
        bubbleUp(i,v);
    }
}

// bottom-up
void heapify2(int v[], int N){
    for (int i = N-1; i > -1; i--){
        bubbleDown(i,v,N);
    }   
}

int heap_pop(int h[], int N){
    swap(h, 0, N-1);
    bubbleDown(0,h,N-1);
    return h[N-1];
}

void ordenaHeap(int h[], int N){
    for(int i = 1; i < N; i++){
        swap(h, 0, N-i);
        bubbleDown(0,h,N-i);
    }
}


int* sequencia(int v[], int N, int k){
    int *aux = malloc(k*sizeof(int));
    for (int i = 0; i < k; i++)
        aux[i] = v[i];
    heapify1(aux,k);
    for(int i = k; i < N; i++){
        if(v[i] > aux[0]){
            heap_pop(aux, k);
            aux[k-1] = v[i];
            bubbleUp(k-1, aux);
        }
    }
    return aux;
}

/*
soluçao acima:
O(N)
*/


#define Size2 10
#define Free 0
#define Used 1
#define Del 2
typedef struct bucket {
    int status; // Free | Used | Del
    char *chave; 
    int ocorr;
} Bucket, THash2 [Size2];

int where(char *s){
    unsigned n = hash(s);
    return n%Size2;
}

void initEmpty2 (THash2 t){
    for(int i=0; i<Size2; i++){
        t[i].status = 0;
        t[i].chave = NULL;
        t[i].ocorr = 0;
    }
}

int lookup2(char *s, THash2 t){
    int i = where(s);
    if(t[i].chave && !strcmp(t[i].chave,s)) return t[i].ocorr;
    else return 0;
}

void add2(char *s, THash2 t){
    int ind = where(s);
    if(lookup2(s,t)){ 
        t[ind].status = Used;
        t[ind].ocorr++;
    }
    else if(t[ind].status == Free){
        t[ind].status = Used;
        t[ind].ocorr = 1;
        t[ind].chave = s;
    }
}


void remove2(char *s, THash2 t){
    if(lookup2(s,t)){
        int ind = where(s);
        int oc = --t[ind].ocorr;
        if(!oc) t[ind].status = Free;
    }
}

void garb_collection (THash2 t){
    for (int i = 0; i < Size2; i++){
        if(t[i].status==Del){ 
            remove2(t[i].chave,t);
        } 
    }
}

void set_Delete(char *s, THash2 t){
    int ind = where(s);
    t[ind].status = Del;
}

int main(){
    PriorityQueue pq = (PriorityQueue){.valores = {10,15,11,16,22}, .tamanho = 0};
    teste(&pq);
    remover(&pq,pq.valores);
    //int *aux = sequencia(minHeap,7,3);
    for(int i=0;i<Max;i++){
        printf("%d ", pq.valores[i]);
    }
    return 0;
}