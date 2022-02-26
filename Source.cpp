#include <iostream>
#include <stdlib.h> 
#include <time.h> 
#include <string>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

map<string, bool> Dictionary;

void fillDictionary(std::string path) {
	string line, lineToLow;
	ifstream file;

	cout << "Loading dictionary from file for Part 2...";

	file.open(path);

	while (file)
	{
		if (getline(file, line))
		{
			lineToLow = "";

			for (int index = 0; index < line.length(); index++)
			{
				lineToLow += tolower(line.at(index));
			}

			Dictionary.insert(make_pair(lineToLow, true));
		}
	}

	file.close();

	cout << endl << endl;
}

void fillMap(map<string, int>& Frequency, string text)
{
	string word = "";

	for (int index = 0; index < text.length(); index++) {
		int chNum = text.at(index);
		string letter(1, char(chNum));

		if (chNum <= 'z' && chNum >= 'a')
		{
			Frequency[letter]++;
			word += char(chNum);
		}
		if (chNum == ' ' || (index + 1 == text.length() && word != ""))
		{
			if(word.length()!= 1)
				Frequency[word]++;
			word = "";
		}
	}
}

string Read(string path) {
	string data = "";
	string line;
	ifstream file;

	file.open(path);

	while (file)
	{
		if (getline(file, line))
		{
			data += line;
		}
	}

	file.close();

	return data;
}

string shiftText(string text, int shift)
{
	string result = "";

	if (shift > 25 || shift < -25)
	{
		while (!(shift < 26 && shift > -26))
		{
			shift = (shift % 26);
		}
	}

	for (int index = 0; index < text.length(); index++) {
		int chNum = text.at(index);

		if (chNum <= 'z' && chNum >= 'a')
		{
			if ((chNum + shift) > 'z')
				chNum = abs(122 - chNum - shift) - 1 + 97;
			else if ((chNum + shift) < 'a')
				chNum = 122 + (chNum + shift - 97) + 1;
			else
				chNum += shift;

			result += (char(chNum));
		}
		else
			result += (char(chNum));
	}

	return result;
}

int countWords(string text)
{
	int rightWords = 0;
	int totalWords = 0;
	string word = "";

	for (int index = 0; index < text.length(); index++) {
		int chNum = text.at(index);

		if (chNum <= 'z' && chNum >= 'a')
		{
			word += char(chNum);
		}
		if (chNum == ' ' || (index + 1 == text.length() && word != ""))
		{
			if (Dictionary[word])
				rightWords++;

			totalWords++;
			word = "";
		}
	}

	return (((float)rightWords/ totalWords) * 100);
}

int decypher(string origin, string cypher)
{
	int shift = 0;

	while (origin != shiftText(cypher, shift))
	{
			shift++;
	}

	return shift;
}

void Part_1(string text)
{
	int shift = 0;
	int option = 1;

	cout << "---------------------------------------------------------------"<< endl;
	cout << "Part 1 - Caesar Cipher:" << endl << endl;
	while (option)
	{
		cout << "Normal text: " << endl << text << endl << endl;
		cout << "For shifting to left, simply put minus sign." << endl;
		cout << "Enter how much to shift: ";
		cin >> shift;

		cout << endl << endl;

		cout << "Cipher Text: " << endl << shiftText(text, shift) << endl << endl;

		cout << "Do you want to try again?" << endl;
		cout << "0) No" << endl;
		cout << "1) Yes" << endl;

		cin >> option;

		cout << endl << endl;
	}
}

void Part_2(string cyphered)
{
	string encypheredText, answer = "n";
	int shift = 0;
	int trueWordPercent = 0;

	cout << "---------------------------------------------------------------" << endl;
	cout << "Part 2 - Code Breaker:" << endl << endl;

	cout << "Code Breaker" << endl << endl;

	cout << "Cyphered text looks like: " << endl << endl << cyphered << endl << endl;

	while (answer == "n")
	{
		encypheredText = "";
		encypheredText = shiftText(cyphered, shift);
		trueWordPercent = countWords(encypheredText);

		if (trueWordPercent > 90)
		{
			cout << "Normal text looks like: " << endl << endl << encypheredText << endl << endl;
			cout << "Left shift equals to " << abs(shift) << " | Right Words Percentage: " << trueWordPercent << endl << endl;
			cout << "Is encyphered text displayed correctly? Y/n?" << endl;
			cin >> answer;

			cout << endl << endl;
		}

		shift--;
	}
}

void Part_3(string originText, string cypherText)
{
	int maxFreq[2] = { 0, 0 };
	string frequence[2] = { "", ""};
	string result = "";
	int shift = 0;
	map<string, int> Freq;
	map<string, int> FreqCypher;

	cout << "---------------------------------------------------------------" << endl;
	cout << "Part 3 - Better guess:" << endl << endl;

	fillMap(Freq, originText);
	fillMap(FreqCypher, cypherText);

	for (auto& it : Freq) {
		if (maxFreq[0] < it.second)
		{
			maxFreq[0] = it.second;
			frequence[0] = it.first;
		}
	}

	for (auto& it : FreqCypher) {
		if (maxFreq[1] < it.second)
		{
			maxFreq[1] = it.second;
			frequence[1] = it.first;
		}
	}

	if (maxFreq[0] == maxFreq[1])
	{
		shift = decypher(frequence[0], frequence[1]);

		cout << "Letter/word with high and same frequency was found." << endl << endl;
		cout << "This letter / word: " << endl;
		cout << frequence[0] << endl << frequence[1] << endl << endl;
		cout << "Both has frequency of ";
		cout << maxFreq[0] << endl << endl;
		cout << "Your shift to decypher text is ";
		cout << shift << endl << endl << "Decyphered Text:" << endl << shiftText(cypherText, shift) << endl;
	}
	else
	{
		cout << "Letter/word with high and same frequency was not found. \n\n";
	}
}

void main()
{
	string files[3] = { "res/words.txt", "res/ciphertext.txt", "res/origintext.txt" };
	string cypherText = Read(files[1]); 
	string originText = Read(files[2]);

	Part_1(originText);

	fillDictionary(files[0]);

	Part_2(cypherText);

	Part_3(originText, cypherText);
}

