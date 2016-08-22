#include "branch.hpp"

template <typename Type>
class tree
{
protected:
	int height;
public:
	branch<Type> *root;
	tree() {
		this->root = NULL;
		this->height = 0;
	}
	tree(branch<Type> *root) {
		this->root = root;
		this->update_height();
	}
	void update_height() {
		this->height = this->root ? this->root->height() : 0;
	}
	int tree_height() {
		return this->height;
	}
};
