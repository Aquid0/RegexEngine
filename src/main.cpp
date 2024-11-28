#include <iostream>
#include "FiniteAutomata.h"
#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <set>
#include <tuple>
#include <string>

using namespace std;

int main()
{
    // Testing NFA to DFA:
    vector<vector<int>> s_tests = {
        {0, 1},
        {0, 1, 2},
        {0, 1, 2, 3}};

    vector<vector<char>> a_tests = {
        {'a', 'b'},
        {'a', 'b'},
        {'a', 'b', 'c'}};

    vector<vector<unordered_map<char, set<int>>>> t_f_tests = {
        {{{'a', {1}}},
         {{'b', {1}}, {'\0', {0}}}},
        {{{'a', {1}}},
         {{'b', {2}}},
         {{'\0', {0}}, {'a', {0}}}},
        {{{'\0', {1, 2, 3}}},
         {{'b', {1}}, {'c', {1}}},
         {{'a', {2}}, {'c', {2}}},
         {{'a', {3}}, {'b', {3}}}}};

    vector<int> i_s_tests = {
        0,
        0,
        0,
    };

    vector<vector<int>> a_s_tests = {
        {1},
        {0},
        {1, 2, 3}};

    vector<vector<string>> w_tests = {
        {"ab", "aa", "", "ba", "hi"},
        {"abab", "aba", "b", "a"},
        {"aa", "bb", "cc", "a", "aabb", "abc"}};

    for (int t = 0; t < s_tests.size(); t++)
    {
        FiniteAutomata x(s_tests[t], a_tests[t], t_f_tests[t], i_s_tests[t], a_s_tests[t]);
        for (auto word : w_tests[t])
        {
            cout << x.process(word) << "\n";
        }
    };

    // FiniteAutomata x(s_tests[2], a_tests[2], t_f_tests[2], i_s_tests[2], a_s_tests[2]);
    // for (auto word : w_tests[2]) {
    //     cout << x.process(word) << "\n";
    // }

    return 0;
}