#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define Size 10
#define Free 0
#define Used 1
#define Del 2

typedef struct bucket {
    int status; // Free | Used | Del
    char *chave;
    int ocorr;
    int colisao;
} Nodo, THash [Size];

unsigned hash(char *str){
    unsigned hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    return hash % Size; // alterado aqui por conveniência
}

int where(char *s){
    return hash(s);
}

void initEmpty(THash t){
    for(int i=0; i<Size; i++){
        t[i].status = Free;
        t[i].chave = NULL;
        t[i].ocorr = 0;
        t[i].colisao = 0;
    }
}

int lookup(char *s, THash t){
    int i = where(s);
    if(t[i].chave && !strcmp(t[i].chave,s)){
        return t[i].ocorr;
    } 
    else return 0;
}

void add(char *s, THash t){
    int ind = where(s);
    if(lookup(s,t)){
        t[ind].ocorr++;
        t[ind].status = Used;
        t[ind].colisao++;
    } 
    else if(t[ind].status == Free){
        t[ind].status = Used;
        t[ind].ocorr = 1;
        t[ind].chave = malloc(sizeof(s));
        strcpy(t[ind].chave,s);
    }
}

void printHash(THash t, int n){
    for (int i = 0; i < n; i++){
        printf("string: %s, ocorr: %d, estado : %d, n colisoes: %d \n", 
                t[i].chave, t[i].ocorr, t[i].status, t[i].colisao);
    } 
}

int main(){
    THash t;
    initEmpty(t);
    add("yuh",t);
    add("ola",t);
    add("adeefeu",t);
    add("yuh",t);
    printHash(t,Size);
    return 0;
}