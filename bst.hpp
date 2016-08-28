#include "tree.hpp"

template <typename Type>
class BinarySearchTree : public tree<Type>
{
public:
	BinarySearchTree() : tree<Type>() { }
	BinarySearchTree(branch<Type> *root) : tree<Type>(root) { }
	~BinarySearchTree();

	void add(Type e);
	void add(Type a[], size_t size);
	void remove(Type e);
	void remove(Type a[], size_t size);
	bool check(Type e);
	void copyToArrIncOrder(Type A[], size_t &size);
	void copyToArrDecOrder(Type A[], size_t &size);
	void print(bool printAll) {
		if (this->root) this->root->inOrderPrint(printAll);
	}
};

template <typename Type>
void BinarySearchTree<Type>::copyToArrIncOrder(Type A[], size_t &size)
{
	if (this->root)
		this->root->copyToArrIncOrder(A, size);
	else
		size = 0;
}

template <typename Type>
void BinarySearchTree<Type>::copyToArrDecOrder(Type A[], size_t &size)
{
	if (this->root)
		this->root->copyToArrDecOrder(A, size);
	else
		size = 0;
}

template <typename Type>
void BinarySearchTree<Type>::add(Type e)
{
	branch<Type> **t = &this->root;
	while (*t)
	{
		if ((*t)->data == e)
		{
			cerr << "Error: Unable to add duplicate element\n";
			return;
		}
		t = (*t)->data > e ? &(*t)->left : &(*t)->right;
	}
	*t = new branch<Type>(e);
	if (this->autoUpdateHeight && this->root)
		this->root->updateHeight();
}

template <typename Type>
void BinarySearchTree<Type>::add(Type a[], size_t size)
{
	bool autoUpdate = this->autoUpdateHeight;
	this->autoUpdateHeight = false;
	for (size_t i = 0; i < size; ++i)
		this->add(a[i]);
	this->autoUpdateHeight = autoUpdate;
	if (this->autoUpdateHeight && this->root)
		this->root->updateHeight();
}

template <typename Type>
void BinarySearchTree<Type>::remove(Type e)
{
	branch<Type> **t = &this->root;
	while (*t)
	{
		if ((*t)->data == e)
		{
			branch<Type> *z = *t;
			if ((*t)->isLeaf())
				*t = NULL;
			else if ((*t)->isOnlyLeftLinked())
				*t = (*t)->left;
			else if ((*t)->isOnlyRightLinked())
				*t = (*t)->right;
			else
			{
				t = &(*t)->right;
				while ((*t)->left)
					t = &(*t)->left;
				z->data = (*t)->data;
				z = *t;
				*t = (*t)->right;
			}
			delete z;
			if (this->autoUpdateHeight && this->root)
				this->root->updateHeight();
			return;
		}
		t = (*t)->data > e ? &(*t)->left : &(*t)->right;
	}
	cerr << "Error: Element not in the tree\n";
}

template <typename Type>
void BinarySearchTree<Type>::remove(Type a[], size_t size)
{
	bool autoUpdate = this->autoUpdateHeight;
	this->autoUpdateHeight = false;
	for (size_t i = 0; i < size; ++i)
		this->remove(a[i]);
	this->autoUpdateHeight = autoUpdate;
	if (this->autoUpdateHeight && this->root)
		this->root->updateHeight();
}

template <typename Type>
BinarySearchTree<Type>::~BinarySearchTree()
{
	if (this->root)
	{
		if (this->root->left)  this->root->removeAll(&this->root->left);
		if (this->root->right) this->root->removeAll(&this->root->right);
		delete this->root;
		this->root = NULL;
	}
}

template <typename Type>
bool BinarySearchTree<Type>::check(Type e)
{
	branch<Type> *t = this->root;
	while (t)
		if (t->data == e)
			return true;
		else
			t = t->data > e ? t->left : t->right;
	return false;
}
