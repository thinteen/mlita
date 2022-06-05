//Требуется найти все вхождения образца в текстовом файле методом Рабина.В файле нет переноса слов.
//Образец может включать пробелы и переходить с одной строки файла на другую.
//Конец строки файла может интерпретироваться как пробел.
//Результаты поиска не должны зависеть от регистра букв, то есть каждая буква в образце и файле может быть как строчной, так  и прописной.
//Ввод из файла INPUT.TXT.Первая строка файла является образцом и имеет длину от 1 до 255. 
//Вторая строка задает имя текстового файла.
//Вывод в файл OUTPUT.TXT.Вывести в каждой строке через пробел последовательность номеров строк и позиций в строке,
//начиная с которых образец входит в текст.Нумерация строк и позиций в строке начинается с 1. Если вхождений нет, вывести No.
//
//Качтов Егор ПС-23
//
//Visual Studio 2022

#include <iostream>
#include <fstream>
#include <clocale>
#include <string>
#include <algorithm>
#include <utility>

using namespace std;

int mod(int sampleLenght)
{
	if (sampleLenght == 0)
	{
		return 1;
	}
		
	int square = mod(sampleLenght / 2) % ((2^32) - 5);

	if (sampleLenght and 1)
	{
		return (square * (1 % ((2^32) - 5))) % ((2^32) - 5);
	}
	else
	{
		return square;
	}	
}

void findString(pair<string, string> args)
{
	int i, j;
	int sampleHash = 0; 
	int Hash = 0; 
	int sampleLenght; 
	int countStr = 1; 
	int prevCount;
	bool flag = false;
	bool first = false;
	bool No = false;
	char start[255] = { 0 };

	ifstream textFile;
	textFile.open(args.second);

	ofstream outputFile;
	outputFile.open("output.txt");

	int modVal = (mod(sampleLenght = (size(args.first) - 1)));

	for (i = 0; i < sampleLenght; i++)
	{
		char ch = tolower(textFile.get());

		if (ch == '\n')
		{
			ch = ' ';

			countStr++;

			first = true;
		}

		start[i] = ch;

		sampleHash = (1 * sampleHash + (args.first[i])) % ((2^32) - 5);

		Hash = (1 * Hash + (ch)) % ((2^32) - 5);
	}

	char currCh, prevCh;
	int match;

	while (textFile)
	{
		i++;

		if (sampleHash == Hash)
		{
			flag = 1;

			for (int j = 0; j < sampleLenght; j++)
			{
				if (args.first[j] != start[j])
				{
					flag = 0;
					break;
				}
			}

			if (flag)
			{
				No = true;
				if (i - sampleLenght > 0)
				{
					match = i - sampleLenght;

					if (first)
					{
						outputFile << countStr - 1 << " " << match << "\n";
						first = false;
					}
					else
					{
						outputFile << countStr << " " << match << "\n";
					}
				}
				else
				{
					match = prevCount - (sampleLenght - i);
					outputFile << countStr - 1 << " " << match << "\n";
				}
			}
		}

		int pos = (strlen(start) - 1);

		prevCh = start[0];
		memmove(start, start + 1, pos);
		start[pos] = 0;
		currCh = tolower(textFile.get());

		if (currCh == '\n')
		{
			countStr++;
			prevCount = i;
			i = 0;
			currCh = ' ';
		}
		start[pos] = currCh;

		Hash = (1 * (Hash - (((prevCh) * modVal) % ((2^32) - 5))) + (currCh)) % ((2^32) - 5);
	}

	if (!No)
	{
		outputFile << "No" << "\n";
	}
}

pair<string, string> fileRead(string inF)
{
	setlocale(LC_ALL, "Russian");

	ifstream inputFile;
	inputFile.open(inF);
	if (!inputFile.is_open())
	{
		exit(0);
	}

	char str[255];

	inputFile.getline(str, 255);

	string sample = str;

	transform(sample.begin(), sample.end(), sample.begin(), tolower);

	string fileName;

	inputFile >> fileName;

	pair<string, string> return_fileRead;

	return_fileRead.first = sample;
	return_fileRead.second = fileName;

	return return_fileRead;
}

int main()
{
	pair<string, string> args;

	args = fileRead("input.txt");

	findString(args);

	return 0;
}