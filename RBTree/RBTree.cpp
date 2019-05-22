#include <fstream>
#include <iostream>
#include "RBNode.h"




class RBTree {
public:
	RBTree();
	~RBTree();

	void RBwrite(RBNode<int>*);
	void RBread();
	void RBinsert(int);
	void RBdelete(int);

	RBNode<int>* getRoot() { return root; }

private:
	bool treeCreated = false;

	RBNode<int>* null;
	RBNode<int>* root;

	RBNode<int>* minimum(RBNode<int>*);

	void RBinsert(typename RBNode<int>::Color, int);
	void RBinsertFixup(RBNode<int>*);
	void RBdeleteFixup(RBNode<int>*);
	void transplant(RBNode<int>*, RBNode<int>*);

	void leftRotate(RBNode<int>*);
	void rightRotate(RBNode<int>*);

	void deleteHelper(RBNode<int>* temp);

	RBNode<int>* search(int);
};