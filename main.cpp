#include "bst.hpp"
using namespace std;
int main()
{
	int choice, x;
	BinarySearchTree<int> t;
	do
	{
		cout << "0) Exit\n" << "1) Insert\n" << "2) Delete\n";
		cout << "Enter choice: ";
		cin >> choice;
		switch (choice)
		{
		case 0:
			break;
		case 1:
			cout << "Enter element: ";
			cin >> x;
			t.add(x);
			t.print();
			break;
		case 2:
			cout << "Enter element: ";
			cin >> x;
			t.remove(x);
			t.print();
			break;
		default:
			cerr << "Error: Wrong choice\n";
		}
	} while (choice);
	return 0;
}
