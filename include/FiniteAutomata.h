#ifndef FINITEAUTOMATA_H
#define FINITEAUTOMATA_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <set>
#include <tuple>

class FiniteAutomata {
    public:
        std::vector<int> states; 
        std::vector<char> alphabet;
        std::vector<std::unordered_map<char, std::set<int>>> transition_func;
        int init_state;
        std::vector<int> accept_states;
 
        FiniteAutomata();
        FiniteAutomata(std::vector<int> s, std::vector<char> a, std::vector<std::unordered_map<char, std::set<int>>> t_f, int i_s, std::vector<int> a_s);
        bool process(std::string);

    private:
        void convert_to_dfa(); 
        void print_table(std::vector<std::vector<std::set<int>>>& table);
        void print_tf(std::vector<std::unordered_map<char, std::set<int>>>& data);
        bool check_states(std::vector<std::vector<std::set<int>>> table, std::set<int> state);
        int find_index(std::vector<std::set<int>> c, std::set<int> t);
        bool is_dfa();
        bool intersects(std::set<int> s, std::vector<int> v);

};

#endif