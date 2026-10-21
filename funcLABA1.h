#pragma once
#include <iostream>
#include <fstream>
#include <string>
bool checkfile(std::ifstream &fin);

bool checkpalindrom(const std::string &word);

std::string *bufer_palindroms(std::ifstream &fin, size_t &counter);

void print_palindroms(std::string *bufer, size_t size);