#include <iostream>
#include <stdio.h>

using namespace std;

template <typename Type>
class branch
{
protected:
	size_t height;
public:
	Type data;
	branch<Type> *right;
	branch<Type> *left;
	branch() {
		this->data = 0;
		this->height = 0;
		this->right = this->left = NULL;
	}
	branch(Type e) {
		this->data = e;
		this->height = 0;
		this->right = this->left = NULL;
	}
	branch(const branch &b) {
		this->data = b.data;
		this->right = b.right;
		this->left = b.left;
		this->height = b.height;
	}
	size_t Height() {
		return this->height;
	}
	void operator=(const branch &b) {
		this->data = b.data;
		this->right = b.right;
		this->left = b.left;
	}
	void operator=(const Type t) {
		this->data = t;
	}
	void rotateAntiClockwise(branch<Type> **thisAddrPtr) {
		if (*thisAddrPtr == this && this->right)
		{
#ifdef DEBUG
				cout << "After rotating anti-clockwise about " << this->data << "\n";
#endif
			branch<Type> *k = this->right->left;
			this->right->left = this;
			*thisAddrPtr = this->right;
			this->right = k;
#ifdef DEBUG
			this->display();
#endif
		}
	}
	void rotateClockwise(branch<Type> **thisAddrPtr) {
		if (*thisAddrPtr == this && this->left)
		{
#ifdef DEBUG
				cout << "After rotating clockwise about " << this->data << "\n";
#endif
			branch<Type> *k = this->left->right;
			this->left->right = this;
			*thisAddrPtr = this->left;
			this->left = k;
#ifdef DEBUG
			this->display();
#endif
		}
	}
	size_t updateHeight() {
		size_t l = this->left  ? this->left->updateHeight()  : 0;
		size_t r = this->right ? this->right->updateHeight() : 0;
		this->height = 1 + max(l, r);
		return this->height;
	}
	size_t balanceHeight(branch<Type> **thisAddrPtr) {
		size_t l = this->left  ? this->left->balanceHeight(&this->left)   : 0;
		size_t r = this->right ? this->right->balanceHeight(&this->right) : 0;
		if (((long)l - (long)r) > 1)
		{
			size_t ll = this->left->right ? this->left->right->height : 0;
			size_t lr = this->left->left  ? this->left->left->height  : 0;
			switch ((long)lr - (long)ll)
			{
			case 0:
			case 1:
				this->rotateClockwise(thisAddrPtr);
#ifdef DEBUG
				cout << "\n";
#endif
				break;
			case -1:
				this->left->rotateAntiClockwise(&this->left);
				this->rotateClockwise(thisAddrPtr);
#ifdef DEBUG
				cout << "\n";
#endif
			}
			return (*thisAddrPtr)->updateHeight();
		}
		else if (((long)l - (long)r) < -1)
		{
			size_t rl = this->right->right ? this->right->right->height : 0;
			size_t rr = this->right->left  ? this->right->left->height  : 0;
			switch ((long)rr - (long)rl)
			{
			case 0:
			case -1:
				this->rotateAntiClockwise(thisAddrPtr);
#ifdef DEBUG
				cout << "\n";
#endif
				break;
			case 1:
				this->right->rotateClockwise(&this->right);
				this->rotateAntiClockwise(thisAddrPtr);
#ifdef DEBUG
				cout << "\n";
#endif
			}
			return (*thisAddrPtr)->updateHeight();
		}
		this->height = 1 + max(l, r);
		return this->height;
	}
	bool isLeaf()            { return !this->right && !this->left;  }
	bool isOnlyRightLinked() { return this->right  && !this->left; }
	bool isOnlyLeftLinked()  { return !this->right && this->left;  }
	bool isRightLinked()     { return this->right; }
	bool isLeftLinked()      { return this->left;  }
	bool print() {
		cout << this->data << " : " << this << " : " << this->height << "\n\t";
		cout << "Left  : " << this->left  << "\n\t";
		cout << "Right : " << this->right << "\n";
		return 0;
	}
	int display_(int is_left, int offset, int depth, char s[20][255]) {
		char b[20];
		int width = 5;

		sprintf(b, "(%01d:%01lu)", this->data, this->height);

		int left  = this->left  ? this->left->display_(1, offset, depth + 1, s) : 0;
		int right = this->right ? this->right->display_(0, offset + left + width, depth + 1, s) : 0;
#define COMPACT
#ifdef COMPACT
		for (int i = 0; i < width; i++)
			s[depth][offset + left + i] = b[i];

		if (depth && is_left) {

			for (int i = 0; i < width + right; i++)
				s[depth - 1][offset + left + width/2 + i] = '-';

			s[depth - 1][offset + left + width/2] = '.';

		} else if (depth && !is_left) {

			for (int i = 0; i < left + width; i++)
				s[depth - 1][offset - width/2 + i] = '-';

			s[depth - 1][offset + left + width/2] = '.';
		}
#else
		for (int i = 0; i < width; i++)
			s[2 * depth][offset + left + i] = b[i];

		if (depth && is_left) {

			for (int i = 0; i < width + right; i++)
				s[2 * depth - 1][offset + left + width/2 + i] = '-';

			s[2 * depth - 1][offset + left + width/2] = '+';
			s[2 * depth - 1][offset + left + width + right + width/2] = '+';

		} else if (depth && !is_left) {

			for (int i = 0; i < left + width; i++)
				s[2 * depth - 1][offset - width/2 + i] = '-';

			s[2 * depth - 1][offset + left + width/2] = '+';
			s[2 * depth - 1][offset - width/2 - 1] = '+';
		}
#endif

		return left + width + right;
	}

