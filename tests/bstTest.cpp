#include <algorithm>
#include <string.h>
#include <unistd.h>
#include "../bst.hpp"

template <typename t>
void display(t *start, const t *end, string sep = " ")
{
	while (start < end)
		cout << *(start++) << sep;
	cout << "\n";
}

template <typename t>
void test(t a[], size_t size)
{
	BinarySearchTree<t> tree;
	t *b = new t[size], *c = new t[size];
	size_t s = 0;

	tree.add(a, size);
	tree.putInArrayInInc(c, s);

	copy(a, a + size, b);
	sort(b, b + size);

	if (!memcmp(b, c, size * sizeof(t)) && size == s)
	{
		delete[]b;
		delete[]c;
		return;
	}
	else if (size != s)
		cout << "Size mismatch\nActual size = " << size << "\nTree size   = " << s << "\n";
	else
	{
		cout << "Permutation : ";
		display(a, a + size);
		cout << "Sorted Array: ";
		display(b, a + size);
		cout << "Tree sort   : ";
		display(c, a + size);
	}
	delete[]b;
	delete[]c;
	exit(1);
}

template <typename t>
void permute(t a[], size_t k, size_t size, void func(t [], size_t))
{
	if (k == size - 1)
		func(a, size);
	else
		for (size_t i = k; i < size; ++i)
		{
			swap(a[k], a[i]);
			permute(a, k + 1, size, func);
			swap(a[k], a[i]);
		}
}

int main()
{
	int a[] = {1, 2, 3, 4, 5};
	permute(a, 0, sizeof(a) / sizeof(int), test);
	cout << "Tests Passed\n";
	cout << "Conclusions:\n";
	cout << "      Things working properly:\n";
	cout << "               BinarySearchTree::add(array, size)";
	cout << "               BinarySearchTree::add(element)";
	cout << "               BinarySearchTree::putInArrayInInc(arr, &size)";
	cout << "               BinarySearchTree::~BinarySearchTree()";
	return 0;
}
