#include <algorithm>
#include <string.h>
#include <unistd.h>
#include "../tree.hpp"
#include "../avlBranch.hpp"

using namespace std;

template <typename t>
void display(t *start, const t *end, string sep = " ")
{
	while (start < end)
		cout << *(start++) << sep;
	cout << "\n";
}

template <typename t>
void testAdd(t a[], size_t size)
{
	tree<avlBranch<t>, t> tree;
	t *b = new t[size], *c = new t[size];
	size_t s = 0;

	tree.add(a, size);
	tree.copyToArrIncOrder(c, s);

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
		cout << "Tree        :\n";
		tree.display();
	}
	delete[]b;
	delete[]c;
	exit(1);
}

template<typename t>
void testRemove(t a[], size_t size)
{
	tree<avlBranch<t>, t> tree;
	t *b = new t[size];

	tree.add(a, size);
	tree.display();

	copy(a, a + size, b);
	sort(b, b + size);
	display(b, b + size);

	tree.remove(b, size);

	if (!tree.isEmpty())
	{
		cout << "Error in removing values\n";
		cout << "Permutation : ";
		display(a, a + size);
		cout << "Sorted Array: ";
		display(b, b + size);
		cout << "Tree        :\n";
		tree.display();
		exit(2);
	}
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
	int a[] = {1, 2, 3, 4, 5, 6, 7};
	permute(a, 0, sizeof(a) / sizeof(int), testAdd);
	cout << "Tests Passed for inserting elements in AVL Tree\n";
	cout << "Conclusions:\n";
	cout << "      Things working properly:\n";
	cout << "               AVLtree::add(array, size)\n";
	cout << "               AVLtree::add(element)\n";
	cout << "               AVLtree::copyToArrIncOrder(arr, &size)\n";
	cout << "               AVLtree::~AVLtree()\n";
	permute(a, 0, sizeof(a) / sizeof(int), testRemove);
	cout << "Tests Passed for removing elements from BST\n";
	cout << "Conclusions:\n";
	cout << "      Things working properly:\n";
	cout << "               AVLtree::remove(array, size)\n";
	cout << "               AVLtree::remove(element)\n";
	cout << "               tree::isEmpty()\n";
	return 0;
}
