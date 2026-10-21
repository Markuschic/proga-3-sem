// Вариант 6
#include <iostream>
#include <fstream>
#include "funcLABA1.h"

int main()
{
    try
    {
        std::ifstream ifs("textLABA.txt");
        checkfile(ifs);
        size_t amount_palindroms = 0;
        std::string *buf_palindroms = bufer_palindroms(ifs, amount_palindroms);
        ifs.close();
        if (amount_palindroms > 0)
        {
            print_palindroms(buf_palindroms, amount_palindroms);
        }
        delete[] buf_palindroms;
    }
    catch (const char *msg)
    {
        std::cerr << msg << '\n';
    }
    return 0;
}