	int display() {
		char s[height][255];
		for (int i = 0; i < height; i++)
			sprintf(s[i], "%80s", " ");

		this->display_(0, 0, 0, s);

		for (int i = 0; i < height; i++)
			printf("%s\n", s[i]);
	}
	void removeAll(branch<Type> **node);
	void preOrderPrint(const bool printAll);
	void postOrderPrint(const bool printAll);
	void inOrderPrint(const bool printAll);
	void copyToArrIncOrder(Type A[], size_t &size);
	void copyToArrDecOrder(Type A[], size_t &size);
};

template <typename Type>
void branch<Type>::copyToArrIncOrder(Type A[], size_t &size)
{
	if (this->left) this->left->copyToArrIncOrder(A, size);
	A[size++] = this->data;
	if (this->right) this->right->copyToArrIncOrder(A, size);
}

template <typename Type>
void branch<Type>::copyToArrDecOrder(Type A[], size_t &size)
{
	if (this->right) this->right->copyToArrDecOrder(A, size);
	A[size++] = this->data;
	if (this->left) this->left->copyToArrDecOrder(A, size);
}

template <typename Type>
void branch<Type>::removeAll(branch<Type> **node)
{
	if (*node)
	{
		(*node)->removeAll(&(*node)->left);
		(*node)->removeAll(&(*node)->right);
		branch<Type> *z = *node;
		*node = NULL;
		delete z;
	}
}

template <typename Type>
void branch<Type>::preOrderPrint(const bool printAll)
{
	printAll ? this->print() : cout << this->data << " ";
	if (this->left)  this->left->preOrderPrint(printAll);
	if (this->right) this->right->preOrderPrint(printAll);
}

template <typename Type>
void branch<Type>::postOrderPrint(const bool printAll)
{
	if (this->left) this->left->postOrderPrint(printAll);
	if (this->right) this->right->postOrderPrint(printAll);
	printAll ? this->print() : cout << this->data << " ";
}

template <typename Type>
void branch<Type>::inOrderPrint(const bool printAll)
{
	if (this->left) this->left->inOrderPrint(printAll);
	printAll ? this->print() : cout << this->data << " ";
	if (this->right)  this->right->inOrderPrint(printAll);
}

template <typename Type>
class AdvBranch : public branch<Type>
{
protected:
	AdvBranch<Type> *parent;
public:
	AdvBranch() {
		this->parent = NULL;
	}
	AdvBranch(AdvBranch<Type> *parent) {
		this->parent = parent;
	}
	AdvBranch(Type e, AdvBranch<Type> *parent) {
		this->data = e;
		this->parent = parent;
		this->updateHeight();
	}
	void print() {
		cout << this->data << " : " << this << " : " << this->heightBalance << "\n\t";
		cout << "Left  : " << this->left  << "\n\t";
		cout << "Right : " << this->right << "\n";
	}
	size_t updateHeight() {
		size_t l = this->left  ? this->left->updateHeight()  : 0;
		size_t r = this->right ? this->right->updateHeight() : 0;
		this->height        = 1 + max(l, r);
		return this->height;
	}
	void rotateAntiClockwise(AdvBranch<Type> **thisAddrPtr) {
		if (*thisAddrPtr == this && this->right)
		{
			AdvBranch<Type> *k = this->right->left;
			this->right->parent = this->parent;
			this->parent = this->right;
			if (k) k->parent = this;
			this->right->left = this;
			*thisAddrPtr = this->right;
			this->right = k;
		}
	}
	void rotateClockwise(AdvBranch<Type> **thisAddrPtr) {
		if (*thisAddrPtr == this && this->left)
		{
			AdvBranch<Type> *k = this->left->right;
			this->left->parent = this->parent;
			this->parent = this->left;
			if (k) k->parent = this;
			this->left->right = this;
			*thisAddrPtr = this->left;
			this->left = k;
		}
	}
	AdvBranch<Type> *brother() {
		return this->parent ? this->parent->left == this ? this->right : this->left : NULL;
	}
	AdvBranch<Type> *grandParent() {
		return this->parent ? this->parent->parent : NULL;
	}
	AdvBranch<Type> *uncle() {
		return this->parent ? this->parent->brother() : NULL;
	}
	AdvBranch<Type> *leftCousin() {
		AdvBranch<Type> *u = this->uncle();
		return u ? u->left : NULL;
	}
	AdvBranch<Type> *rightCousin() {
		AdvBranch<Type> *u = this->uncle();
		return u ? u->right : NULL;
	}
};
