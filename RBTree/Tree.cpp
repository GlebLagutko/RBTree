#include "RBTree.h"

template <class T>

void RBTree<T>:: leftRotate(RBNode<T> *x) {

	/**************************
	 *  rotate node x to left *
	 **************************/

	RBNode<T> *y = x->right;

	/* establish x->right link */
	x->right = y->left;
	if (y->left != NULL) y->left->parent = x;

	/* establish y->parent link */
	if (y != NULL) y->parent = x->parent;
	if (x->parent) {
		if (x == x->parent->left)
			x->parent->left = y;
		else
			x->parent->right = y;
	}
	else {
		root = y;
	}

	/* link x and y */
	y->left = x;
	if (x != NULL) x->parent = y;
}

template <class T>
void RBTree<T>::rightRotate(RBNode<T> *x) {

	/****************************
	 *  rotate node x to right  *
	 ****************************/

	RBNode<T> *y = x->left;

	/* establish x->left link */
	x->left = y->right;
	if (y->right != NULL) y->right->parent = x;

	/* establish y->parent link */
	if (y != NULL) y->parent = x->parent;
	if (x->parent) {
		if (x == x->parent->right)
			x->parent->right = y;
		else
			x->parent->left = y;
	}
	else {
		root = y;
	}

	/* link x and y */
	y->right = x;
	if (x != NULL) x->parent = y;
}

template <class T>
void RBTree<T>::RBinsertFixup(RBNode<T> *x) {

	/*************************************
	 *  maintain Red-Black tree balance  *
	 *  after inserting node x           *
	 *************************************/

	 /* check Red-Black properties */
	while (x != root && x->parent->color == RED) {
		/* we have a violation */
		if (x->parent == x->parent->parent->left) {
			RBNode<T> *y = x->parent->parent->right;
			if (y->color == RED) {

				/* uncle is RED */
				x->parent->color = BLACK;
				y->color = BLACK;
				x->parent->parent->color = RED;
				x = x->parent->parent;
			}
			else {

				/* uncle is BLACK */
				if (x == x->parent->right) {
					/* make x a left child */
					x = x->parent;
					leftRotate(x);
				}

				/* recolor and rotate */
				x->parent->color = BLACK;
				x->parent->parent->color = RED;
				rightRotate(x->parent->parent);
			}
		}
		else {

			/* mirror image of above code */
			RBNode<T> *y = x->parent->parent->left;
			if (y->color == RED) {

				/* uncle is RED */
				x->parent->color = BLACK;
				y->color = BLACK;
				x->parent->parent->color = RED;
				x = x->parent->parent;
			}
			else {

				/* uncle is BLACK */
				if (x == x->parent->left) {
					x = x->parent;
					rightRotate(x);
				}
				x->parent->color = BLACK;
				x->parent->parent->color = RED;
				leftRotate(x->parent->parent);
			}
		}
	}
	root->color = BLACK;
}

template <class T>
RBNode<T> RBTree<T>:: *search(T data) {

	/*******************************
	 *  find node containing data  *
	 *******************************/

	RBNode<T> *current = root;
	while (current != NULL)
		if (compEQ(data, current->data))
			return (current);
		else
			current = compLT(data, current->data) ?
			current->left : current->right;
	return(0);
}

template <class T>
void RBTree<T>:: RBinsert(T data) {
	RBNode<T> *current, *parent, *x;

	/***********************************************
	 *  allocate node for data and insert in tree  *
	 ***********************************************/

	 /* find where node belongs */
	current = root;
	parent = 0;
	while (current != NULL) {
		if (compEQ(data, current->data)) return;
		parent = current;
		current = compLT(data, current->data) ?
			current->left : current->right;
	}

	/* setup new node */
	if ((x = malloc(sizeof(*x))) == 0) {
		printf("insufficient memory (insertNode)\n");
		exit(1);
	}
	x->data = data;
	x->parent = parent;
	x->left = NULL;
	x->right = NULL;
	x->color = RED;

	/* insert node in tree */
	if (parent) {
		if (compLT(data, parent->data))
			parent->left = x;
		else
			parent->right = x;
	}
	else {
		root = x;
	}

	insertFixup(x);
}

template <class T>
void RBTree<T>::RBdeleteFixup(RBNode<T> *x) {

	/*************************************
	 *  maintain Red-Black tree balance  *
	 *  after deleting node x            *
	 *************************************/

	while (x != root && x->color == BLACK) {
		if (x == x->parent->left) {
			RBNode<T> *w = x->parent->right;
			if (w->color == RED) {
				w->color = BLACK;
				x->parent->color = RED;
				leftRotate(x->parent);
				w = x->parent->right;
			}
			if (w->left->color == BLACK && w->right->color == BLACK) {
				w->color = RED;
				x = x->parent;
			}
			else 
			{

				if (w->right->color == BLACK) {
					w->left->color = BLACK;
					w->color = RED;
					rightRotate(w);
					w = x->parent->right;
				}
				w->color = x->parent->color;
				x->parent->color = BLACK;
				w->right->color = BLACK;
				leftRotate(x->parent);
				x = root;
			}
		}
		else {
			RBNode<T> *w = x->parent->left;
			if (w->color == RED) {
				w->color = BLACK;
				x->parent->color = RED;
				rightRotate(x->parent);
				w = x->parent->left;
			}
			if (w->right->color == BLACK && w->left->color == BLACK) {
				w->color = RED;
				x = x->parent;
			}
			else {
				if (w->left->color == BLACK) {
					w->right->color = BLACK;
					w->color = RED;
					leftRotate(w);
					w = x->parent->left;
				}
				w->color = x->parent->color;
				x->parent->color = BLACK;
				w->left->color = BLACK;
				rightRotate(x->parent);
				x = root;
			}
		}
	}
	x->color = BLACK;
}

template <class T>
void RBTree<T>:: RBdelete(T data) {
	RBNode<T> *x, *y;
	RBNode<T> z = search(data);
	/*****************************
	 *  delete node z from tree  *
	 *****************************/

	if (!z || z == NULL) return;


	if (z->left == NULL || z->right == NULL) {
		/* y has a NIL node as a child */
		y = z;
	}
	else {
		/* find tree successor with a NIL node as a child */
		y = z->right;
		while (y->left != NULL) y = y->left;
	}

	/* x is y's only child */
	if (y->left != NULL)
		x = y->left;
	else
		x = y->right;

	/* remove y from the parent chain */
	x->parent = y->parent;
	if (y->parent)
		if (y == y->parent->left)
			y->parent->left = x;
		else
			y->parent->right = x;
	else
		root = x;

	if (y != z) z->data = y->data;


	if (y->color == BLACK)
		deleteFixup(x);

	free(y);
}


