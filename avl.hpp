#include "bst.hpp"

template <typename Type>
class AVLtree : public BinarySearchTree<Type>
{
public:
	AVLtree() : BinarySearchTree<Type>() { }
	AVLtree(AdvBranch<Type> *root) : BinarySearchTree<Type>(root) { }
	AdvBranch<Type> *Root() { this->root; }
	void add(Type e);
	void remove(Type e);
	bool check(Type e);
	void print() {
		if (this->root) this->root->inOrderPrint();
	}
};

template <typename Type>
void AVLtree<Type>::add(Type e)
{
	AdvBranch<Type> **t = &this->root, *z = NULL;
	while (*t)
	{
		if ((*t)->data == e)
		{
			cerr << "Error: Unable to add duplicate element\n";
			return;
		}
		z = *t;
		t = (*t)->data > e ? &(*t)->left : &(*t)->right;
	}
	*t = new AdvBranch<Type>(e, z);
	if (this->autoUpdateHeight) this->root->updateHeight();
}
