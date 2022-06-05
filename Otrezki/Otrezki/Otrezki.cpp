#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = INT_MAX;

const int SIZE = 7;
int a[] = { 5, 3, 2, 4, 1, 6, 7 };
vector<int> treeMax(4 * SIZE);
vector<int> treeSum(4 * SIZE);

void buildMaxTree(int v, int L, int R)
{
	if (L == R - 1)
	{
		if (L < SIZE)
			treeMax[v] = a[L];
		return;
	}
	int M = (L + R) / 2;
	buildMaxTree(2 * v + 1, L, M);
	buildMaxTree(2 * v + 2, M, R);
	treeMax[v] = max(treeMax[2 * v + 1], treeMax[2 * v + 2]);
}

void buildSumTree(int v, int L, int R)
{
	if (L == R - 1)
	{
		if (L < SIZE)
			treeSum[v] = a[L];
		return;
	}
	int M = (L + R) / 2;
	buildSumTree(2 * v + 1, L, M);
	buildSumTree(2 * v + 2, M, R);
	treeSum[v] = treeSum[2 * v + 1] + treeSum[2 * v + 2];
}

int rmq(int v, int L, int R, int l, int r)
{
	if (r <= L || R <= l) 
		return 0;
	if (l <= L && R <= r) 
		return treeMax[v];
	int M = (L + R) / 2;
	return max(rmq(2 * v + 1, L, M, l, r), rmq(2 * v + 2, M, R, l, r));
}

void Add1(int v, int L, int R, int i, int x)
{
	if (L == R - 1)
	{
		treeSum[v] += x;
		treeMax[v] += x;
		return;
	}
	
	int M = (L + R) / 2;

	if (i < M) 
		Add1(2 * v + 1, L, M, i, x);
	else 
		Add1(2 * v + 2, M, R, i, x);

	treeSum[v] = treeSum[2 * v + 1] + treeSum[2 * v + 2];
	treeMax[v] = max(treeMax[2 * v + 1], treeMax[2 * v + 2]);
}

void ReverseSegmentsTree()
{
	cout << "\n";
	for (size_t i = 0; i < SIZE; i++)
	{
		cout << rmq(0, 0, SIZE, i, i + 1) << " ";
	}
}

int main()
{
	buildMaxTree(0, 0, SIZE);
	buildSumTree(0, 0, SIZE);

	cout << "Select an operation: \n";
	cout << "\t1 - Rmq\n\t2 - Add1\n\t3 - Add2\n\t0 - exit";

	int i = 0, j = 0, k = 0, x = 0;

	bool exit = false;
	while (!exit)
	{
		cout << "\n< operation: ";
		cin >> i;
		switch (i)
		{
		case 0:
			exit = true;
			break;
		case 1:
			cin >> k;
			cin >> j;
			cout << rmq(0, 0, SIZE, k, j);
			break;
		case 2:
			cin >> k;
			cin >> j;
			Add1(0, 0, SIZE, k - 1, j);
			ReverseSegmentsTree();
			break;
		case 3:
			break;
		}
	}
	return 0;
}
