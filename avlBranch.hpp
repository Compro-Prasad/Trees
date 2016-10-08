#ifndef ADVBRANCH_HPP
#define ADVBRANCH_HPP

#include "baseBranch.hpp"

#define AVLptr(x)  ((avlBranch<Type> *)x)
#define AVLpptr(x) ((avlBranch<Type> **)x)

template <typename Type>
class avlBranch : public baseBranch<Type>
{
protected:
	signed char heightBalance;
	bool balanceRightWeightedTree(avlBranch<Type> **root) {
		switch (--this->heightBalance)
		{
		case -1:
			return 1;
		case -2:
			switch (((avlBranch<Type> *)this->right)->heightBalance)
			{
			case 0:  /* Single Rotation */
			case -1:
				this->rotateAntiClockwise(root);
				(*root)->heightBalance =
					((avlBranch<Type> *)(*root)->left)->heightBalance = 0;
				break;
			case +1:  /* Double Rotation */
				this->right->rotateClockwise(&this->right);
				((avlBranch<Type> *)((avlBranch<Type> *)this->right)->right)->heightBalance = 1;
				this->rotateAntiClockwise(root);
				(*root)->heightBalance = 0;
				((avlBranch<Type> *)(*root)->left)->heightBalance = 0;
			}
		case 0:
			return 0;
		}
	}
	bool balanceLeftWeightedTree(avlBranch<Type> **root) {
		switch (++this->heightBalance)
		{
		case 0:
			return 0;
		case 1:
			return 1;
		case 2:
			switch (((avlBranch<Type> *)this->left)->heightBalance)
			{
			case 0:  /* Single Rotation */
			case +1:
				this->rotateClockwise(root);
				(*root)->heightBalance =
					((avlBranch<Type> *)(*root)->right)->heightBalance = 0;
				break;
			case -1:  /* Double Rotation */
				this->left->rotateAntiClockwise(&this->left);
				((avlBranch<Type> *)((avlBranch<Type> *)this->left)->left)->heightBalance = 1;
				this->rotateClockwise(root);
				(*root)->heightBalance = 0;
				((avlBranch<Type> *)(*root)->right)->heightBalance = 0;
			}
		}
	}

	Type killElementHaving2Children(avlBranch<Type> **);

public:
	avlBranch() { this->heightBalance = 0; }
	avlBranch(Type e) : baseBranch<Type>::baseBranch(e), heightBalance(0) { }
	void print() {
		std::cout << this->data << " : " << this << "\n\t";
		std::cout << "Left  : " << this->left  << "\n\t";
		std::cout << "Right : " << this->right << "\n";
	}
	bool add(avlBranch<Type> **, Type);
	bool remove(avlBranch<Type> **, Type);
};

template <typename Type>
bool avlBranch<Type>::add(avlBranch<Type> **root, Type e)
{
#ifdef TESTING
	if (*root != this)
		throw "Error: Addresses don't match";
#endif
	if (!*root)
	{
		*root = new avlBranch<Type>(e);
		return 1;
	}
	if (e < this->data)
	{
		if (AVLptr(this->left)->add(AVLpptr(&this->left), e))
			return balanceLeftWeightedTree(root);
	}
	else if (AVLptr(this->right)->add(AVLpptr(&this->right), e))
		return balanceRightWeightedTree(root);
	return 0;
}

template <typename Type>
Type avlBranch<Type>::killElementHaving2Children(avlBranch<Type> **root)
{
#ifdef TESTING
	if (this || this != *root)
		throw "Bad memory location";
#endif // TESTING
	if ((*root)->left)
		return AVLptr((*root)->left)->killElementHaving2Children(AVLpptr(&(*root)->left));
	else
	{
		Type x = (*root)->data;
		avlBranch<Type> *z = *root;
		*root = AVLptr((*root)->right);
		delete z;
		return x;
	}
}

template <typename Type>
bool avlBranch<Type>::remove(avlBranch<Type> **root, Type e)
{
	try
	{
		if (!*root)
		{
			if (e < (*root)->data)
			{
				if (AVLptr(this->left)->remove(AVLpptr(&this->left), e))
					return balanceRightWeightedTree(root);
			}
			else if (e > (*root)->data)
			{
				if (AVLptr(this->right)->remove(AVLpptr(&this->left), e))
					return balanceLeftWeightedTree(root);
			}
			else
			{
				avlBranch<Type> *z = *root;
				if (z->isLeaf())
					*root = NULL;
				else if (z->isOnlyLeftLinked())
					*root = AVLptr(z->left);
				else if (z->isOnlyRightLinked())
					*root = AVLptr(z->right);
				else
				{
					z->data = AVLptr(z->right)->killElementHaving2Children(AVLpptr(&z->right));
					return 1;
				}
				delete z;
			}
			return 1;
		}
		throw "Element not found\n";
	}
	catch (const char *c)
	{
		throw c;
	}
}

#endif
