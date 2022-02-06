typedef struct node {
    int value;
    struct node *left, *right;
} Node, *BTree;

int heapOK(BTree a){
    if(!a) return 1;
    return ((a->left && a->value < a->esq->value)
        &&  (a->right && a->value < a->right->value)
        &&  heapOK(a->left)
        &&  heapOK(a->right);
}