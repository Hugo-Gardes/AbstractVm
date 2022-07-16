/*
** EPITECH PROJECT, 2022
** B-SYN-400-MPL-4-1-abstractVM-hugo.gardes
** File description:
** ErrorInFile.cpp
*/
#include "../../headers/ErrorInFile.hpp"

ErrorInFile::ErrorInFile()
{
    return;
}

void ErrorInFile::verifLine(std::string &s)
{
    std::string data = std::regex_replace(s, std::regex(" *( *(push|assert|store|load) +((int8|int16|int32)(\\(-?\\d+\\))( *;.*| *)|(float|double|bigdecimal)\\((-?\\d+.?\\d*)\\))( *;.*| *)| *(pop|dump|clear|dup|swap|add|sub|mul|div|mod|print|exit)( *;.*| *))"), "\n");

    if (data != "\0" && data != "\n") {
        throw std::invalid_argument("the line contains unnecessary characters: " + s);
    }
    return;
}

void ErrorInFile::verifFileExist(bool is_open)
{
    if (is_open == false)
        throw std::invalid_argument("the file doesn't exist");
    return;
}

void ErrorInFile::verifIfValue(std::string &value)
{
    if (value.compare("NULL") == 0)
        throw std::invalid_argument("no value enter");
    return;
}

ErrorInFile::~ErrorInFile()
{
    return;
}