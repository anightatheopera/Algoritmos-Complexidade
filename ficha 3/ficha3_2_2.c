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
    } 
    else if(t[ind].status == Free){
        t[ind].status = Used;
        t[ind].ocorr = 1;
        t[ind].chave = malloc(sizeof(s));
        strcpy(t[ind].chave,s);
    }
}

void addDel(char *s, THash t){
    int ind = where(s);
    if(lookup(s,t)){
        t[ind].ocorr++;
        t[ind].status = Del;
    } 
    else if(t[ind].status == Free){
        t[ind].status = Del;
        t[ind].ocorr = 1;
        t[ind].chave = malloc(sizeof(s));
        strcpy(t[ind].chave,s);
    }
}

int remover(char *s, THash t){
    int ind = where(s);
    if(lookup(s,t) && t[ind].ocorr==1){
       t[ind].chave = NULL;
       t[ind].ocorr = 0;
       t[ind].status = Free;
       return 0; 
    }
    if(lookup(s,t) && t[ind].ocorr>1){
        t[ind].ocorr--;
        return t[ind].ocorr;
    }
}

int garb_collection(THash t){
    int i;
    for(i = 0; i<Size; i++){
        if(t[i].status == Del)
            remover(t[i].chave,t);
    }
    return i;
}

void printHash(THash t, int n){
    for (int i = 0; i < n; i++){
        printf("string: %s, ocorr: %d, estado : %d \n", 
                t[i].chave, t[i].ocorr, t[i].status);
    } 
}

int main(){
    THash t;
    initEmpty(t);
    add("yuh",t);
    add("ola",t);
    addDel("teste",t);
    add("adeefeu",t);
    add("yuh",t);
    remover("adeefeu",t);
    garb_collection(t);
    printHash(t,Size);
    return 0;
}