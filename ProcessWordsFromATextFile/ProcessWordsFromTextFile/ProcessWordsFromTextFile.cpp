///Name: Vijay Shirsat  |  Email: vijayshirsat065@gmail.com  |  Microsoft Studio 2017 Community Edition

/**
 *  Write a console application in C++ that reads input from the attached text file pride - and-prejudiceANSII.txt and outputs some statistics.
 *	Before processing, discard any words consisting of a single character and any words in the attached file stop_words.txt
 *	Any non - alphabetic characters should be converted to spaces before processing the input text.
 *	Words differing only in the case of the characters are considered to be identical
 *	From the input, the following should be calculated :
 *	The number of words entered and the number of distinct words.
 *	The mean, median, mode, and range of all word lengths(including identical words).
 *	The five most common and the five least common words.
 *	The five most common and the five least common letters.
**/

#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <cctype>
#include <functional>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iterator>

using namespace std;

template<typename KeyType>
void PopulatePairFromMapAndSortItByValueType(const map<KeyType, int>& MapToBeRead,
	vector<pair<KeyType, int>>& vectorOfPairsToBeSorted)
{
	for (auto itr = MapToBeRead.cbegin(); itr != MapToBeRead.cend(); ++itr)
		vectorOfPairsToBeSorted.push_back(*itr);

	sort(vectorOfPairsToBeSorted.begin(), vectorOfPairsToBeSorted.end(),
		[=](pair<KeyType, int>& a, pair<KeyType, int>& b) { return a.second < b.second; });
}

float FindMedianOfKeysOfAMap(const map<int, int>& mapOfNumbersAsKeys)
{
	float median = 0.0f;
	if ((mapOfNumbersAsKeys.size() % 2) == 0)
	{
		auto middleElementIterator = mapOfNumbersAsKeys.cbegin();
		advance(middleElementIterator, ((mapOfNumbersAsKeys.size() - 1) / 2));

		int firstMiddleElement = middleElementIterator->first;
		++middleElementIterator;

		median = (firstMiddleElement + middleElementIterator->first) / 2.0f;
	}
	else
	{
		auto middleElementIterator = mapOfNumbersAsKeys.cbegin();
		advance(middleElementIterator, (mapOfNumbersAsKeys.size() / 2));
		median = static_cast<float>(middleElementIterator->first);
	}
	return median;
}

void FindKeysInAMapWithHighestValues(const map<int, int>& mapOfNumbersAndOccurrenceCount, vector<int>& listOfKeysWithHighestValues)
{
	vector<pair<int, int>> sortedValuePairs;
	PopulatePairFromMapAndSortItByValueType(mapOfNumbersAndOccurrenceCount, sortedValuePairs);

	int previousValue = sortedValuePairs.rbegin()->second;
	for (auto modeElementsIterator = sortedValuePairs.rbegin();
		modeElementsIterator != sortedValuePairs.rend();
		++modeElementsIterator)
	{
		if (modeElementsIterator->second == previousValue)
		{
			listOfKeysWithHighestValues.push_back(modeElementsIterator->first);
		}
		else
		{
			break;
		}
	}
}

