#include <iostream>
#include <fstream>
#include "funcLABA1.h"
bool checkfile(std::ifstream &fin)
{
    if (!fin.is_open())
    {
        throw "File wasn't opened";
    }
    if (fin.peek() == EOF)
    {
        throw "File is empty";
    }
    if (!fin.good())
    {
        throw "Error in file";
    }
    return true;
}

bool checkpalindrom(const std::string &word)
{
    size_t size = word.length();
    for (size_t i = 0, j = size - 1; i < size / 2; ++i, --j)
    {
        if (word[i] != word[j])
        {
            return false;
        }
    }
    return true;
}

std::string *bufer_palindroms(std::ifstream &fin, size_t &counter)
{
    size_t size = 5;
    counter = 0;
    std::string word;
    std::string *bufer = new std::string[size];
    while (fin >> word)
    {
        if (checkpalindrom(word))
        {
            if (counter == size)
            {
                size_t newsize = size * 2;
                std::string *newbufer = new std::string[newsize];
                for (size_t i = 0; i < counter; ++i)
                {
                    newbufer[i] = bufer[i];
                }
                delete[] bufer;
                bufer = newbufer;
                size = newsize;
            }
            bufer[counter] = word;
            ++counter;
        }
    }
    return bufer;
}

void print_palindroms(std::string *bufer, size_t size)
{
    size_t max = bufer[0].length();
    for (size_t i = 1; i < size; ++i)
    {
        if (bufer[i].length() > max)
        {
            max = bufer[i].length();
        }
    }
    for (size_t i = 0; i < size; ++i)
    {
        if (bufer[i].length() == max)
        {
            std::cout << bufer[i] << '\n';
        }
    }
}