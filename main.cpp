#include <iostream>
#include <fstream>
#include <string>
#include <thread>

#include "CRingBuffer.h"

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

void remover(CRingBuffer& ringBuffer)
{
    float digit;
    while (flag)
    {
        if (ringBuffer.read(digit))
        {
            cout << digit << " ";
        }
    }
}

int main(int argc, char* argv[])
{
    if (argc == 2)
    {
        CRingBuffer ringBuffer(10);
        thread insertThread(inserter, argv[1], std::ref(ringBuffer));
        thread removeThread(remover, std::ref(ringBuffer));
        insertThread.join();
        removeThread.join();
    }
    else
    {
        cout << "Specify input svg file" << endl;
    }
    return 0;
}
