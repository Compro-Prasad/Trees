#include <iostream>

using namespace std;

template <typename Type>
class branch
{
public:
	Type data;
	branch<Type> *right;
	branch<Type> *left;
	branch() {
		this->data = 0;
		this->right = this->left = NULL;
	}
	branch(Type e) {
		this->data = e;
		this->right = this->left = NULL;
	}
	branch(const branch &b) {
		this->data = b.data;
		this->right = b.right;
		this->left = b.left;
	}
	void operator=(const branch &b) {
		this->data = b.data;
		this->right = b.right;
		this->left = b.left;
	}
	void operator=(const Type t) {
		this->data = t;
	}
	int height() {
		int l = left  ? left->height()  : 0;
		int r = right ? right->height() : 0;
		return 1 + max(l, r);
	}
	bool isLeaf()            { return !this->right && !this->left;  }
	bool isOnlyRightLinked() { return this->right  && !this->left; }
	bool isOnlyLeftLinked()  { return !this->right && this->left;  }
	bool isRightLinked()     { return this->right; }
	bool isLeftLinked()      { return this->left;  }
	void print() {
		cout << this->data << " : " << this << "\n\t";
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
