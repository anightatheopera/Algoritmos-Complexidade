typedef enum balancefactor { LH , EH , RH } BalanceFactor;
typedef struct treenode {
    BalanceFactor bf;      // indicador de equilíbrio AVL
    int entry;             // inteiro guardado no nó
    int n_elems;           // número de elementos desta árvore
    struct treeNode *left, *right;
} *Tree;

Tree rotateLeft(Tree t){
    Tree aux = t->right;
    t->n_elems = (t->left != NULL ? (t->left)->n_elem : 0) + ((t->right) != NULL ? t->right->n_elem : 0) + 1;
    aux->left = t;
    aux->n_elems = (t->left != NULL ? (t->left)->n_elem : 0) + ((t->right) != NULL ? t->right->n_elem : 0) + 1;
    t = aux;
    return aux;
}

int rank(Tree a, int x){
    if(a == NULL)
        return 0;
    if(a->entry <= x)
        return 1 + (a->left != NULL ? a->left->n_elem : 0) + rank(a->right, x);
    return rank(a->left,x);
}
