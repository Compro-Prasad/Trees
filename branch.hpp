#include <iostream>

using namespace std;

template <typename Type>
class branch
{
protected:
	int height;
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
	int Height() {
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
	int updateHeight() {
		int l = this->left  ? this->left->updateHeight()  : 0;
		int r = this->right ? this->right->updateHeight() : 0;
		this->height = 1 + max(l, r);
		return this->height;
	}
	bool isLeaf()            { return !this->right && !this->left;  }
	bool isOnlyRightLinked() { return this->right  && !this->left; }
	bool isOnlyLeftLinked()  { return !this->right && this->left;  }
	bool isRightLinked()     { return this->right; }
	bool isLeftLinked()      { return this->left;  }
	void print() {
		cout << this->data << " : " << this << " : " << this->height << "\n\t";
		cout << "Left  : " << this->left  << "\n\t";
		cout << "Right : " << this->right << "\n";
	}
	void preOrderPrint();
	void postOrderPrint();
	void inOrderPrint();
};

template <typename Type>
void branch<Type>::preOrderPrint()
{
	this->print();
	if (this->left)  this->left->preOrderPrint();
	if (this->right) this->right->preOrderPrint();
}

template <typename Type>
void branch<Type>::postOrderPrint()
{
	if (this->left) this->left->postOrderPrint();
	if (this->right) this->right->postOrderPrint();
	this->print();
}

template <typename Type>
void branch<Type>::inOrderPrint()
{
	if (this->left) this->left->inOrderPrint();
	this->print();
	if (this->right)  this->right->inOrderPrint();
}

template <typename Type>
class AdvBranch : public branch<Type>
{
protected:
	int heightBalance;
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
	int updateHeight() {
		int l = this->left  ? this->left->updateHeight()  : 0;
		int r = this->right ? this->right->updateHeight() : 0;
		this->heightBalance = l - r;
		this->height        = 1 + max(l, r);
		return this->height;
	}
	void rotateAntiClockwise(AdvBranch<Type> **thisAddrPtr) {
		if (*thisAddrPtr == this && this->right)
		{
			AdvBranch<Type> *k = this->right->left;
			this->right->left = this;
			*thisAddrPtr = this->right;
			this->right = k;
		}
	}
	void rotateClockwise(AdvBranch<Type> **thisAddrPtr) {
		if (*thisAddrPtr == this && this->leftt)
		{
			AdvBranch<Type> *k = this->left->right;
			this->left->right = this;
			*thisAddrPtr = this->leftt;
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
