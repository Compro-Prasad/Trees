#include <iostream>

using namespace std;

template <typename Type>
class branch
{
private:
	int height;
	int heightBalance;
public:
	Type data;
	branch<Type> *right;
	branch<Type> *left;
	branch() {
		this->data = 0;
		this->height = this->heightBalance = 0;
		this->right = this->left = NULL;
	}
	branch(Type e) {
		this->data = e;
		this->height = this->heightBalance = 0;
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
		int l = left  ? left->updateHeight()  : 0;
		int r = right ? right->updateHeight() : 0;
	    heightBalance = l - r;
		height        = 1 + max(l, r);
		return height;
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
