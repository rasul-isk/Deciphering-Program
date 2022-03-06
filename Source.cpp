//Name:		Rasul Iskandarov
//Date:		28/02/2022

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
	int accuracy = 0;

	cout << "---------------------------------------------------------------" << endl;
	cout << "Part 2 - Code Breaker:" << endl << endl;

	cout << "Code Breaker" << endl << endl;

	cout << "Cyphered text looks like: " << endl << endl << cyphered << endl << endl;

	cout << "How much decyphering accuracy do you want? (0-100)" << endl;
	cout << "More than or equal to ";
	cin >> accuracy;
	cout << endl << endl;

	while (true)
	{
		if (accuracy <= 100 && accuracy >= 0)
		{
			while (answer == "n" && shift !=-100)
			{
				encypheredText = "";
				encypheredText = shiftText(cyphered, shift);
				trueWordPercent = countWords(encypheredText);

				if (trueWordPercent >= accuracy && shift != -100)
				{
					cout << "Normal text looks like: " << endl << endl << encypheredText << endl << endl;
					cout << "Left shift equals to " << abs(shift) << " | Right Words Percentage: " << trueWordPercent << endl << endl;
					cout << "Is encyphered text displayed correctly? Y/n?" << endl;
					cin >> answer;	

					cout << endl << endl;
				}

				shift--;
			}
			if (shift == -100)
				cout << "Accuracy not found." << endl << endl;
			break;
		}
		else
		{
			cout << "Please enter correct number. From 0 to 100." << endl << endl;
		}
	}
}

void Part_3(string originText, string cypherText)
{
	int maxFreq[2];
	int request = 0;
	int repeat = 0;
	string frequence[2] = { "", ""};
	string result = "";
	int shift = 0;
	map<string, int> Freq;
	map<string, int> FreqCypher;
	string answer = "n";

	cout << "---------------------------------------------------------------" << endl;
	cout << "Part 3 - Better guess:" << endl << endl;

	fillMap(Freq, originText);
	fillMap(FreqCypher, cypherText);

	while (answer == "n" && repeat < 20)
	{
		repeat++;
		request = 0;
		
		cout << "Enter maximum frequency can be used (minimum input 5): ";
		cin >> request;
		cin.ignore();
		cout << endl << endl;
		if (request > 5)
		{
			maxFreq[0] = 0;
			maxFreq[1] = 0;

			for (auto& it : Freq) {
				if (maxFreq[0] < it.second && it.second <= request)
				{
					maxFreq[0] = it.second;
					frequence[0] = it.first;
				}
			}

			for (auto& it : FreqCypher) {
				if (maxFreq[1] < it.second && it.second <= request)
				{
					maxFreq[1] = it.second;
					frequence[1] = it.first;
				}
			}

			if (maxFreq[0] == maxFreq[1])
			{
				shift = decypher(frequence[0], frequence[1]);

				cout << "Letter/word with high and same frequency was found!" << endl << endl;
				cout << "This letter / word: " << endl;
				cout << frequence[0] << " and " << frequence[1] << endl << endl;
				cout << "Both has frequency of ";
				cout << maxFreq[0] << endl << endl;
				cout << "Your shift to decypher text is ";
				cout << shift << endl << endl << "Decyphered Text:" << endl << shiftText(cypherText, shift) << endl;

				cout << "Is encyphered text displayed correctly? Y/n?" << endl;
				cin >> answer;
			}
			else
			{
				cout << "Letter/word with high and same frequency was not found. Try again.\n\n";
				answer = "n";
			}
		}
		else
		{
			cout << "Please enter correct number. From 0 to infinity." << endl << endl;
			answer = "n";
		}
	}

	if (repeat == 100)
		cout << "Fail to decipher." << endl << endl;

	cout << endl << "Bye!" << endl << endl;
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

