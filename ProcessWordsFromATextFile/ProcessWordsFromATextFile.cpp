//Name: Vijay Shirsat  |  Email: vijayshirsat065@gmail.com  |  Compiler: GCC 5.1.0

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <ctype.h>
#include <functional>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iterator>

using namespace std;

bool IsAValidCharacter(char& inputCharacter)
{
  bool returnValue = false;
  if(((inputCharacter >= 48) && (inputCharacter <= 57)) || 
     ((inputCharacter >= 65) && (inputCharacter <= 90)) ||
     ((inputCharacter >= 97) && (inputCharacter <= 122)))
  {
    returnValue = true;
  }
  return returnValue;
}

template<typename KeyType>
void PopulatePairFromMapAndSortItByValueType(const map<KeyType, int>& MapToBeRead, 
                                             vector<pair<KeyType, int>>& vectorOfPairsToBeSorted)
{
  for (auto itr = MapToBeRead.cbegin(); itr != MapToBeRead.cend(); ++itr)
    vectorOfPairsToBeSorted.push_back(*itr);

  sort(vectorOfPairsToBeSorted.begin(), vectorOfPairsToBeSorted.end(), 
       [=](pair<KeyType, int>& a, pair<KeyType, int>& b) { return a.second < b.second;});
}

float FindMedianOfKeysOfAMap(const map<int, int>& mapOfNumbersAsKeys)
{
    float median = 0.0f;
    if((mapOfNumbersAsKeys.size() % 2) == 0)
    {
      auto middleElementIterator = mapOfNumbersAsKeys.cbegin();
      advance(middleElementIterator, ((mapOfNumbersAsKeys.size()-1) / 2));

      int firstMiddleElement = middleElementIterator->first;
      ++middleElementIterator;

      median = (firstMiddleElement + middleElementIterator->first) / 2.0f;
    }
    else
    {
      auto middleElementIterator = mapOfNumbersAsKeys.cbegin();
      advance(middleElementIterator, (mapOfNumbersAsKeys.size() / 2));
      median = middleElementIterator->first;
    }
    return median;
}

void FindKeysInAMapWithHighestValues(const map<int, int>& mapOfNumbersAndOccurrenceCount, vector<int>& listOfKeysWithHighestValues)
{
  vector<pair<int, int>> sortedValuePairs;
  PopulatePairFromMapAndSortItByValueType(mapOfNumbersAndOccurrenceCount, sortedValuePairs);

  int previousValue = sortedValuePairs.rbegin()->second;
  for(auto modeElementsIterator = sortedValuePairs.rbegin();
           modeElementsIterator != sortedValuePairs.rend();
           ++modeElementsIterator)
  {
    if(modeElementsIterator->second == previousValue)
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
  const char* FILE_NAME = "InputFile.txt";

  ifstream inputFile(FILE_NAME);

  if(inputFile.is_open())
  {
    int numberOfSentencesEntered = 0;
    int numberOfWordsEntered = 0;
    map<string /*word*/, int /*number of occurrences*/> wordCountMap;
    map<string /*distinct word*/, int /*number of occurrences*/> distinctWordCountMap;
    map<string /*letter*/, int /*number of occurrences*/> letterCountMap;
    map<int /*length of word*/, int /*number of occurrences*/> lengthsOfAllWords;
    size_t sumOfLengthOfAllWords = 0;

    char nextCharacterInFile = '\0';
    string currentWord;

    //A convenient lambda function for checking if a word break happens and handles it
    auto checkForWordBreak = [&](){
      if(currentWord.length() > 1)
      {
        wordCountMap[currentWord] = wordCountMap.at(currentWord) + 1;
        ++numberOfWordsEntered;
        lengthsOfAllWords[currentWord.length()] = lengthsOfAllWords.at(currentWord.length()) + 1;
        sumOfLengthOfAllWords += currentWord.length();
        std::transform(currentWord.begin(), currentWord.end(), currentWord.begin(), ::tolower);
        distinctWordCountMap[currentWord] = distinctWordCountMap.at(currentWord) + 1;
        currentWord.clear();
      }
      else if(1 == currentWord.length())
      {
        letterCountMap[currentWord] = letterCountMap.at(currentWord) + 1;
        currentWord.clear();
      }
      else
      {
        //ignore
      }
    };

    while(inputFile.get(nextCharacterInFile))
    {
      if(nextCharacterInFile != '.')
      {
        if(IsAValidCharacter(nextCharacterInFile))
        {
          currentWord.append(1, nextCharacterInFile);
        }
        else
        {
          checkForWordBreak();
        }
      }
      else
      {
        checkForWordBreak();
        ++numberOfSentencesEntered;
      }
    }

    //Check for corner condition in case the file's last character is not '.' and the last sentence is incomplete
    checkForWordBreak();

    cout << "Number Of Sentences Entered : "      << numberOfSentencesEntered << endl;
    cout << "Total Number Of Words Entered : "    << numberOfWordsEntered     << endl;
    cout << "Number Of Distinct Words Entered : " << distinctWordCountMap.size()      << endl << endl;

    cout << "Mean of Lengths Of All Words : " << sumOfLengthOfAllWords/static_cast<double>(numberOfWordsEntered) << endl;

    cout << "Median Of Lengths Of All Words : " << FindMedianOfKeysOfAMap(lengthsOfAllWords) << endl;

    vector<int> modesOfLengths;
    //'lengthsOfAllWords' map contains lengths of all words and their occurence counts.
    //The following functions converts the map into a sorted vector of pairs,
    //where the sorting happens on the basis of value type and then finds the keys with highest values
    FindKeysInAMapWithHighestValues(lengthsOfAllWords, modesOfLengths);

    if(modesOfLengths.size() == 1)
    {
      cout << "Mode Of Lengths Of All Words : " << modesOfLengths[0];
    }
    else
    {
      cout << "Modes Of Lengths Of All Words : ";
      for(int mode : modesOfLengths)
      {
        cout << mode << "  ";
      }
    }
    cout << endl;

    cout << "Range Of Lengths Of All Words : " << (lengthsOfAllWords.rbegin()->first - lengthsOfAllWords.begin()->first) << endl << endl;

    constexpr int numberOfCommonOccurrencesToBeDisplayed = 5;

    //A generic function to print top five and bottom five elements in the sorted vector
    auto printFiveMostAndFiveLeastOccurrences = [&numberOfCommonOccurrencesToBeDisplayed](const vector<pair<string, int>>& pairs, const string& textToBeDisplayed){
        cout << "Five Most Common " << textToBeDisplayed << " : " << endl;
        int iterationCount = 1;
        for(int j = (pairs.size() - 1); j >= 0; --j)
        {
          cout << pairs.at(j).first << " | ";
          ++iterationCount;

          if(numberOfCommonOccurrencesToBeDisplayed < iterationCount)
          {
            break;
          }
        }
        cout << endl << endl;
      
      if(!pairs.empty())
      {
        cout << "Five Least Common " << textToBeDisplayed << " : " << endl;
        for(int i = 0; ((i < numberOfCommonOccurrencesToBeDisplayed) && (i < pairs.size())); ++i)
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
    cout << "Failed to Open File '" << FILE_NAME << "'";
  }
}