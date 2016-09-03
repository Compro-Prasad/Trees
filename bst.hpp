#include "tree.hpp"

template <typename Type>
class BinarySearchTree : public tree<Type>
{
protected:
	bool _add_(Type e);
	bool _remove_(Type e);
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
bool BinarySearchTree<Type>::_add_(Type e)
{
	branch<Type> **t = &this->root;
	while (*t)
	{
		if ((*t)->data == e)
			return 0;
		t = (*t)->data > e ? &(*t)->left : &(*t)->right;
	}
	*t = new branch<Type>(e);
	return 1;
}

template <typename Type>
void BinarySearchTree<Type>::add(Type e)
{
	if (!this->_add_(e))
		cerr << "Error: Unable to add duplicate element [ " << e << " ]\n";
	if (this->autoUpdateHeight && this->root)
		this->root->updateHeight();
}

template <typename Type>
void BinarySearchTree<Type>::add(Type a[], size_t size)
{
	for (size_t i = 0; i < size; ++i)
		this->_add_(a[i]);
	if (this->autoUpdateHeight && this->root)
		this->root->updateHeight();
}

template <typename Type>
bool BinarySearchTree<Type>::_remove_(Type e)
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
			return 1;
		}
		t = (*t)->data > e ? &(*t)->left : &(*t)->right;
	}
	return 0;
}

template <typename Type>
void BinarySearchTree<Type>::remove(Type e)
{
	if (!this->_remove_(e))
		cerr << "Error: Unable to find [ " << e << " ]\n";
	if (this->autoUpdateHeight && this->root)
		this->root->updateHeight();
}

template <typename Type>
void BinarySearchTree<Type>::remove(Type a[], size_t size)
{
	for (size_t i = 0; i < size; ++i)
		if (!this->_remove_(a[i]))
			cerr << "Error: Unable to find [ " << a[i] << " ]\n";
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
