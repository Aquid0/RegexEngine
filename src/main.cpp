#include <iostream>
#include "FiniteAutomata.h"

int main() {
    std::cout << "Hello World" << std::endl; 
    vector<int> s = {0, 1, 2};
    vector<char> a = {'a', 'b'};
    vector<unordered_map<char, vector<int>>> t_f = { {{'a', {1}}, {'b', {2}}} , {{'a', {2}}, {'b', {1}}} , {{'a', {1}}, {'b',  {1}}} };
    int i_s = 0;
    vector<int> a_s = {2};


    FiniteAutomata x(s, a, t_f, i_s, a_s);

}