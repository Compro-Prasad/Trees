#include "branch.hpp"

template <typename Type>
class tree
{
public:
	bool autoUpdateHeight;
	branch<Type> *root;
	size_t rootHeight() {
		return this->root ? this->root->Height() : 0;
	}
	branch<Type> *Root() { return this->root; }
	tree() {
		autoUpdateHeight = true;
		this->root = NULL;
	}
	tree(branch<Type> *root) {
		this->root = root;
		if (this->autoUpdateHeight && this->root) root->updateHeight();
	}
	bool isEmpty() { return !this->root; }
	void updateHeight() {
		if (this->root) this->root->updateHeight();
	}
	void display() {
		if (this->root) this->root->display();
	}
};
