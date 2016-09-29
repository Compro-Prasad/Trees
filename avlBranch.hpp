#ifndef ADVBRANCH_HPP
#define ADVBRANCH_HPP

#include "baseBranch.hpp"

template <typename Type>
class avlBranch : public baseBranch<Type>
{
protected:
	signed char heightBalance;
public:
	avlBranch() { this->heightBalance = 0; }
	avlBranch(Type e) : baseBranch<Type>::baseBranch(e), heightBalance(0) { }
	void print() {
		std::cout << this->data << " : " << this << "\n\t";
		std::cout << "Left  : " << this->left  << "\n\t";
		std::cout << "Right : " << this->right << "\n";
	}
	void removeAll(avlBranch<Type> **);
	bool add(avlBranch<Type> **, Type);
};

template <typename Type>
void avlBranch<Type>::removeAll(avlBranch<Type> **node)
{
#ifdef TESTING
	if (*node != this)
		throw "Bad memory location";
#endif // TESTING
	if (this->left)  ((avlBranch<Type> *)this->left)->removeAll((avlBranch<Type> **)&this->left);
	if (this->right) ((avlBranch<Type> *)this->right)->removeAll((avlBranch<Type> **)&this->right);
	delete *node;
	*node = NULL;
}

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
		if (((avlBranch<Type> *)this->left)->add((avlBranch<Type> **)&this->left, e))
		{
			switch (++this->heightBalance)
			{
			case 0:
				return 0;
			case 1:
				return 1;
			case 2:
				switch (((avlBranch<Type> *)this->left)->heightBalance)
				{
				case +1:  /* Single Rotation */
					this->rotateClockwise((baseBranch<Type> **)root);
					((avlBranch<Type> *)(*root))->heightBalance =
						((avlBranch<Type> *)(*root)->right)->heightBalance = 0;
					break;
				case -1:  /* Double Rotation */
					((avlBranch<Type> *)this->left)->rotateAntiClockwise((baseBranch<Type> **)&this->left);
					// this->left->heightBalance = 1;
					((avlBranch<Type> *)((avlBranch<Type> *)this->left)->left)->heightBalance = 1;
					this->rotateClockwise((baseBranch<Type> **)root);
					((avlBranch<Type> *)(*root))->heightBalance = 0;
					((avlBranch<Type> *)(*root)->right)->heightBalance = 0;
				}
			}
		}
	}
	else
	{
		if (((avlBranch<Type> *)this->right)->add((avlBranch<Type> **)&this->right, e))
		{
			switch (--this->heightBalance)
			{
			case 0:
				return 0;
			case -1:
				return 1;
			case -2:
				switch (((avlBranch<Type> *)this->right)->heightBalance)
				{
				case -1:  /* Single Rotation */
					this->rotateAntiClockwise((baseBranch<Type> **)root);
					((avlBranch<Type> *)(*root))->heightBalance =
						((avlBranch<Type> *)(*root)->left)->heightBalance = 0;
					break;
				case +1:  /* Double Rotation */
					((avlBranch<Type> *)this->right)->rotateClockwise((baseBranch<Type> **)&this->right);
					// this->left->heightBalance = 1;
					((avlBranch<Type> *)((avlBranch<Type> *)this->right)->right)->heightBalance = 1;
					this->rotateAntiClockwise((baseBranch<Type> **)root);
					((avlBranch<Type> *)(*root))->heightBalance = 0;
					((avlBranch<Type> *)(*root)->left)->heightBalance = 0;
				}
			}
		}
	}
	return 0;
}

#endif
