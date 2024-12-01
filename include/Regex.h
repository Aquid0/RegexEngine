#ifndef REGEX_H
#define REGEX_H

#include "../include/FiniteAutomata.h"

#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <set>
#include <tuple>
#include <queue>

class Regex
{
public:
    std::string regex;
    std::queue<char> pfn;
    FiniteAutomata nfa;
    Regex(std:: string regex);
    bool process(std:: string s);

private:
    void add_concatenation_ops();
    void to_pfn();
    void to_nfa();
};

#endif