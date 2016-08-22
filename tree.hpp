#include "branch.hpp"

template <typename Type>
class tree
{
public:
	branch<Type> *root;
	tree() {
		this->root = NULL;
	}
	tree(branch<Type> *root) {
		this->root = root;
		root->updateHeight();
	}
	bool isEmpty() { return !this->root; }
	void updateHeight() {
		if (this->root) this->root->updateHeight();
	}
};
