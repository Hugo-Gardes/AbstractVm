/*
** EPITECH PROJECT, 2022
** B-SYN-400-MPL-4-1-abstractVM-hugo.gardes
** File description:
** Do_exec.hpp
*/

#ifndef __Do_exec_H__
    #define __Do_exec_H__

    #include "var.hpp"
    #include "Factory.hpp"
    #include "parseCommand.hpp"
    #include <list>
    #include <csetjmp>
    #include <map>

class Do_exec
{
    private:
        static void push(std::string &, eOperandType);
        static void pop(std::string &, eOperandType);
        static void dump(std::string &, eOperandType);
        static void clear(std::string &, eOperandType);
        static void dup(std::string &, eOperandType);
        static void swap(std::string &, eOperandType);
        static void assert(std::string &, eOperandType);
        static void add(std::string &, eOperandType);
        static void sub(std::string &, eOperandType);
        static void mul(std::string &, eOperandType);
        static void div(std::string &, eOperandType);
        static void mod(std::string &, eOperandType);
        static void load(std::string &, eOperandType);
        static void store(std::string &, eOperandType);
        static void print(std::string &, eOperandType);
        static void exit(std::string &, eOperandType);
        static void err(std::string &, eOperandType);

    public:
        void exec_instruction(std::string &, eOperandType, std::string &);
        void main_loop(parseCommand &, std::jmp_buf *);
        Do_exec();
        ~Do_exec();
};

#endif