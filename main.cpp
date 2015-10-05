#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <thread>
#include <set>

#include "CRingBuffer.h"

using std::set;
using std::string;
using std::ifstream;
using std::thread;
using std::cout;
using std::endl;

void inserter(const string& fileName, CRingBuffer& ringBuffer, bool& isInserterRunning)
{
    ifstream input(fileName, ifstream::in);
    string inputString;
    while (!input.eof())
    {
        std::getline(input, inputString, ';');
        if (!inputString.empty())
        {
            ringBuffer.push_back(atof(inputString.c_str()));
        }
    }
    input.close();
    isInserterRunning = false;
}

void remover(set<float>& output, CRingBuffer& ringBuffer, bool& isInserterRunning)
{
    float digit;
    while (isInserterRunning)
    {
        if (ringBuffer.read(digit))
        {
            output.insert(digit);
        }
    }
}

int main(int argc, char* argv[])
{
    if (argc == 2)
    {
        set<float> output;
        CRingBuffer ringBuffer(10);

        bool isInserterRunning = true;
        const auto start = std::chrono::high_resolution_clock::now();
        thread insertThread(inserter, argv[1], std::ref(ringBuffer), std::ref(isInserterRunning));
        thread removeThread(remover, std::ref(output), std::ref(ringBuffer), std::ref(isInserterRunning));
        insertThread.join();
        removeThread.join();
        const auto end = std::chrono::high_resolution_clock::now();

        cout << "Analyse time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms\n";

        cout << "Result: ";
        for (auto digit : output)
        {
            cout << digit << " ";
        }
    }
    else
    {
        cout << "Specify input csv file" << endl;
    }
    return 0;
}
