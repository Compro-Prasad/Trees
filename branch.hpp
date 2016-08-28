#include <iostream>

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
		this->heightBalance = b.heightBalance;
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
			branch<Type> *k = this->right->left;
			this->right->left = this;
			*thisAddrPtr = this->right;
			this->right = k;
		}
	}
	void rotateClockwise(branch<Type> **thisAddrPtr) {
		if (*thisAddrPtr == this && this->leftt)
		{
			branch<Type> *k = this->left->right;
			this->left->right = this;
			*thisAddrPtr = this->leftt;
			this->left = k;
		}
	}
	size_t updateHeight() {
		size_t l = this->left  ? this->left->updateHeight()  : 0;
		size_t r = this->right ? this->right->updateHeight() : 0;
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
	void removeAll(branch<Type> **node);
	void preOrderPrint(const bool printAll);
	void postOrderPrint(const bool printAll);
	void inOrderPrint(const bool printAll);
	void putInArrayInInc(Type A[], size_t &size);
	void putInArrayInDec(Type A[], size_t &size);
};

template <typename Type>
void branch<Type>::putInArrayInInc(Type A[], size_t &size)
{
	if (this->left) this->left->putInArrayInInc(A, size);
	A[size++] = this->data;
	if (this->right) this->right->putInArrayInInc(A, size);
}

template <typename Type>
void branch<Type>::putInArrayInDec(Type A[], size_t &size)
{
	if (this->right) this->right->putInArrayInDec(A, size);
	A[size++] = this->data;
	if (this->left) this->left->putInArrayInDec(A, size);
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
	long heightBalance;
	AdvBranch<Type> *parent;
public:
	AdvBranch() {
		this->parent = NULL;
		this->heightBalance = 0;
	}
	AdvBranch(AdvBranch<Type> *parent) {
		this->parent = parent;
		this->heightBalance = 0;
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
		this->heightBalance = (long)l - (long)r;
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
