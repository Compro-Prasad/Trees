#ifndef ADVBRANCH_HPP
#define ADVBRANCH_HPP

#include "Branch.hpp"

template <typename Type>
class AVLbranch : public Branch<Type>
{
private:
	signed char heightBalance;
public:
	AVLbranch() { this->heightBalance = 0; }
	AVLbranch(Type e) : Branch<Type>::Branch(e), heightBalance(0) { }
	void print() {
		std::cout << this->data << " : " << this << "\n\t";
		std::cout << "Left  : " << this->left  << "\n\t";
		std::cout << "Right : " << this->right << "\n";
	}
	void rotateAntiClockwise(AVLbranch<Type> **thisAddrPtr) {
#ifdef TESTING
		if (*thisAddrPtr != this || not this || not this->right)
			throw "Wrong node selected for rotating anti clockwise";
#endif
		AVLbranch<Type> *k = (AVLbranch<Type> *)this->right->left;
		this->right->left = this;
		*thisAddrPtr = (AVLbranch<Type> *)this->right;
		this->right = k;
	}
	void rotateClockwise(AVLbranch<Type> **thisAddrPtr) {
#ifdef TESTING
		if (*thisAddrPtr != this|| not this || not this->left)
			throw "Wrong node selected for rotating anti clockwise";
#endif
		AVLbranch<Type> *k = (AVLbranch<Type> *)this->left->right;
		this->left->right = this;
		*thisAddrPtr = (AVLbranch<Type> *)this->left;
		this->left = k;
	}
	bool insert(AVLbranch<Type> **, AVLbranch<Type> *);
};

template <typename Type>
bool AVLbranch<Type>::insert(AVLbranch<Type> **root, AVLbranch<Type> *newBranch)
{
#ifdef TESTING
	if (*root != this)
		throw "Error: Addresses don't match";
#endif
	if (newBranch->data < this->data)
	{
		if (this->left)
		{
			if (((AVLbranch<Type> *)this->left)->insert((AVLbranch<Type> **)&this->left, newBranch))
			{
				switch (this->heightBalance)
				{
				case 0:
					return 0;
				case 1:
					return 1;
				case 2:
					switch (((AVLbranch<Type> *)this->left)->heightBalance)
					{
					case +1:  /* Single Rotation */
						AVLbranch<Type>::rotateClockwise(root);
						((AVLbranch<Type> *)(*root))->heightBalance =
							((AVLbranch<Type> *)(*root)->right)->heightBalance = 0;
						break;
					case -1:  /* Double Rotation */
						((AVLbranch<Type> *)this->left)->rotateAntiClockwise((AVLbranch<Type> **)&this->left);
						// this->left->heightBalance = 1;
						((AVLbranch<Type> *)this->left->left)->heightBalance = 1;
						AVLbranch<Type>::rotateClockwise(root);
						((AVLbranch<Type> *)(*root))->heightBalance = 0;
						((AVLbranch<Type> *)(*root)->right)->heightBalance = 0;
					}
				}
			}
		}
		else
		{
			this->left = newBranch;
			return 1;
		}
	}
	else
	{
		if (this->right)
		{
			if (((AVLbranch<Type> *)this->right)->insert((AVLbranch<Type> **)&this->right, newBranch))
			{
				switch (this->heightBalance)
				{
				case 0:
					return 0;
				case -1:
					return 1;
				case -2:
					switch (((AVLbranch<Type> *)this->right)->heightBalance)
					{
					case -1:  /* Single Rotation */
						AVLbranch<Type>::rotateAntiClockwise(root);
						((AVLbranch<Type> *)(*root))->heightBalance =
							((AVLbranch<Type> *)(*root)->left)->heightBalance = 0;
						break;
					case +1:  /* Double Rotation */
						((AVLbranch<Type> *)this->right)->rotateClockwise((AVLbranch<Type> **)&this->right);
						// this->left->heightBalance = 1;
						((AVLbranch<Type> *)this->right->right)->heightBalance = 1;
						AVLbranch<Type>::rotateAntiClockwise(root);
						((AVLbranch<Type> *)(*root))->heightBalance = 0;
						((AVLbranch<Type> *)(*root)->left)->heightBalance = 0;
					}
				}
			}
		}
		else
		{
			this->right = newBranch;
			return 1;
		}
	}
	return 0;
}

#endif
