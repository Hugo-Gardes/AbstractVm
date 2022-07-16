/*
** EPITECH PROJECT, 2022
** B-SYN-400-MPL-4-1-abstractVM-hugo.gardes
** File description:
** Factory.hpp
*/

#ifndef __Factory_H__
    #define __Factory_H__

    #include "IOperands.hpp"
    #include <sstream>
    #include <map>
    #include <iostream>
    #include <list>
    #include <iomanip>

class Factory {
    private:
        static IOperand *createInt8(const std::string &value);
        static IOperand *createInt16(const std::string &value);
        static IOperand *createInt32(const std::string &value);
        static IOperand *createFloat(const std::string &value);
        static IOperand *createDouble(const std::string &value);
        static IOperand *createBigDecimal(const std::string &value);

    public:
        static IOperand *createOperand(eOperandType type, const std::string &value);

        Factory();
        ~Factory();
};

#endif
