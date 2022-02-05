struct btree {​​  
    int info;​​
    int weight;​​  
    struct btree *left, *right;
​​};​​
typedef struct btree *BTree;

int checkweight(BTree t){
    if(t == NULL)
        return 1;
    return t->weight == (t->left != NULL ? t->left->weigth : 0) + (t->right != NULL ? t->right->weight : 0) + 1
    && checkWeight(t->left)
    && checkWeight(t->right);   