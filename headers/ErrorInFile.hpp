/*
** EPITECH PROJECT, 2022
** B-SYN-400-MPL-4-1-abstractVM-hugo.gardes
** File description:
** ErrorInFile.hpp
*/

#ifndef __ERRORINFILE__
#define __ERRORINFILE__
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <regex>

class ErrorInFile : public std::exception
{
public:
    int nb_exit = 0;
    ErrorInFile();
    void verifLine(std::string &);
    void isExit(std::string &);
    void verifExit();
    void verifIfValue(std::string &);
    void verifFileExist(bool is_open);
    ~ErrorInFile();
};

#endif