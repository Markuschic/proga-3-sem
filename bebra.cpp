#include <iostream>
#include <fstream>
#include <cmath>

bool checkfile(std::ifstream &fin)
{
    if (!fin.is_open())
    {
        throw " file isn't exist ";
    }
    if (fin.peek() == EOF)
    {
        throw " file is empty ";
    }
    return true;
}

size_t amountdigits(std::ifstream &ifs)
{
    int number;
    size_t amount = 0;
    while (ifs >> number)
    {
        ++amount;
    }
    return amount;
}

size_t mtrxDimension(size_t count)
{
    return static_cast<size_t>(std::ceil(std::sqrt(static_cast<double>(count))));
}

void fill(std::ifstream &fin, int **matrix, size_t size)
{
    fin.clear();
    fin.seekg(0);
    size_t rows = 0;
    size_t cols = 0;
    int number;
    while (fin >> number)
    {
        matrix[rows][cols] = number;
        ++cols;
        if (cols >= size)
        {
            cols = 0;
            ++rows;
        }
        if (rows >= size)
        {
            break;
        }
    }
}

void print(std::ofstream &fout, int **matrix, size_t size)
{
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            fout << std::setw(5) << matrix[i][j] << ' ';
        }
        fout << '\n';
    }
}

void delmtrx(int **matrix, size_t size)
{
    for (int i = 0; i < size; ++i)
    {
        delete[] matrix[i];
    }
    delete[] matrix;
}

int main()
{
    std::ifstream ifs("input.txt");
    std::ofstream ofs("output.txt");
    try
    {
        checkfile(ifs);
        size_t count = amountdigits(ifs);
        size_t dimension = mtrxDimension(count);
        int **matrix = new int *[dimension];
        for (int i = 0; i < dimension; ++i)
        {
            matrix[i] = new int[dimension];
        }
        fill(ifs, matrix, dimension);
        print(ofs, matrix, dimension);
        delmtrx(matrix, dimension);
        ifs.close();
        ofs.close();
    }
    catch (const char *msg)
    {
        std::cerr << msg << '\n';
    }
}