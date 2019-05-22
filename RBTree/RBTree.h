#include <fstream>
#include <iostream>

#define compLT(a,b) (a < b)
#define compEQ(a,b) (a == b)

typedef enum { BLACK, RED } nodeColor;

template <class T>

struct RBNode {
	struct RBNode *left;         /* left child */
	struct RBNode *right;        /* right child */
	struct RBNode *parent;       /* parent */
	nodeColor color;            /* node color (BLACK, RED) */
	T data;                     /* data stored in node */
};

template <class T>
class RBTree {
public:
	RBTree();
	~RBTree();
	RBNode<T>* null;
	RBNode<T>* root;

	void RBinsert(T);
	void RBdelete(T);

	RBNode<T>* getRoot() { return root; }

private:
	bool treeCreated = false;


	RBNode<T>* minimum(RBNode<T>*);

	void RBinsert(T);
	void RBinsertFixup(RBNode<T>*);
	void RBdeleteFixup(RBNode<T>*);
	void transplant(RBNode<T>*, RBNode<T>*);

	void leftRotate(RBNode<T>*);
	void rightRotate(RBNode<T>*);

	void deleteHelper(RBNode<T>* temp);

	RBNode<T>* search(T);
};