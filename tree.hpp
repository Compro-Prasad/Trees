#ifndef TREE_HPP
#define TREE_HPP

#include "Branch.hpp"

template <typename Type>
class Tree
{
public:
	Branch<Type> *root;
	size_t rootHeight() {
		return this->root ? this->root->Height() : 0;
	}
	Branch<Type> *Root() { return this->root; }
	Tree() {
		this->root = NULL;
	}
	Tree(Branch<Type> *root) {
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

#endif
