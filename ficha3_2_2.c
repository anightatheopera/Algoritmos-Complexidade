#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define Size 5
#define Free 0
#define Used 1
#define Del 2

typedef struct bucket {
    int status; // Free | Used | Del
    char *chave;
    int ocorr;
} THash [Size];

unsigned hash(char *str){
    unsigned hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    return hash % Size; // alterado aqui por conveniência
}

int where(char *s){
    int a = (int) hash(s);
    return a%Size;
}

void initEmpty(THash t){
    for(int i=0; i<Size; i++){
        t[i].status = 0;
        t[i].chave = NULL;
        t[i].ocorr = 0;
    }
}

void printHash(THash t, int n){
    for (int i = 0; i < n; i++){
        printf("string: %s, ocorr: %d, estado : %d \n", 
                t[i].chave, t[i].ocorr, t[i].status);
    } 
}

int main(){
    return 0;
}