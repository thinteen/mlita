#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

void Add(int k, int d, int N, vector<int>& fenwick)
{
	while (k < N)
	{
		fenwick[k] += d;
		k = k | (k + 1);	
	}
}

int Sum(int k, vector<int>& fenwick)
{
	int result = 0;
	while (k >= 0)
	{
		result += fenwick[k];
		k = (k & (k + 1)) - 1;
	}
	return result;
}

int Rsq(int i, int j, vector<int>& fenwick)
{
	return Sum(j, fenwick) - Sum(i - 1, fenwick);
}

int main()
{
	vector<int> array = {7, 9, -4, 6, -5, 8};
	
	vector<int> Tree(array.size(), 0);
	for (size_t i = 0; i < Tree.size(); i++)
	{
		Add(i, array[i], array.size(), Tree);
	}

	cout << "operations: \n1 - Rsq\n2 - Add\n3 - Update\n4 - Show tree\n0 - exit";

	int j = 0;
	int k = 0;
	bool exit = false;

	vector<int> arrRew(array.size(), 0);

	int i = -1;

	while (i != 0)
	{
		cout << "\n< operation: ";
		cin >> i;
		switch (i)
		{
		case 0:
			break;

		case 1:
			cin >> k;
			cin >> j;
			cout << Rsq(k, j, Tree);
			break;

		case 2:
			cin >> k;
			cin >> j;
			Add(k, j, array.size(), Tree);
			for (size_t i = 0; i < Tree.size(); i++)
				arrRew[i] = Rsq(i, i, Tree);
			for (size_t i = 0; i < arrRew.size(); i++)
				cout << arrRew[i] << " ";
			break;

		case 3:
			cin >> k;
			cin >> j;
			Add(k, j - Rsq(k, k, Tree), array.size(), Tree);
			for (size_t i = 0; i < Tree.size(); i++)
				arrRew[i] = Rsq(i, i, Tree);
			for (size_t i = 0; i < arrRew.size(); i++)
				cout << arrRew[i] << " ";
			break;

		case 4:
			cout << "\n";
			for (size_t i = 0; i < array.size(); i++)
			{
				cout << Tree[i] << " ";
			}
		}
	}	
}
