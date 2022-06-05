#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector <int> arr(26, -1);

int main(int argc, char* argv[])
{
	ifstream inputFile;
	inputFile.open(argv[1]);

	ofstream outputFile;
	outputFile.open("OutF.txt");

	int len = 0;
	inputFile >> len;
	string inStr = "";
	inputFile >> inStr;

	string res = "";
	string underStr = "";
	int i = 0;

	while (i < len)
	{
		if (arr[inStr[i] - 'A'] == -1)
		{
			arr[inStr[i] - 'A'] = i;
			underStr += inStr[i];
			i++;
		}
		else
		{
			i = arr[inStr[i] - 'A'] + 1;
			fill(arr.begin(), arr.end(), -1);
			underStr.clear();
		}

		if ((underStr.size() > res.size()) or ((underStr.size() == res.size()) and (underStr < res)))
			res = underStr;
	}
	outputFile << res;
}