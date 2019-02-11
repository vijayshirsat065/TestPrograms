#include <iostream>
#include <vector>

using namespace std;

struct Sample
{
    int SampleTime;
    int SamplePosition;
};

int getInterpolatedValue(int minTime, int maxTime, int minPosition, int maxPosition, int inputTime)
{
    int interpolatedPosition = 0;

    int timeDiff = ((inputTime - minTime) / (maxTime - minTime)) * 100;

    interpolatedPosition = (timeDiff / 100) * (maxPosition - minPosition);

    return interpolatedPosition;
}

vector<Sample> InterpolateDataset(const vector<Sample>& inputSamples, int newSampleTime)
{
    vector<Sample> outputSamples;
    
    Sample tempSample;
    
    int minSampleTime = get the min sample time;
    int maxSampleTime = inputSamples;

    for(int i = 0; i < ((maxSampleTime - minSampleTime)/ newSampleTime))


    for(Sample& sample : outputSamples)
    {

    }
}

int main()
{
    return 0;
}