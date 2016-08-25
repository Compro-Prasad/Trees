#include "branch.hpp"

template <typename Type>
class tree
{
public:
	static bool autoUpdateHeight;
	branch<Type> *root;
	branch<Type> *Root() { return this->root; }
	tree() {
		this->root = NULL;
	}
	tree(branch<Type> *root) {
		this->root = root;
		if (this->autoUpdateHeight) root->updateHeight();
	}
	bool isEmpty() { return !this->root; }
	void updateHeight() {
		if (this->root) this->root->updateHeight();
	}
};

template <typename Type>
bool tree<Type>::autoUpdateHeight = true;
