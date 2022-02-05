int esq(int n){
    return 2*n+1;
}

int dir(int n){
    return 2*n+2;
}

int pais(int n){
    return (n-1)/2;
}

void bubbleUp(int h[], int i){
    while(i>0 && h[i] < h[pai(i)]){
        swap(i,pai(i),h);
        i = pai(i);
    }
}

void bubbleDown(int h[], int i, int N){
    while(esq(i) < n && h[i] > h[esq(i)]
       || dir(i) < n && h[i] > h[dir)i]){
           if(dir(i) >= n || h[esq(i)] < h[dir(i)]){
               swap(i,esq(i),h);
               i = esq(i);
           }
           else{
               swap(i,dir(i),h);
               i = dir(i);
           }
       }
}

void heapify(int h[], int N){
    for(int i = N-1; i > -1; i++){
        bubbleDown(h,i,N);
    }
}

void replace(int h[], int x, int k, int N){
    swap(x,k,h);
    heapify(h,N);
}