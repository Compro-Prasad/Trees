#ifndef BRANCH_HPP
#define BRANCH_HPP

#include <iostream>
#include <string>
#include <stdio.h>

template <typename Type>
class Branch
{
public:
	Type data;
	Branch<Type> *right;
	Branch<Type> *left;

	Branch() {
		this->data = 0;
		this->right = this->left = NULL;
	}
	Branch(Type e) {
		this->data = e;
		this->right = this->left = NULL;
	}
	Branch(const Branch &b) {
		this->data = b.data;
		this->right = b.right;
		this->left = b.left;
	}

	void operator=(const Branch &b) {
		this->data = b.data;
		this->right = b.right;
		this->left = b.left;
	}

	void operator=(const Type t) {
		this->data = t;
	}

	void rotateAntiClockwise(Branch<Type> **thisAddrPtr) {
#ifdef TESTING
		if (*thisAddrPtr != this || not this->right)
			throw "Wrong node selected for rotating anti clockwise";
#endif
		Branch<Type> *k = this->right->left;
		this->right->left = this;
		*thisAddrPtr = this->right;
		this->right = k;
	}
	void rotateClockwise(Branch<Type> **thisAddrPtr) {
#ifdef TESTING
		if (*thisAddrPtr != this || not this->left)
			throw "Wrong node selected for rotating anti clockwise";
#endif
		Branch<Type> *k = this->left->right;
		this->left->right = this;
		*thisAddrPtr = this->left;
		this->left = k;
	}

	bool isLeaf()            { return !this->right && !this->left; }
	bool isOnlyRightLinked() { return this->right  && !this->left; }
	bool isOnlyLeftLinked()  { return !this->right && this->left;  }
	bool isRightLinked()     { return this->right; }
	bool isLeftLinked()      { return this->left;  }

	void printAll() {
		std::cout << this->data << " : " << this << "\n\t";
		std::cout << "Left  : " << this->left  << "\n\t";
		std::cout << "Right : " << this->right << "\n";
	}
	void print() {
		std::cout << this->data;
	}
	void print(std::string s) {
		std::cout << this->data << s;
	}
	void print_() {
		std::cout << this->data << " ";
	}
	void println() {
		this->print("\n");
	}
	int display_(int is_left, int offset, int depth, char s[50][255]);
	void display();

	void removeAll(Branch<Type> **node);

	void preOrder  (void func(void)) const;
	void postOrder (void func(void)) const;
	void inOrderInc(void func(void)) const;
	void inOrderDec(void func(void)) const;

	void preOrder (void func(const Type), const Type) const;
	void postOrder(void func(const Type), const Type) const;
	void inOrderInc(void func(const Type), const Type) const;
	void inOrderDec(void func(const Type), const Type) const;

	void copyToArrIncOrder(Type [], size_t &);
	void copyToArrDecOrder(Type [], size_t &);
};

template <typename Type>
void Branch<Type>::copyToArrIncOrder(Type A[], size_t &s)
{
	if (this->left)  this->left->copyToArrIncOrder(A, s);
	A[s++] = this->data;
	if (this->right) this->right->copyToArrIncOrder(A, s);
}

template <typename Type>
void Branch<Type>::copyToArrDecOrder(Type A[], size_t &size)
{
	if (this->right) this->right->copyToArrDecOrder(A, size);
	A[size++] = this->data;
	if (this->left) this->left->copyToArrDecOrder(A, size);
}

template <typename Type>
void Branch<Type>::removeAll(Branch<Type> **node)
{
	if (*node)
	{
		(*node)->removeAll(&(*node)->left);
		(*node)->removeAll(&(*node)->right);
		Branch<Type> *z = *node;
		*node = NULL;
		delete z;
	}
}

template <typename Type>
void Branch<Type>::preOrder(void func(void)) const
{
	func();
	if (this->left)  this->left->preOrder(func);
	if (this->right) this->right->preOrder(func);
}

template <typename Type>
void Branch<Type>::postOrder(void func(void)) const
{
	if (this->left) this->left->postOrder(func);
	if (this->right) this->right->postOrder(func);
	func();
}

template <typename Type>
void Branch<Type>::inOrderInc(void func(void)) const
{
	if (this->left) this->left->inOrderInc(func);
	func();
	if (this->right)  this->right->inOrderInc(func);
}

template <typename Type>
void Branch<Type>::inOrderDec(void func(void)) const
{
	if (this->right) this->right->inOrderDec(func);
	func();
	if (this->left)  this->left->inOrderDec(func);
}

template <typename Type>
void Branch<Type>::preOrder(void func(const Type), const Type x) const
{
	func(x);
	if (this->left)  this->left->preOrder(func, x);
	if (this->right) this->right->preOrder(func, x);
}

template <typename Type>
void Branch<Type>::postOrder(void func(const Type), const Type x) const
{
	if (this->left) this->left->postOrder(func, x);
	if (this->right) this->right->postOrder(func, x);
	func(x);
}

template <typename Type>
void Branch<Type>::inOrderInc(void func(const Type), const Type x) const
{
	if (this->left) this->left->inOrderInc(func, x);
	func(x);
	if (this->right)  this->right->inOrderInc(func, x);
}

template <typename Type>
void Branch<Type>::inOrderDec(void func(const Type), const Type x) const
{
	if (this->right) this->right->inOrderDec(func, x);
	func(x);
	if (this->left)  this->left->inOrderDec(func, x);
}

template <typename Type>
int Branch<Type>::display_(int is_left, int offset, int depth, char s[50][255]) {
	char b[20];
	int width = 5;

	sprintf(b, "%03d", this->data);

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

template <typename Type>
void Branch<Type>::display() {
	char s[50][255];
	for (int i = 0; i < 50; i++)
		sprintf(s[i], "%80s", " ");

	this->display_(0, 0, 0, s);

	for (int i = 0; i < 50; i++)
		printf("%s\n", s[i]);
}

#endif
