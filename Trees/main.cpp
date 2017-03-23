/*
 * nodes with two descendants are pushed twice, nodes with one descendant are pushed once.
 */
template<class T>
void BST<T>::iterativePostOrder() {
	Stack<BSTNode<T>*> travStack;
	BSTNode<T>* p = root, *q = root;
	while(p != 0) {
		for( ; p->left != 0; p = p->left)
			travStack.push(p);
		while(p->right == 0 || p->right == q){
			visit(p);
			q = p;
			if(travStack.empty())
				return;
			p = travStack.pop();
		}
		travStack.push(p); // this is reached if p->right does not equal 0, if node did not have a left leaf, the node was not pushed on the stack. if node has both it is
						   // pushed twice.
		p = p->right;
	}
}

/*
 * the successor member in the previous node i think says something about its children or descendents that it points to on the left or right
 * in order left to right traversal means go to the left most leaf, print it or visit it, and go back up printing them as you go. a successor is above the current node
 * closer to the root. i think predecessor means what i think of as child.  the predecessor successor relationship is inverted from my assumption of what they mean
 * From insert description, a node with a right child has a successor somewhere in its right subtree, a node with no right child has its successor somewhere above it.
 * if a node becomes the right child of another node, it inherits a successor from its parent.  if a node becomes the left child of another node, this parent becomes
 * its successor.
 * a key's predecessor is the key in the rightmost node in the left subtree, its immediate successor is the key in the leftmost node in the right subtree
 */
template<class T>
void ThreadedTree<T>::inorder() {
	ThreadedNode<T> *prev, *p = root;
	if(p != 0){
		while(p != 0) // go to the left most node
			p = p->left;
		while(p != 0){
			visit(p);
			prev = p;
			p = p->right; // go to the right node and
			if(p != 0 && prev->successor == 0) // only if it is a descendant
				while(p->left != 0) // go to the left most node.  other wise visit the successor by another iteration of the while loop.
					p = p->left;
		}
	}
}

/*
 * input 0-9, middle is 4 on first call, 4 is the root, then 0 and 3 are passed and 1 is inserted. then 0 and 0 are passed 0 is inserted, 0 and -1 are passed and method
 * returns.  1 and 0 are passed to second recursive call and method returns, the last call on the stack was where 0 and 3 were first and last.  it returns to call the
 * second balance with 2 and 3 as the parameters which will insert 2.  the insert method ensures the right leaf will be greater than the parent and the left leaf will be
 * less than the parent.
 */
template<class T>
void BST<T>::balance(T data[], int first, int last){
	if(first <= last){
		int middle = (first + last)/2;
		insert(data[middle]);
		balance(data, first, middle-1);
		balance(data, middle+1, last);
	}
}
