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

volatile bool flag = true;

void inserter(const string& fileName, CRingBuffer& ringBuffer)
{
    ifstream input(fileName, ifstream::in);
    string inputString;
    getline(input, inputString, ';');
    while (!input.eof())
    {
        std::getline(input, inputString, ';');
        ringBuffer.push_back(atof(inputString.c_str()));
    }
    input.close();
    flag = false;
}

void remover(CRingBuffer& ringBuffer)
{
    while (flag)
    {
//        cout << flag;
        cout << ringBuffer.pop_front() << " ";
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
