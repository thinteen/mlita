#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

void beetlesTrip(const vector<vector<char>>& garMatrix, const int i, const int j, int& actual, const int step)
{
	vector<vector<char>> matrix = garMatrix;
	matrix[i][j] = { '+' };

	if (garMatrix[i + 1][j] == '#')
	{
		if (actual < step + 1)
		{
			actual = step + 1;
		}	
		beetlesTrip(matrix, i + 1, j, actual, step + 1);
	}

	if (garMatrix[i - 1][j] == '#')
	{
		if (actual < step + 1)
		{
			actual = step + 1;
		}
		beetlesTrip(matrix, i - 1, j, actual, step + 1);
	}

	if (garMatrix[i][j + 1] == '#')
	{
		if (actual < step + 1)
		{
			actual = step + 1;
		}
		beetlesTrip(matrix, i, j + 1, actual, step + 1);
	}

	if (garMatrix[i][j - 1] == '#')
	{
		if (actual < step + 1)
		{
			actual = step + 1;
		}	
		beetlesTrip(matrix, i, j - 1, actual, step + 1);
	}
}

int main()
{
	ofstream outputFile("output.txt");
	ifstream inputFile("input.txt");
	if (!inputFile.is_open())
		return 1;

	int m, n, result = 0, potatoesCount = 0;
	char potato;

	inputFile >> m >> n;

	if ((m > 5) or (n > 5))
	{
		outputFile << "Square of garden is more than it can be";
		exit(0);
	}
	
	if ((m < 5) or (n < 5))
	{
		outputFile << "Square of garden is less than it can be";
		exit(0);
	}

	vector<vector<char>> garMatrix(m + 2, vector<char>(n + 2, '.'));

	for (size_t i = 0; i < m; i++)
	{
		for (size_t j = 0; j < n; j++)
		{
			inputFile >> potato;
			if (potato == '#')
			{
				garMatrix[i + 1][j + 1] = potato;
			}		
		}
	}

	for (size_t i = 0; i < garMatrix.size(); i++)
	{
		for (size_t j = 0; j < garMatrix[0].size(); j++)
		{
			if (garMatrix[i][j] == '#') potatoesCount++;
		}
	}

	for (size_t i = 0; i < garMatrix.size(); i++)
	{
		for (size_t j = 0; j < garMatrix[0].size(); j++)
		{
			if (garMatrix[i][j] == '#')
			{
				int actual = 1;
				beetlesTrip(garMatrix, i, j, actual, 1);
				result = max(result, actual);
				if (result == potatoesCount)
				{
					outputFile << result;
					exit(0);
				}
			}
		}
	}

	outputFile << result;
	return 0;
}