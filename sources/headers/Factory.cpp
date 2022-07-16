/*
** EPITECH PROJECT, 2022
** B-SYN-400-MPL-4-1-abstractVM-hugo.gardes
** File description:
** Factory.cpp
*/

#include "var.hpp"

static std::map<int, IOperand *(*)(const std::string &)> tranform;

Factory::Factory() {
    tranform[(int)eOperandType::Int8] = createInt8;
    tranform[(int)eOperandType::Int16] = createInt16;
    tranform[(int)eOperandType::Int32] = createInt32;
    tranform[(int)eOperandType::Float] = createFloat;
    tranform[(int)eOperandType::Double] = createDouble;
    tranform[(int)eOperandType::BigDecimal] = createBigDecimal;
    tranform[(int)eOperandType::undefined] = NULL;
};

IOperand *Factory::createInt8(const std::string &value)
{
    int val;
    std::stringstream ss;
    try {
        val = std::stoi(value);
    } catch (const std::exception &e) {
        ss << "cannot convert " << value << " to int8";
        throw std::runtime_error(ss.str());
    }
    if (val > 127 || val < -128) {
        ss << "Variable overflow expected value beetween 127 && -128: " << val;
        throw std::invalid_argument(ss.str());
    }
    return (new var<int>(eOperandType::Int8, val));
}

IOperand *Factory::createInt16(const std::string &value)
{
    int val;
    std::stringstream ss;
    try {
        val = stoi(value);
    } catch (const std::exception &e) {
        ss << "cannot convert " << value << " to int16";
        throw std::runtime_error(ss.str());
    }
    if (val > 32767 || val < -32768) {
        ss << val;
        throw std::invalid_argument("Variable overflow expected value beetween 32767 && -32768: " + ss.str());
    }
    return (new var<int>(eOperandType::Int16, val));
}

IOperand *Factory::createInt32(const std::string &value)
{
    long val;
    std::stringstream ss;
    try {
        val = stol(value);
    } catch (const std::exception &e) {
        ss << "cannot convert " << value << " to int32";
        throw std::runtime_error(ss.str());
    }
    if (val > 2147483647 || val < -2147483648) {
        ss << val;
        throw std::invalid_argument("Variable overflow expected value beetween 2147483647 && -2147483648: " + ss.str());
    }
    return (new var<int>(eOperandType::Int32, val));
}

IOperand *Factory::createFloat(const std::string &value)
{
    double val;
    std::stringstream ss;
    try {
        val = std::stod(value);
    } catch (const std::exception &e) {
        ss << "cannot convert " << value << " to float";
        throw std::runtime_error(ss.str());
    }
    if (val > std::numeric_limits<float>::max() || val < std::numeric_limits<float>::lowest()) {
        ss << "Variable overflow expected value beetween " << std::numeric_limits<float>::max() << " && " << std::numeric_limits<float>::lowest() << ": " << val;
        throw std::invalid_argument(ss.str());
    }
    return (new var<double>(eOperandType::Float, val));
}

IOperand *Factory::createDouble(const std::string &value)
{
    long double val;
    std::stringstream ss;
    try {
        val = stold(value);
    } catch (const std::exception &e) {
        ss << "cannot convert " << value << " to double";
        throw std::runtime_error(ss.str());
    }
    if (val > std::numeric_limits<double>::max() || val < std::numeric_limits<double>::lowest()) {
        ss << "Variable overflow expected value beetween " << std::numeric_limits<double>::max() << " && " << std::numeric_limits<double>::lowest() << ": " << val;
        throw std::invalid_argument(ss.str());
    }
    return (new var<double>(eOperandType::Double, val));
}

IOperand *Factory::createBigDecimal(const std::string &value)
{
    long double val;
    std::stringstream ss;
    try {
        val = stold(value);
    } catch (std::exception &e) {
        ss << "cannot convert " << value << " to BigDecimal";
        throw std::runtime_error(ss.str());
    }
    return (new var<long double>(eOperandType::BigDecimal, val));
}

IOperand *Factory::createOperand(eOperandType type, const std::string &value)
{
    return (tranform[type](value));
}

Factory::~Factory()
{
}