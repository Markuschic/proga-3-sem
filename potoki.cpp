#include <iostream>
#include <sstream>
#include <fstream>

bool checkfile(std::ifstream &fin)
{
    if (!fin.is_open())
    {
        throw "file isn't exist";
    }
    if (fin.peek() == EOF)
    {
        throw "file is empty";
    }
    return true;
}

bool checkword(const std::string &word1, const std::string &word2)
{
    if (word1.length() != word2.length())
    {
        return false;
    }
    int bufer[256]{0};
    for (int i = 0; i < word1.size(); ++i)
    {
        ++bufer[(unsigned char)word1[i]];
    }
    for (int i = 0; i < word2.size(); ++i)
    {
        --bufer[(unsigned char)word2[i]];
    }
    for (int i = 0; i < 256; ++i)
    {
        if (bufer[i] != 0)
        {
            return false;
        }
    }
    return true;
}
int main()
{
    std::ifstream ifs("input.txt");
    std::ofstream ofs("output.txt");
    std::ofstream data("data.txt");
    try
    {
        checkfile(ifs);
    }
    catch (const char *msg)
    {
        std::cerr << " Error" << msg << '\n';
    }
    std::string word;
    std::string prev_word;
    size_t count = 0;
    int number;
    while (ifs >> word)
    {
        std::istringstream iss(word);
        std::istringstream iss(prev_word);
        if (iss >> number && iss.eof())
        {
            data << number << '\n';
        }
        else
        {
            if (checkword(prev_word, word))
            {
                ++count;
                ofs << word << ":" << count << '\n';
            }
        }
    }
    ifs.close();
    ofs.close();
    return 0;
}