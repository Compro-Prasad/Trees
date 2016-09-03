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
	bool autoUpdate = this->autoUpdateHeight;
	this->autoUpdateHeight = false;
	BinarySearchTree<Type>::add(e);
	this->autoUpdateHeight = autoUpdate;
	if (this->autoUpdateHeight && this->root) this->root->balanceHeight(&this->root);
}

template <typename Type>
void AVLtree<Type>::add(Type a[], size_t size)
{
	for (size_t i = 0; i < size; ++i)
		AVLtree<Type>::add(a[i]);
}

template <typename Type>
void AVLtree<Type>::remove(Type e)
{
	bool autoUpdate = this->autoUpdateHeight;
	this->autoUpdateHeight = false;
	BinarySearchTree<Type>::remove(e);
	this->autoUpdateHeight = autoUpdate;
	if (this->autoUpdateHeight && this->root) this->root->balanceHeight(&this->root);
}

template <typename Type>
void AVLtree<Type>::remove(Type a[], size_t size)
{
	bool autoUpdate = this->autoUpdateHeight;
	this->autoUpdateHeight = false;
	for (size_t i = 0; i < size; ++i)
		this->remove(a[i]);
	this->autoUpdateHeight = autoUpdate;
	if (this->autoUpdateHeight && this->root)
		this->root->balanceHeight(&this->root);
}
