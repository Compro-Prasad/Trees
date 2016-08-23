#include "branch.hpp"

template <typename Type>
class tree
{
public:
	bool autoUpdateHeight;
	branch<Type> *root;
	tree() {
		this->root = NULL;
		autoUpdateHeight = true;
	}
	tree(branch<Type> *root) {
		this->root = root;
		if (autoUpdateHeight) root->updateHeight();
	}
	bool isEmpty() { return !this->root; }
	void updateHeight() {
		if (this->root) this->root->updateHeight();
	}
};
