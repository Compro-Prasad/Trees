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
		int l = left  ? this->left->updateHeight()  : 0;
		int r = right ? this->right->updateHeight() : 0;
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
class AVLbranch : public branch<Type>
{
protected:
	int heightBalance;
public:
	AVLbranch() {
		this->heightBalance = 0;
	}
	int updateHeight() {
		int l = left  ? this->left->updateHeight()  : 0;
		int r = right ? this->right->updateHeight() : 0;
		this->heightBalance = l - r;
		this->height        = 1 + max(l, r);
		return this->height;
	}
};
