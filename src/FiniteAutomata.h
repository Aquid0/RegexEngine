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
        vector<unordered_map<char, set<int>>> transition_func;
        int init_state;
        vector<int> accept_states;
 
        FiniteAutomata(vector<int> s, vector<char> a, vector<unordered_map<char, set<int>>> t_f, int i_s, vector<int> a_s);
        bool process(string);

    private:
        void convert_to_dfa(); 
        void print_table(vector<vector<set<int>>>& table);
        void print_tf(vector<unordered_map<char, set<int>>>& data);
        bool check_states(vector<vector<set<int>>> table, set<int> state);
        int find_index(vector<set<int>> c, set<int> t);
        bool is_dfa();
        bool intersects(set<int> s, vector<int> v);

};

#endif