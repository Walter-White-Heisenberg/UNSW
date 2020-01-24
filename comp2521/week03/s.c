int BSTreeNumLeaves (BSTree t)
{
	if(t == NULL)
	    return 0; 
	else if(t->left == NULL && t->right == NULL)
	    return 1;
	else
	    return BSTreeNumLeaves(t->left) + BSTreeNumLeaves(t->right);
}



void BSTreeLevelOrder (BSTree t)
{
	if(t == NULL)
	    return;
	Queue QQQ = newQueue();
	QueueJoin(QQQ, t);
	Item m;
	while(QueueIsEmpty(QQQ) != true){
	    m = QueueLeave (QQQ);
	    printf("%d ",m->value);   
	    if(t->left != NULL)
	        QueueJoin (QQQ, m->left);
	    if(t->right != NULL){
	        QueueJoin (QQQ, m->right);
	    }
	}
	dropQueue(QQQ);
	return; 
}
