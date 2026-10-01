// #include <iostream>
// #include <fstream>
// #include <sstream>

// int main()
// {
//     std::string filename = "bebra.txt";
//     std::fstream file(filename);
//     std::string stroka;

//     std::getline(file, stroka);
//     std::cout << stroka << '\n';
//     return 0;
// }

#include <iostream>
#include <sstream>
#include <fstream>

int main()
{
    std::fstream filename("bebra.txt");
    std::stringstream bufer;
    bufer << filename.rdbuf();
    std::string copystr = bufer.str();
    std::cout << copystr << '\n';
    return 0;
}