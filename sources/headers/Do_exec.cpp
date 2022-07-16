/*
** EPITECH PROJECT, 2022
** B-SYN-400-MPL-4-1-abstractVM-hugo.gardes
** File description:
** Do_exec.cpp
*/

#include "Do_exec.hpp"
#include <algorithm>

static std::jmp_buf *exec_handler;
static std::list<IOperand *> stack;
static std::map<std::string, std::map<eOperandType, std::list<IOperand *>>> registers;
static std::map<std::string, void (*)(std::string &, eOperandType)> funct;

Do_exec::Do_exec()
{
    funct["push"] = push;
    funct["pop"] = pop;
    funct["dump"] = dump;
    funct["clear"] = clear;
    funct["dup"] = dup;
    funct["swap"] = swap;
    funct["assert"] = assert;
    funct["add"] = add;
    funct["sub"] = sub;
    funct["mul"] = mul;
    funct["div"] = div;
    funct["mod"] = mod;
    funct["load"] = load;
    funct["store"] = store;
    funct["print"] = print;
    funct["exit"] = exit;
    funct[";;"] = err;
}

void Do_exec::main_loop(parseCommand &parsed, std::jmp_buf *exec)
{
    auto e = parsed.all_enum.begin();
    auto v = parsed.all_value.begin();
    exec_handler = exec;
    for (auto c = parsed.all_command.begin(); c != parsed.all_command.end(); c++, e++, v++) {
        exec_instruction(*(*c), *e, *(*v));
    }
}

void Do_exec::exec_instruction(std::string &instruction, eOperandType type, std::string &arg)
{
    funct[instruction](arg, type);
}

void Do_exec::err(std::string &vallue, eOperandType type)
{
    (void)vallue;
    (void)type;
    throw std::runtime_error("exit is needed");
}

void Do_exec::push(std::string &vallue, eOperandType type)
{
    Factory fact;
    stack.push_front(fact.createOperand(type, vallue));
}

void Do_exec::pop(std::string &vallue, eOperandType type)
{
    (void)vallue;
    (void)type;
    if (!stack.size())
        throw std::runtime_error("Stack is empty");
    try {
        auto var = stack.front();
        stack.pop_front();
        delete (var);
    } catch (std::runtime_error &e) {
        throw e.what();
    }
}

void Do_exec::dump(std::string &vallue, eOperandType type)
{
    (void)type;
    (void)vallue;
    for (auto base = stack.begin(); base != stack.end(); base++) {
        try {
            std::cout << (*base)->toString() << std::endl;
        } catch (std::exception &e) {
            throw e.what();
        }
    }
}

void Do_exec::clear(std::string &vallue, eOperandType type)
{
    (void)vallue;
    (void)type;
    try {
        for (auto i = stack.begin(); i != stack.end(); i++) {
            delete (*i);
        }
        stack.clear();
    } catch (std::exception &e) {
        e.what();
    }
}

void Do_exec::dup(std::string &vallue, eOperandType type)
{
    Factory fact;
    (void)type;
    (void)vallue;
    if (!stack.size())
        throw std::runtime_error("stack is empty");
    stack.push_front(fact.createOperand(stack.front()->getType(), stack.front()->toString()));
}

void Do_exec::swap(std::string &vallue, eOperandType type)
{
    std::stringstream ss;
    (void)type;
    (void)vallue;
    if (stack.size() < 2) {
        ss << "Too few arguments in stack, size: " << stack.size();
        throw std::runtime_error(ss.str());
    }
    auto it1 = (stack.front());
    try {
        *stack.begin() = *(++stack.begin());
        *(++stack.begin()) = it1;
    } catch (const std::exception& e) {
        throw e.what();
    }
}

void Do_exec::assert(std::string &vallue, eOperandType type)
{
    (void)type;
    std::stringstream ss;
    if (!stack.size())
        throw std::runtime_error("Stack is empty");
    if (stold(stack.front()->toString()) != stold(vallue) || stack.front()->getType() != type) {
        ss << "Assertion failed: " << stack.front()->toString() << " != " << vallue << " or " << stack.front()->getType() << " != " << type;
        throw std::runtime_error(ss.str());
    }
}

void Do_exec::add(std::string &vallue, eOperandType type)
{
    std::stringstream ss;
    (void)type;
    (void)vallue;
    if (stack.size() < 2) {
        ss << "Stack size is less than 2, size: " << stack.size();
        throw std::runtime_error(ss.str());
    }
    auto it = stack.front();
    stack.pop_front();
    auto it2 = stack.front();
    auto res = (*it) + (*it2);
    stack.pop_front();
    delete (it);
    delete (it2);
    stack.push_front(Factory::createOperand(res->getType(), res->toString()));
    delete (res);
}

