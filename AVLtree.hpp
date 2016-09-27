#include "AVLbranch.hpp"
#include "BinarySearchTree.hpp"

template <typename Type>
class AVLtree : public BinarySearchTree<Type>
{
protected:
	AVLbranch<Type> *root;
	void _add_(Type e);
	void _remove_(Type e);
public:
	AVLtree() { this->root = NULL;  }
	AVLtree(AVLbranch<Type> *root) { this->root = root; }
	AVLbranch<Type> *Root() { this->root; }
	void add(Type e);
	void add(Type a[], size_t size);
	void remove(Type e);
	void remove(Type a[], size_t size);
	bool check(Type e);
};

template <typename Type>
void AVLtree<Type>::_add_(Type e)
{
	try
	{
		AVLbranch<Type> *newNode = new AVLbranch<Type>(e);
#ifdef DEBUG
		printf("\nAdding %d to bst\n", e);
#endif // DEBUG
		if (this->root)
			this->root->insert(&this->root, newNode);
		else
			root = newNode;
	}
	catch (std::bad_alloc x)
	{
		throw "Unable to allocate memory for AVLbranch";
	}
}

template <typename Type>
void AVLtree<Type>::add(Type e)
{
	try
	{
		this->root->_add_(e);
	}
	catch (const std::string c)
	{
		std::cerr << c;
		std::exit(-1);
	}
}

template <typename Type>
void AVLtree<Type>::add(Type a[], size_t size)
{
	try
	{
		for (size_t i = 0; i < size; ++i)
		{
#ifdef DEBUG
			printf("\n\t\t\ti = %lu\n", i);
#endif // DEBUG			
			this->_add_(a[i]);
		}
	}
	catch (const std::string c)
	{
		std::cerr << c;
		std::exit(-1);
	}
}
/*
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
*/
