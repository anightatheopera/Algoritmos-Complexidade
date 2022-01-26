#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define Size 5

typedef struct nodo {
    char *chave;
    int ocorr;
    struct nodo *prox;
} Nodo, *THash [Size];

unsigned hash(char *str){
    unsigned hash = 5381;
    int c;
    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    return hash % Size; // alterado aqui por conveniência
}

void initEmpty (THash t){
    for(int i = 0; i < Size; i++)
        t[i] = NULL;
}

void add(char *s, THash t){
    int ind = hash(s);
    if(ind >= Size) return;
    Nodo** aux;
    for(aux=&(t[ind]); *aux != NULL; aux = &(*aux)->prox){
        if(!strcmp(s,(*aux)->chave)){
            (*aux)->ocorr++;
            return;

        }
    }
    (*aux) = malloc(sizeof(struct nodo));
    (*aux)->chave = s;
    (*aux)->ocorr = 1;
}

void printHash(THash t, int n){
    THash aux;
    for (int i = 0; i < n; i++){
        for(aux[i]=t[i]; aux[i] != NULL; aux[i] = aux[i]->prox){
            printf("string: %s \n", aux[i]->chave);
            printf("ocorr: %d ", aux[i]->ocorr);
            printf("\n");
        }
    } 
}

int lookup(char *s, THash t){
    int ind = hash(s);
    Nodo **aux;
    for(aux=&(t[ind]); *aux != NULL; aux = &(*aux)->prox){
        if(!strcmp((*aux)->chave,s)){
            return ((*aux)->ocorr);
        }
    }
    return 0;
}

int remover(char *s, THash t){
    int ind = hash(s);
    Nodo **aux;
    for(aux=&(t[ind]); *aux != NULL; aux = &(*aux)->prox){
        if(!strcmp((*aux)->chave,s)){
            (*aux)->ocorr--;
            if((*aux)->ocorr == 0){
                Nodo* tmp = *aux;
                *aux = (*aux)->prox;
                free(tmp);
                return 0;
            }
            else return (*aux)->ocorr;
        }
    }
    return -1;
}

int main(){
    THash t;
    initEmpty(t);
    add("ola",t);
    add("adeus",t);
    add("yuh",t);
    add("ola",t);
    add("ola",t);
    remover("yuh",t);
    printHash(t,3);
    //int look = lookup("yuh",t);
    //printf("resultado look up: %d", look);
    return 0;
}