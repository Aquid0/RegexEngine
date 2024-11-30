#ifndef REGEX_H
#define REGEX_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <set>
#include <tuple>

using namespace std;

class Regex
{
public:
    string regex;
    vector<char> pfn;
    Regex(string regex);

private:
    void add_concatenation_ops();
    void to_pfn();
};

#endif