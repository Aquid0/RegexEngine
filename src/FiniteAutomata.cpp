#include <iostream>
#include <vector>
#include <unordered_map>

class FiniteAutomata {
    public: 
        std::vector<int> states; 
        std::vector<char> alphabet; 
        std::vector<std::unordered_map<char, int>> transition_func; 
        int init_state; 
        std::vector<int> accept_states;
 
        FiniteAutomata(std::vector<int> s, std::vector<char> a, std::vector<std::unordered_map<char, int>> t_f, int i, std::vector<int> a_s) {
            states = s; 
            alphabet = a; 
            transition_func = t_f; 
            init_state = i; 
            accept_states = a_s; 
        }
};