#include "bst.hpp"

template <typename Type>
class AVLtree : public BinarySearchTree<Type>
{
public:
	AVLtree() : BinarySearchTree<Type>() { }
	AVLtree(branch<Type> *root) : BinarySearchTree<Type>(root) { }
	branch<Type> *Root() { this->root; }
	void add(Type e);
	void add(Type a[], size_t size);
	void remove(Type e);
	void remove(Type a[], size_t size);
	bool check(Type e);
};

template <typename Type>
void AVLtree<Type>::add(Type e)
{
	if (BinarySearchTree<Type>::_add_(e))
		this->root->balanceHeight(&this->root);
	else
		cerr << "Error: Unable to add duplicate element [ " << e << " ]\n";
}

template <typename Type>
void AVLtree<Type>::add(Type a[], size_t size)
{
	for (size_t i = 0; i < size; ++i)
		if (BinarySearchTree<Type>::_add_(a[i]))
			this->root->balanceHeight(&this->root);
		else
			cerr << "Error: Unable to add duplicate element [ " << a[i] << " ]\n";
}

template <typename Type>
void AVLtree<Type>::remove(Type e)
{
	if (BinarySearchTree<Type>::_remove_(e))
		this->root ? this->root->balanceHeight(&this->root) : 0;
	else
		cerr << "Error: Unable to find [ " << e << " ]\n";
}

template <typename Type>
void AVLtree<Type>::remove(Type a[], size_t size)
{
	for (size_t i = 0; i < size; ++i)
		if (BinarySearchTree<Type>::_remove_(a[i]))
			this->root ? this->root->balanceHeight(&this->root) : 0;
		else
			cerr << "Error: Unable to find [ " << a[i] << " ]\n";
}
