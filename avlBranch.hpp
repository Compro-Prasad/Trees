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

	Type deleteAndReturnLeftmostChild(avlBranch<Type> **);
	Type deleteAndReturnRightmostChild(avlBranch<Type> **);

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
		{
			switch (++this->heightBalance) {
			case 1:
				return 1;
			case 2:
				switch (AVLptr(this->left)->heightBalance)
				{
				case +1:  /* Single Rotation */
					this->rotateClockwise(root);
					(*root)->heightBalance = 0;
					AVLptr((*root)->right)->heightBalance = 0;
					break;
				case -1:  /* Double Rotation */
					this->left->rotateAntiClockwise(&this->left);
					AVLptr(AVLptr(this->left)->left)->heightBalance =
						!!AVLptr(AVLptr(this->left)->left)->left;
					this->rotateClockwise(root);
					(*root)->heightBalance = 0;
					AVLptr((*root)->right)->heightBalance = 0;
				}
			}
			return 0;
		}
	}
	else if (AVLptr(this->right)->add(AVLpptr(&this->right), e))
	{
		switch (--this->heightBalance) {
		case -1:
			return 1;
		case -2:
			switch (AVLptr(this->right)->heightBalance)
			{
			case -1:  /* Single Rotation */
				this->rotateAntiClockwise(root);
				(*root)->heightBalance = 0;
				AVLptr((*root)->left)->heightBalance = 0;
				break;
			case +1:  /* Double Rotation */
				this->right->rotateClockwise(&this->right);
				AVLptr(AVLptr(this->right)->right)->heightBalance =
					-!!AVLptr(AVLptr(this->right)->right)->right;
				this->rotateAntiClockwise(root);
				(*root)->heightBalance = 0;
				AVLptr((*root)->left)->heightBalance = 0;
			}
		}
		return 0;
	}
	return 0;
}

template <typename Type>
Type avlBranch<Type>::deleteAndReturnRightmostChild(avlBranch<Type> **root)
{
#ifdef TESTING
	if (this || this != *root)
		throw "Bad memory location";
#endif // TESTING
	if ((*root)->right)
		return AVLptr((*root)->right)->deleteAndReturnRightmostChild(AVLpptr(&(*root)->right));
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
Type avlBranch<Type>::deleteAndReturnLeftmostChild(avlBranch<Type> **root)
{
#ifdef TESTING
	if (this || this != *root)
		throw "Bad memory location";
#endif // TESTING
	if ((*root)->left)
		return AVLptr((*root)->left)->deleteAndReturnLeftmostChild(AVLpptr(&(*root)->left));
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
#ifdef TESTING
		if (*root != this)
			throw "Pointers don't match";
#endif
		if (*root)
		{
			if (e < (*root)->data)
			{
				if (AVLptr(this->left)->remove(AVLpptr(&this->left), e))
				{
					switch (--this->heightBalance) {
					case 0:
						return 1;
					case -1:
						return 0;
					case -2:
						switch (AVLptr(this->right)->heightBalance) {
						case 0:
							this->rotateAntiClockwise(root);
							AVLptr((*root)->left)->heightBalance = -1;
							(*root)->heightBalance = 1;
							break;
						case -1:
							this->rotateAntiClockwise(root);
							AVLptr((*root)->left)->heightBalance = 0;
							(*root)->heightBalance = 0;
							break;
						case +1:
							this->right->rotateClockwise(&this->right);
							AVLptr(AVLptr(this->right)->right)->heightBalance =
								-!!AVLptr(AVLptr(this->right)->right)->right;
							this->rotateAntiClockwise(root);
							(*root)->heightBalance = 0;
							AVLptr((*root)->left)->heightBalance = 0;
						}
					}
				}
				return 0;
			}
			else if (e > (*root)->data)
			{
				if (AVLptr(this->right)->remove(AVLpptr(&this->left), e))
				{
					switch (++this->heightBalance) {
					case 0:
						return 1;
					case +1:
						return 0;
					case +2:
						switch (AVLptr(this->left)->heightBalance) {
						case 0:
							this->rotateClockwise(root);
							AVLptr((*root)->right)->heightBalance = -1;
							(*root)->heightBalance = 1;
							break;
						case +1:
							this->rotateClockwise(root);
							AVLptr((*root)->right)->heightBalance = 0;
							(*root)->heightBalance = 0;
							break;
						case -1:
							this->left->rotateAntiClockwise(&this->left);
							AVLptr(AVLptr(this->left)->left)->heightBalance =
								!!AVLptr(AVLptr(this->left)->left)->left;
							this->rotateClockwise(root);
							(*root)->heightBalance = 0;
							AVLptr((*root)->right)->heightBalance = 0;
						}
					}
				}
				return 0;
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
					z->data = AVLptr(z->right)->deleteAndReturnLeftmostChild(AVLpptr(&z->right));
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
