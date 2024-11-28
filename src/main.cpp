#include <iostream>
#include "FiniteAutomata.h"
#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <set>
#include <tuple>

using namespace std;

int main() {
    vector<int> s = {0, 1, 2};
    vector<char> a = {'a', 'b'};
    vector<unordered_map<char, set<int>>> t_f = { {{'b', {1}}, {'\0', {2}}}, 
                                                  {{'a', {1, 2}}, {'b', {2}}}, 
                                                  {{'a', {0}}} };
    int i_s = 0;
    vector<int> a_s = {1};

    FiniteAutomata x(s, a, t_f, i_s, a_s);
    x.process("hello");
    return 0;
}