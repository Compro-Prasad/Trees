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
#ifdef DEBUG
		printf("\nRotating Anti Clockwise:\n\tBefore:\n");
		printf("\t\tPivot    : %p(%d)\n", *thisAddrPtr, (*thisAddrPtr)->data);
		printf("\t\tLeft     : %p\n", (*thisAddrPtr)->left);
		printf("\t\tRight    : %p(%d)\n", (*thisAddrPtr)->right, (*thisAddrPtr)->right->data);
		printf("\t\tRleft    : %p\n", (*thisAddrPtr)->right->left);
#endif // DEBUG
		AVLbranch<Type> *k = (AVLbranch<Type> *)this->right->left;
		this->right->left = this;
		*thisAddrPtr = (AVLbranch<Type> *)this->right;
		this->right = k;
#ifdef DEBUG
		printf("\tAfter:\n");
		printf("\t\tPivot    : %p(%d)\n", *thisAddrPtr, (*thisAddrPtr)->data);
		printf("\t\tLeft     : %p(%d)\n", (*thisAddrPtr)->left, (*thisAddrPtr)->left->data);
		printf("\t\tRight    : %p\n", (*thisAddrPtr)->right);
		printf("\t\tLright    : %p\n\n", (*thisAddrPtr)->left->right);
#endif // DEBUG
	}
	void rotateClockwise(AVLbranch<Type> **thisAddrPtr) {
#ifdef TESTING
		if (*thisAddrPtr != this|| not this || not this->left)
			throw "Wrong node selected for rotating anti clockwise";
#endif
#ifdef DEBUG
		printf("\nRotating Clockwise:\n\tBefore:\n");
		printf("\tPivot    : %p(%d)\n", *thisAddrPtr, (*thisAddrPtr)->data);
		printf("\tLeft     : %p(%d)\n", (*thisAddrPtr)->left, (*thisAddrPtr)->left->data);
		printf("\tRight    : %p\n", (*thisAddrPtr)->right);
		printf("\tLright   : %p\n", (*thisAddrPtr)->left->right);
#endif // DEBUG
		AVLbranch<Type> *k = (AVLbranch<Type> *)this->left->right;
		this->left->right = this;
		*thisAddrPtr = (AVLbranch<Type> *)this->left;
		this->left = k;
#ifdef DEBUG
		printf("\tAfter:\n");
		printf("\t\tPivot    : %p(%d)\n", *thisAddrPtr, (*thisAddrPtr)->data);
		printf("\t\tLeft     : %p\n", (*thisAddrPtr)->left);
		printf("\t\tRight    : %p(%d)\n", (*thisAddrPtr)->right, (*thisAddrPtr)->right->data);
		printf("\t\tRleft    : %p\n", (*thisAddrPtr)->right->left);
#endif // DEBUG
	}
	bool insert(AVLbranch<Type> **, AVLbranch<Type> *);
};

template <typename Type>
bool AVLbranch<Type>::insert(AVLbranch<Type> **root, AVLbranch<Type> *newBranch)
{
	printf("\nEntering insert() with (*root)->data = %d and newData=%d\n", (*root)->data, newBranch->data);
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
				printf("\nBalance height of %d is %d\n", this->data, ++this->heightBalance);
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
			printf("\nBalance height of %d is %d\n", this->data, ++this->heightBalance);
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
				printf("\nBalance height of %d is %d\n", this->data, --this->heightBalance);
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
						((AVLbranch<Type> *)this->right)->rotateClockwise((AVLbranch<Type> **)&this->left);
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
			printf("\nBalance height of %d is %d\n", this->data, --this->heightBalance);
			this->right = newBranch;
			return 1;
		}
	}
	return 0;
}

#endif
