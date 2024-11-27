#ifndef FINITEAUTOMATA_H
#define FINITEAUTOMATA_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <set>
#include <tuple>

using namespace std;

class FiniteAutomata {
    public:
        vector<int> states; 
        vector<char> alphabet;
        vector<unordered_map<char, vector<int>>> transiton_func;
        int init_state;
        vector<int> accept_states;
 
        FiniteAutomata(vector<int> s, vector<char> a, vector<unordered_map<char, vector<int>>> t_f, int i_s, vector<int> a_s);
        bool process(string);

    private:
        unordered_map<pair<int, char>, int> get_transition_tuples();
        void convert_to_dfa(); 


};

#endif