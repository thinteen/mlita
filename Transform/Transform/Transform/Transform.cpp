#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

void show(int i) 
{
	cout << i << " ";
}

int main(int argc, char* argv[])
{
	vector<int> typesOfTransformators;

	long long n;

	cin >> n;

	if (n % 2 == 0)
	{
		cout << "No";
		return 0;
	}

	while (n != 1)
	{
		if (((n - 1) / 2) % 2 != 0)
		{
			n = (n - 1) / 2;
			typesOfTransformators.push_back(2);
		}
		else
		{
			n = (n + 1) / 2;
			typesOfTransformators.push_back(1);
		}
	}

	reverse(typesOfTransformators.begin(), typesOfTransformators.end());

	cout << typesOfTransformators.size() << "\n";

	for_each(typesOfTransformators.begin(), typesOfTransformators.end(), show);

	return 0;
}