#ifndef BSTBRANCH_HPP
#define BSTBRANCH_HPP

#include <new>

#include "baseBranch.hpp"

template <typename Type>
class bstBranch : public baseBranch<Type>
{
public:
	bstBranch() : baseBranch<Type>::baseBranch() { }
	bstBranch(Type e) : baseBranch<Type>::baseBranch(e) { }
	bstBranch(const bstBranch &b) {
		this->data  = b.data;
		this->right = b.right;
		this->left  = b.left;
	}

	void removeAll(bstBranch<Type> **node);

	void operator=(const bstBranch &b) {
		this->data  = b.data;
		this->right = b.right;
		this->left  = b.left;
	}
	void operator=(const Type t) {
		this->data = t;
	}

	void add(bstBranch<Type> **, Type);
	bool remove(bstBranch<Type> **, Type);
};

template <typename Type>
void bstBranch<Type>::removeAll(bstBranch<Type> **node)
{
#ifdef TESTING
	if (*node != this)
		throw "Bad memory location";
#endif // TESTING
	if (this->left)  ((bstBranch<Type> *)this->left)->removeAll((bstBranch<Type> **)&this->left);
	if (this->right) ((bstBranch<Type> *)this->right)->removeAll((bstBranch<Type> **)&this->right);
	delete *node;
	*node = NULL;
}

template <typename Type>
void bstBranch<Type>::add(bstBranch<Type> **root, Type e)
{
#ifdef TESTING
	if (this != *root)
		throw "Bad memory location";
#endif // TESTING
	try
	{
		while (*root)
		{
			if ((*root)->data == e)
				throw "Duplicate element found";
			root = (bstBranch<Type> **)(e < (*root)->data ? &(*root)->left : &(*root)->right);
		}
		*root = new bstBranch<Type>(e);
	}
	catch (std::bad_alloc e)
	{
		throw "Memory cannot be allocated";
	}
}

template <typename Type>
bool bstBranch<Type>::remove(bstBranch<Type> **root, Type e)
{
#ifdef TESTING
	if (this != *root)
		throw "Bad memory location";
#endif // TESTING
	while (*root)
	{
		if ((*root)->data == e)
		{
			bstBranch<Type> *z = *root;
			if (z->isLeaf())
				*root = NULL;
			else if (z->isOnlyLeftLinked())
				*root = (bstBranch<Type> *)z->left;
			else if (z->isOnlyRightLinked())
				*root = (bstBranch<Type> *)z->right;
			else
			{
				root = (bstBranch<Type> **)&z->right;
				while ((*root)->left)
					root = (bstBranch<Type> **)&(*root)->left;
				z->data = (*root)->data;
				z = *root;
				*root = (bstBranch<Type> *)(*root)->right;
			}
			delete z;
			return 1;
		}
		root = (bstBranch<Type> **)(e < (*root)->data ? &(*root)->left : &(*root)->right);
	}
	return 0;
}

#endif // BSTBRANCH_HPP
