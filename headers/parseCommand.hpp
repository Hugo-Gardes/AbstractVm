/*
** EPITECH PROJECT, 2022
** B-SYN-400-MPL-4-1-abstractVM-hugo.gardes
** File description:
** parseCommand.hpp
*/

#ifndef __PARSECOMMAND__
#define __PARSECOMMAND__

#include "ErrorInFile.hpp"
#include "IOperands.hpp"
#include <map>
#include <list>

class parseCommand : public ErrorInFile
{
public:
    std::list<std::string *> command_list;
    std::list<std::string *> all_command;
    std::list<std::string *> all_type;
    std::list<std::string *> all_value;
    std::list<eOperandType> all_enum;
    bool error = false;
    std::string *err_txt;
    std::map<std::string, eOperandType> possible_type = {
        {"int8", eOperandType::Int8},
        {"int16", eOperandType::Int16},
        {"int32", eOperandType::Int32},
        {"float", eOperandType::Float},
        {"double", eOperandType::Double},
        {"bigdecimal", eOperandType::BigDecimal}
    };
    parseCommand(char *filename);
    parseCommand();
    void parseLine(std::string &);
    std::string splitLine(std::string, std::string &, std::string);
    void getEnum(std::string &);
    void getFile(char *filename);
    void printAfterParsing();
    ~parseCommand();
};

#endif
