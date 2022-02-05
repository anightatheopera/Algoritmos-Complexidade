typedef struct llint {
    int value;
    struct llint *next;
} *LInt;

typedef struct avl {
    int value;
    int bal, deleted;
    struct avl *left, *right;
} *AVL;

AVL fromList(LInt l, int n){
    int p = 0; LInt aux = l;
    for(int i = 0; i < (n-1)/2; i++, aux=aux->next);
    p = aux->value;
    AVL a = (AVL) malloc(sizeof(struct avl));
    a->value = p;
    a->left = fromList(l,n-p);
    l = aux->next;
    a->right = fromList(l,n-p-1);
    return a;
}