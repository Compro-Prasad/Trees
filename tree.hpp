#ifndef TREE_HPP
#define TREE_HPP

#include <algorithm>
#include <iostream>

template <typename type>
void print_(type x)
{
	std::cout << x << " ";
}

template <typename node, typename type>
class tree
{
	node *root;
public:
	tree() { this->root = NULL; }
	tree(node *root) {
		this->root = root;
	}
	~tree();

	void add(type e);
	void add(type a[], size_t size);
	void remove(type e);
	void remove(type a[], size_t size);
	bool check(type e) const;
	void copyToArrIncOrder(type [], size_t &) const;
	void copyToArrDecOrder(type [], size_t &) const;
	void print() const {
		if (this->root) this->root->inOrderInc(print_, this->root->Data());
	}
	size_t rootHeight() const {
		return this->root ? this->root->Height() : 0;
	}
	node *Root() const { return this->root; }
	bool isEmpty() const { return !this->root; }
	void updateHeight() {
		if (this->root) this->root->updateHeight();
	}
	void display() const {
		if (this->root) this->root->display();
	}
};

template <typename node, typename type>
void tree<node, type>::copyToArrIncOrder(type A[], size_t &s) const
{
	if (this->root)
		this->root->copyToArrIncOrder(A, s);
	else
		s = 0;
}

template <typename node, typename type>
void tree<node, type>::copyToArrDecOrder(type A[], size_t &s) const
{
	if (this->root)
		this->root->copyToArrDecOrder(A, s);
	else
		s = 0;
}

template <typename node, typename type>
void tree<node, type>::add(type e)
{
	try
	{
		this->root->add(&this->root, e);
	}
	catch (const char *c)
	{
		std::cerr << "Error   : Unable to add " << e << " in the tree\n";
		std::cerr << "Recieved: " << c << "\n";
	}
}

template <typename node, typename type>
void tree<node, type>::add(type a[], size_t size)
{
	for (size_t i = 0; i < size; ++i)
		try
		{
			this->root->add(&this->root, a[i]);
		}
		catch (const char *c)
		{
			std::cerr << "Error   : Unable to add " << a[i] << " in the tree\n";
			std::cerr << "Recieved: " << c << "\n";
		}
}

template <typename node, typename type>
void tree<node, type>::remove(type e)
{
	try
	{
		this->root->remove(&this->root, e);
	}
	catch (const char *c)
	{
		std::cerr << "Error   : Unable to remove [ " << e << " ] from the tree\n";
		std::cerr << "Recieved: " << c << "\n";
		exit(1);
	}
}

template <typename node, typename type>
void tree<node, type>::remove(type a[], size_t size)
{
	for (size_t i = 0; i < size; ++i)
		try
		{
			this->root->remove(&this->root, a[i]);
		}
		catch (const char *c)
		{
			std::cerr << "Error   : Unable to remove [ " << a[i] << " ]\n";
			std::cerr << "Recieved: " << c << "\n";
			this->root->display();
			exit(1);
		}
}

template <typename node, typename type>
tree<node, type>::~tree()
{
	if (this->root)
		this->root->removeAll(&this->root);
}

template <typename node, typename type>
bool tree<node, type>::check(type e) const
{
	node *t = this->root;
	while (t)
		if (t->data == e)
			return true;
		else
			t = t->data > e ? t->left : t->right;
	return false;
}

#endif
