/*
** EPITECH PROJECT, 2022
** B-SYN-400-MPL-4-1-abstractVM-hugo.gardes
** File description:
** IOperands.hpp
*/

#ifndef __IOperands_H__
    #define __IOperands_H__

    #include <string>

enum eOperandType {
    Int8 = 8,
    Int16 = 16,
    Int32 = 32,
    Float = 64,
    Double = 128,
    BigDecimal = 256,
    undefined = -1
};

class IOperand {
    public:
        virtual std::string toString() const = 0; // string that represents the instance
        virtual eOperandType getType() const = 0; // returns the type of instance
        virtual IOperand *operator+(const IOperand &rhs) const = 0; // sum
        virtual IOperand *operator-(const IOperand &rhs) const = 0; // difference
        virtual IOperand *operator*(const IOperand &rhs) const = 0; // product
        virtual IOperand *operator/(const IOperand &rhs) const = 0; // quotient
        virtual IOperand *operator%(const IOperand &rhs) const = 0; // modulo
        virtual ~IOperand(){}
};

#endif