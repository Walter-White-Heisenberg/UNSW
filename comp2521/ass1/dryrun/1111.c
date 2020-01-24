


int BSTree leafcount(Tree t){
    if t == NULL return 0;
    return (t->left == NULL && t->right == NULL) ? 1 : leafcount(t->left) + leafcount(t->right);
}

