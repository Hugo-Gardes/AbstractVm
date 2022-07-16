/*
** EPITECH PROJECT, 2022
** B-SYN-400-MPL-4-1-abstractVM-hugo.gardes
** File description:
** var.hpp
*/

#ifndef __var_H__
    #define __var_H__
    #include "IOperands.hpp"
    #include <sstream>
    #include <map>
    #include <iostream>
    #include <typeinfo>
    #include <limits>
    #include "Factory.hpp"

class Abstract_var: public virtual IOperand {
    public:
        virtual std::string toString() const = 0;
        virtual eOperandType getType() const = 0;
        ~Abstract_var(){};
};

template <typename T>
class var: public virtual Abstract_var {
    eOperandType type;
    T value;
    public:
        var(eOperandType ty, T valu) {
            value = valu;
            type = ty;
        }

        std::string toString() const {
            std::stringstream ss;
            if (type == 64 || type == 128 || type == 256) {
                ss.precision((type == 64) ? 7 : (type == 128) ? 15 : 15);
            }
            ss << value;
            // std::cout << "ss: " << ss.str() << std::endl;
            // std::printf("%.7f\n", value);
            return (ss.str());
        }; // string that represents the instance

        eOperandType getType() const {
            return (type);
        } // returns the type of instance

        IOperand *operator+(const IOperand &rhs) const {
            std::stringstream ss;
            eOperandType rhst = rhs.getType();
            long double var1;
            try {
                var1 = std::stold(rhs.toString());
            } catch (const std::exception &e) {
                throw e.what();
            }
            ss << std::setprecision(15);
            ss << var1 + value;
            return (Factory::createOperand((type < rhst) ? rhst : type, ss.str()));
        }; // sum

        IOperand *operator-(const IOperand &rhs) const {
            std::stringstream ss;
            eOperandType rhst = rhs.getType();
            long double var1;
            try {
                var1 = std::stold(rhs.toString());
            } catch (const std::exception &e) {
                throw e.what();
            }
            ss << std::setprecision(15);
            ss << var1 - value;
            return (Factory::createOperand((type < rhst) ? rhst : type, ss.str()));
        }; // difference

        IOperand *operator*(const IOperand &rhs) const {
            std::stringstream ss;
            eOperandType rhst = rhs.getType();
            long double var1;
            try {
                var1 = std::stold(rhs.toString());
            } catch (const std::exception &e) {
                throw e.what();
            }
            ss << std::setprecision(15);
            ss << value * var1;
            return (Factory::createOperand((type < rhst) ? rhst : type, ss.str()));
        }; // product

        IOperand *operator/(const IOperand &rhs) const {
            std::stringstream ss;
            eOperandType rhst = rhs.getType();
            long double var1;
            try {
                var1 = std::stold(rhs.toString());
            } catch (const std::exception &e) {
                throw e.what();
            }
            if (!(long double)value) {
                ss << "Invalid argument for division (first: " << value << " second: " << var1 << ") abort";
                throw std::invalid_argument(ss.str());
            }
            ss << std::setprecision(15);
            ss << var1 / value;
            return (Factory::createOperand((type < rhst) ? rhst : type, ss.str()));
        }; // quotient

        IOperand *operator%(const IOperand &rhs) const {
            std::stringstream ss;
            eOperandType rhst = rhs.getType();
            long var1;
            try {
                var1 = std::stol(rhs.toString());
            } catch (const std::exception &e) {
                throw e.what();
            }
            if (!(long)value) {
                ss << "Invalid argument for modulo (first: " << var1 << " second: " << (long)value << ") abort";
                throw std::invalid_argument(ss.str());
            }
            ss << std::setprecision(15);
            ss << var1 % (long)value;
            return (Factory::createOperand((type < rhst) ? rhst : type, ss.str()));
        }; // modulo
};

#endif