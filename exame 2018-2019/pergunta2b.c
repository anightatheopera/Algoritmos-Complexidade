typedef struct avlNode {
    int valor;
    int bal; //1:Esq, -1:Dir
    struct avlNode *esq, *dir;
} *AVL;

int converte(AVL a){
    if(a == NULL)
        return 0;
    int aleft = converte(a->left);
    int aright = converte(a->right);
    a->bal = aleft > aright ? aleft : aright;
    return a->bal + 1;
}