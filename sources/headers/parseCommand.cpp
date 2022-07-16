/*
** EPITECH PROJECT, 2022
** B-SYN-400-MPL-4-1-abstractVM-hugo.gardes
** File description:
** parseCommand.cpp
*/
#include "../../headers/parseCommand.hpp"

parseCommand::parseCommand(char *filename)
{
    this->getFile(filename);
    try {
        for (auto &i : this->command_list) {
            this->parseLine(*i);
        }
    } catch (const std::exception &e) {
        for (auto &i : this->command_list) {
            delete i;
        }
        this->command_list.clear();
        for (auto &i : this->all_command) {
            delete i;
        }
        this->all_command.clear();
        for (auto &i : this->all_type) {
            delete i;
        }
        this->all_type.clear();
        this->all_enum.clear();
        for (auto &i : this->all_value) {
            delete i;
        }
        this->all_value.clear();
        this->error = true;
        this->err_txt = new std::string(e.what());
    }
}

parseCommand::parseCommand()
{
    std::string line;
    try {
        while (std::getline(std::cin, line) && line != ";;") {
            this->parseLine(line);
        }
    } catch (const std::exception &e) {
        for (auto &i : this->command_list) {
            delete i;
        }
        this->command_list.clear();
        for (auto &i : this->all_command) {
            delete i;
        }
        this->all_command.clear();
        for (auto &i : this->all_type) {
            delete i;
        }
        this->all_type.clear();
        this->all_enum.clear();
        for (auto &i : this->all_value) {
            delete i;
        }
        this->all_value.clear();
        this->error = true;
        this->err_txt = new std::string(e.what());
    }
}

void parseCommand::getFile(char *filename)
{
    std::ifstream file;
    std::string line;

    file.open(filename);
    this->verifFileExist(file.is_open());
    while (std::getline(file, line)) {
        this->command_list.push_back(new std::string(line));
    }
    file.close();
    return;
}

void parseCommand::parseLine(std::string &i)
{
    if (std::regex_replace(i, std::regex("^ *;.*|^ *"), "") == "") {
        return;
    }
    this->verifLine(i);
    this->all_command.push_back(new std::string(this->splitLine("^ *", i, "( +.*)")));
    this->all_type.push_back(new std::string(this->splitLine("((push|assert|store|load) +)|(pop|dump|clear|dup|swap|add|sub|mul|div|mod|print|exit)", i, "\\(.*")));
    getEnum(*this->all_type.back());
    this->all_value.push_back(new std::string(this->splitLine("((int8|int16|int32|float|double|bigdecimal)\\()", i, "\\).*")));
    if ((*(this->all_type.back())).compare("NULL") != 0) {
        this->verifIfValue(*(this->all_value.back()));
    }
    return;
}

void parseCommand::getEnum(std::string &type)
{
    auto &it = possible_type[type];
    if (!eOperandType(it))
        all_enum.push_back(eOperandType::undefined);
    else
        this->all_enum.push_back(it);
}

std::string parseCommand::splitLine(std::string before, std::string &line, std::string after)
{
    line = std::regex_replace(line, std::regex(before), "");
    std::string data = std::regex_replace(line, std::regex(after), "");
    if (data.compare("") == 0)
        data = "NULL";
    return (data);
}

void parseCommand::printAfterParsing()
{
    for (auto &a : this->all_command) {
        std::cout << *a << std::endl;
    }
    std::cout << "----------" << this->all_command.size() << "----------" << std::endl;
    for (auto &a : this->all_type) {
        std::cout << *a << std::endl;
    }
    std::cout << "----------" << this->all_type.size() << "----------" << std::endl;
    for (auto &a : this->all_enum) {
        std::cout << a << std::endl;
    }
    std::cout << "----------" << this->all_enum.size() << "----------" << std::endl;
    for (auto &a : this->all_value) {
        std::cout << *a << std::endl;
    }
    std::cout << "----------" << this->all_value.size() << "----------" << std::endl;
    return;
}

parseCommand::~parseCommand()
{
    for (auto &i : this->command_list) {
        delete i;
    }
    this->command_list.clear();
    for (auto &i : this->all_command) {
        delete i;
    }
    this->all_command.clear();
    for (auto &i : this->all_type) {
        delete i;
    }
    this->all_type.clear();
    this->all_enum.clear();
    for (auto &i : this->all_value) {
        delete i;
    }
    this->all_value.clear();
}
