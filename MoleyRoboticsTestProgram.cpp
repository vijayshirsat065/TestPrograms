#include <iostream>
#include <vector>

using namespace std;

std::pair<int, int> CheckTargetSumAndReturnIndexes(const vector<int>& inputList, const int& targetSum)
{
    std::pair<int, int> indexes;
    indexes.first = -1;
    indexes.second = -1;

    bool sumFound = false;
    for(int i = 0; i < inputList.size(); ++i)
    {
        for(int j = i; j < inputList.size(); ++j)
        {
            if(targetSum == (inputList[i] + inputList[j]))
            {
                indexes.first = i;
                indexes.second = j;
                sumFound = true;
                break;
            }
        }

        if(sumFound)
        {
            break;
        }
    }

    return indexes;
}

int main()
{
    vector<int> inputList = {2,6,8,33,21,9};

    std::pair<int, int> indexes;
    indexes = CheckTargetSumAndReturnIndexes(inputList, 11);

    cout << "First Index : " << indexes.first << endl;
    cout << "Second Index : " << indexes.second << endl;
    return 0;
}