int main()
{
	const char* STOP_WORDS_FILE_NAME = "stop_words.txt";

	cout << "Loading stop words from '" << STOP_WORDS_FILE_NAME << "' file" << endl << endl;

	map<string, int> stopWordsMap;

	//Create a map of stop_words
	ifstream stopWordsFile(STOP_WORDS_FILE_NAME);
	char nextStopWordCharacter = '\0';
	string stopWord;
	if (stopWordsFile.is_open())
	{
		while (stopWordsFile.get(nextStopWordCharacter))
		{
			if (isalpha(nextStopWordCharacter))
			{
				stopWord += nextStopWordCharacter;
			}
			else
			{
				//If any non-alphabetic character is encountered, convert it to space and consider it as end of a word
				nextStopWordCharacter = ' ';

				//Discard single letter words
				if(stopWord.size() > 1)
				{
					stopWordsMap[stopWord] = stopWordsMap[stopWord] + 1;
				}

				stopWord.clear();
			}
		}

		if (stopWord.size() > 1)
		{
			stopWordsMap[stopWord] = stopWordsMap[stopWord] + 1;
		}

		stopWord.clear();
	}
	else
	{
		cout << "Failed to open '" << STOP_WORDS_FILE_NAME << "' file. No stop words loaded." << endl << endl;
	}



	const char* INPUT_FILE_NAME = "pride-and-prejudiceANSII.txt";

	ifstream inputFile(INPUT_FILE_NAME);

	if (inputFile.is_open())
	{	
		cout << "Reading '" << INPUT_FILE_NAME  << "' file and processing text." << endl << endl;

		map<string /*word*/, int /*number of occurrences*/> wordCountMap;
		map<string /*distinct word*/, int /*number of occurrences*/> distinctWordCountMap;
		map<string /*letter*/, int /*number of occurrences*/> letterCountMap;
		map<int /*length of word*/, int /*number of occurrences*/> lengthsOfAllWords;

		int numberOfWordsEntered = 0;
		size_t sumOfLengthOfAllWords = 0;

		char nextCharacterInFile = '\0';
		string currentWord;

		//A convenient lambda function for checking if a word break happens and handles it
		auto checkForWordBreak = [&]() {
			//Only add valid words to word map
			if ((currentWord.length() > 1) && (stopWordsMap.find(currentWord) == stopWordsMap.end()))
			{
				wordCountMap[currentWord] = wordCountMap[currentWord] + 1;
				++numberOfWordsEntered;
				lengthsOfAllWords[static_cast<int>(currentWord.length())] = lengthsOfAllWords[static_cast<int>(currentWord.length())] + 1;
				sumOfLengthOfAllWords += currentWord.length();
				std::transform(currentWord.begin(), currentWord.end(), currentWord.begin(), ::tolower);
				distinctWordCountMap[currentWord] = distinctWordCountMap[currentWord] + 1;
			}
			else
			{
				//Discard single character words
			}
			currentWord.clear();
		};

		//Start reading characters from the input text
		while (inputFile.get(nextCharacterInFile))
		{
			//If any non-alphabetic character is encountered, convert it to space
			if (!isalpha(nextCharacterInFile))
			{
				nextCharacterInFile = ' ';
			}

			if (isalpha(nextCharacterInFile))
			{
				currentWord += nextCharacterInFile;

				string tempString;
				tempString += nextCharacterInFile;
				letterCountMap[tempString] = letterCountMap[tempString] + 1;
			}
			else if(' ' == nextCharacterInFile)
			{
				checkForWordBreak();
			}
			else
			{
				//Ignore
			}
		}

		//Check for corner condition in case the file's last word gets missed 
		checkForWordBreak();

		cout << "Total Number Of Words : " << numberOfWordsEntered << endl;
		cout << "Number Of Distinct Words : " << distinctWordCountMap.size() << endl << endl;

		cout << "Mean of Lengths Of All Words : " << sumOfLengthOfAllWords / static_cast<double>(numberOfWordsEntered) << endl;

		cout << "Median Of Lengths Of All Words : " << FindMedianOfKeysOfAMap(lengthsOfAllWords) << endl;

		vector<int> modesOfLengths;
		//'lengthsOfAllWords' map contains lengths of all words and their occurence counts.
		//The following functions converts the map into a sorted vector of pairs,
		//where the sorting happens on the basis of value type and then finds the keys with highest values
		FindKeysInAMapWithHighestValues(lengthsOfAllWords, modesOfLengths);

		if (modesOfLengths.size() == 1)
		{
			cout << "Mode Of Lengths Of All Words : " << modesOfLengths[0];
		}
		else
		{
			cout << "Modes Of Lengths Of All Words : ";
			for (int mode : modesOfLengths)
			{
				cout << mode << "  ";
			}
		}
		cout << endl;

		cout << "Range Of Lengths Of All Words : " << (lengthsOfAllWords.rbegin()->first - lengthsOfAllWords.begin()->first) << endl << endl;

		constexpr int numberOfCommonOccurrencesToBeDisplayed = 5;

		//A generic function to print top five and bottom five elements in the sorted vector
		auto printFiveMostAndFiveLeastOccurrences = [&numberOfCommonOccurrencesToBeDisplayed](const vector<pair<string, int>>& pairs, const string& textToBeDisplayed) {
			cout << "Five Most Common " << textToBeDisplayed << " : " << endl;
			int iterationCount = 1;
			for (int j = (static_cast<int>(pairs.size()) - 1); j >= 0; --j)
			{
				cout << pairs.at(j).first << " | ";
				++iterationCount;

				if (numberOfCommonOccurrencesToBeDisplayed < iterationCount)
				{
					break;
				}
			}
			cout << endl << endl;

			if (!pairs.empty())
			{
				cout << "Five Least Common " << textToBeDisplayed << " : " << endl;
				for (int i = 0; ((i < numberOfCommonOccurrencesToBeDisplayed) && (i < pairs.size())); ++i)
				{
					cout << pairs.at(i).first << " | ";
				}
				cout << endl << endl;
			}
		};

		vector<pair<string, int>> sortedWordCountPairs;
		PopulatePairFromMapAndSortItByValueType(wordCountMap, sortedWordCountPairs);
		printFiveMostAndFiveLeastOccurrences(sortedWordCountPairs, "Words");

		vector<pair<string, int>> sortedLetterCountPairs;
		PopulatePairFromMapAndSortItByValueType(letterCountMap, sortedLetterCountPairs);
		printFiveMostAndFiveLeastOccurrences(sortedLetterCountPairs, "Letters");

		inputFile.close();
	}
	else
	{
		cout << "Failed to Open Input File '" << INPUT_FILE_NAME << "'" << endl;
	}

	getchar();

	return 0;
}