void Do_exec::sub(std::string &vallue, eOperandType type)
{
    Factory fact;
    std::stringstream ss;
    (void)type;
    (void)vallue;
    if (stack.size() < 2) {
        ss << "Stack size is less than 2, size: " << stack.size();
        throw std::runtime_error(ss.str());
    }
    auto it = stack.front();
    stack.pop_front();
    auto it2 = stack.front();
    auto res = (*it) - (*it2);
    stack.pop_front();
    delete (it);
    delete (it2);
    stack.push_front(fact.createOperand(res->getType(), res->toString()));
    delete (res);
}

void Do_exec::mul(std::string &vallue, eOperandType type)
{
    Factory fact;
    std::stringstream ss;
    (void)type;
    (void)vallue;
    if (stack.size() < 2) {
        ss << "Stack size is less than 2, size: " << stack.size();
        throw std::runtime_error(ss.str());
    }
    auto it = stack.front();
    stack.pop_front();
    auto it2 = stack.front();
    auto res = (*it) * (*it2);
    stack.pop_front();
    delete (it);
    delete (it2);
    stack.push_front(fact.createOperand(res->getType(), res->toString()));
    delete (res);
}

void Do_exec::div(std::string &vallue, eOperandType type)
{
    Factory fact;
    std::stringstream ss;
    (void)type;
    (void)vallue;
    if (stack.size() < 2) {
        ss << "Stack size is less than 2, size: " << stack.size();
        throw std::runtime_error(ss.str());
    }
    auto it = stack.front();
    stack.pop_front();
    auto it2 = stack.front();
    auto res = (*it) / (*it2);
    stack.pop_front();
    delete (it);
    delete (it2);
    stack.push_front(fact.createOperand(res->getType(), res->toString()));
    delete (res);
}

void Do_exec::mod(std::string &vallue, eOperandType type)
{
    Factory fact;
    std::stringstream ss;
    (void)type;
    (void)vallue;
    if (stack.size() < 2) {
        ss << "Stack size is less than 2, size: " << stack.size();
        throw std::runtime_error(ss.str());
    }
    auto it = stack.front();
    stack.pop_front();
    auto it2 = stack.front();
    auto res = (*it) % (*it2);
    stack.pop_front();
    delete (it);
    delete (it2);
    stack.push_front(fact.createOperand(res->getType(), res->toString()));
    delete (res);
}

void Do_exec::load(std::string &vallue, eOperandType type)
{
    std::stringstream ss;
    auto &list_reg_f = registers[vallue];
    auto &list_reg = list_reg_f[type];
    if (list_reg.size() <= 0) {
        ss << "Variable underflow register: " << vallue << ", is empty abort";
        throw std::runtime_error(ss.str());
    }
    stack.push_front(list_reg.front());
    list_reg.pop_front();
}

void Do_exec::store(std::string &vallue, eOperandType type)
{
    std::stringstream ss;
    auto &list_reg_f = registers[vallue];
    auto &list_reg = list_reg_f[type];
    if (list_reg.size() >= 17) {
        ss << "Variable overflow register: " << vallue << ", is of size: " << list_reg.size() << " abort";
        throw std::runtime_error(ss.str());
    }
    list_reg.push_front(stack.front());
    stack.pop_front();
}

void Do_exec::print(std::string &vallue, eOperandType type)
{
    (void)type;
    (void)vallue;
    if (!stack.size()) {
        throw std::runtime_error("stack is empty");
    }
    auto it = stack.front();
    if (it->getType() != eOperandType::Int8) {
        throw std::runtime_error("Try to print a non int8");
    }
    // if (stoi(it->toString()) < 0)
    //     throw std::runtime_error("Try to print a negative value");
    try {
        std::cout << (char)stoi(it->toString()) << std::endl;
    } catch (const std::exception &e) {
        throw e.what();
    }
}

void Do_exec::exit(std::string &vallue, eOperandType type)
{
    (void)type;
    (void)vallue;
    std::longjmp(*exec_handler, 64);
}

Do_exec::~Do_exec()
{
    for (auto s = stack.begin(); s != stack.end(); s++) {
        delete (*s);
    }
    for (auto &map1 : registers) {
        for (auto &map2 : map1.second) {
            for (auto &map3 : map2.second) {
                delete (map3);
            }
        }
    }
    stack.clear();
    funct.clear();
}