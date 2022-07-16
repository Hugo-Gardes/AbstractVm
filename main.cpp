/*
** EPITECH PROJECT, 2022
** B-SYN-400-MPL-4-1-abstractVM-hugo.gardes
** File description:
** main.cpp
*/

#include "headers/parseCommand.hpp"
#include "Do_exec.hpp"

int main(int argc, char **argv)
{
    parseCommand *test;
    if (argc == 2) {
        test = new parseCommand(argv[1]);
    } else if (argc == 1) {
        test = new parseCommand();
    } else {
        std::cout << "Usage: ./abstractVM [file]" << std::endl;
        return (84);
    }
    if (test->error) {
        std::cerr << *test->err_txt << std::endl;
        delete test->err_txt;
        delete test;
        return (84);
    }
    std::jmp_buf buf;
    Do_exec exe;
    if (setjmp(buf) == 64) {
        delete test;
        return (0);
    }
    try {
        exe.main_loop(*test, &buf);
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        delete test;
        return (84);
    }
    std::cerr << "exit not found" << std::endl;
    delete test;
    return (84);
}

// 3,286