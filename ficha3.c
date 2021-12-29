#include <stdio.h>
#include <stdlib.h>

int minHeap[]={10,32,22,15,16,25,30};

#define Max 100
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

void swap(int h[], int xp, int yp)
{
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
    while (i<n && esq(i)<=n && dir(i)<=i){
        if(h[i] > h[esq(i)] && esq(i)){
            swap(h,i,esq(i));
            i = esq(i);
        }
        else if(h[i] > h[dir(i)] && dir(i)){
                swap(h,i,dir(i));
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

int remover(PriorityQueue *q, int *rem) {
    if(q->tamanho == 0) return 1;
    *rem = q->valores[0];
    q->tamanho--;
    for(int i = 0; i < q->tamanho; i++)
      q->valores[i] = q->valores[i+1];
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
    for (int i = N; i > 0; i--){
        bubbleDown(i,v,N);
    }   
}

void ordenaHeap(int h[], int N){
    for(int i = N-1; i > 0; i--){
        for (int j = 0; j < i; j++){
            if(h[i]<h[j]) swap(h,i,j);
        }
        bubbleDown(i,h,N);
    }
}

int main(){
    //PriorityQueue pq = (PriorityQueue){.valores = {1,2,3,4,5,6}, .tamanho = 0};
    //teste(&pq);
    //remover(&pq,pq.valores);
    ordenaHeap(minHeap,7);
    for(int i=0;i<7;i++){
        printf("%d ", minHeap[i]);
    }
}