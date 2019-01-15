#include "CreateASharedLibraryToReadNumbersFromAFile.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool CheckIfNumberedStringIsANonNegativeNumber(const string& numberedString)
{
    return ('-' != numberedString[0]);
}

bool DoesTheStringContainAllValidNumericCharacters(const string& inputString)
{
    bool isAValidNumber = true;
    for(const char& c : inputString)
    {
        if(!isdigit(c))
        {
           isAValidNumber = false;
           break; 
        }
    }
    return isAValidNumber;
}

bool IsTheInputStringAValidWholeNumber(const string& inputString)
{
    return (!inputString.empty() && 
            CheckIfNumberedStringIsANonNegativeNumber(inputString) && 
            DoesTheStringContainAllValidNumericCharacters(inputString));
}

int analyse(const char* input, const char* output)
{
    int operationResult = -1;
    ifstream inputFile(input);

    if(inputFile.is_open())
    {
        size_t nextCharPosition = 0;
        unsigned int numberOfLinesRead = 0;
        size_t sumOfAllNumbersRead = 0;

        string lineRead;
        while(getline(inputFile, lineRead))
        {
            if(IsTheInputStringAValidWholeNumber(lineRead))
            {
                unsigned long number = stoul(lineRead, &nextCharPosition, 10);

                ++numberOfLinesRead;
                sumOfAllNumbersRead += number;
                operationResult = 0;
            }
            else
            {
                operationResult = -1;
                break;
            }
        }

        if(0 == operationResult)
        {
            double average = (sumOfAllNumbersRead / static_cast<double>(numberOfLinesRead));

            ofstream outputFile;
            outputFile.open(output);
            outputFile << numberOfLinesRead << endl;
            outputFile << sumOfAllNumbersRead << endl;
            outputFile << average << endl;
        }
    }

    return operationResult;
}

int main()
{
    const char* INPUT_FILE_NAME = "InputFile.txt";
    const char* OUTPUT_FILE_NAME = "OutputFile.txt";

    analyse(INPUT_FILE_NAME, OUTPUT_FILE_NAME);

    return 0;
}
