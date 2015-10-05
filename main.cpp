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

bool flag = true;

void inserter(const string& fileName, CRingBuffer& ringBuffer)
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
    flag = false;
}

void remover(set<float>& output, CRingBuffer& ringBuffer)
{
    float digit;
    while (flag)
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

        const std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();
        thread insertThread(inserter, argv[1], std::ref(ringBuffer));
        thread removeThread(remover, std::ref(output), std::ref(ringBuffer));
        insertThread.join();
        removeThread.join();
        const std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();

        cout << "Analyse time: " << (end-start).count() << " ms" << endl;

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
