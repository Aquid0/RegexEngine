#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <set>

using namespace std;

class FiniteAutomata {
    public: 
        vector<int> states; 
        vector<char> alphabet; 
        vector<unordered_map<char, vector<int>>> transition_func; 
        int init_state; 
        vector<int> accept_states;

 
        FiniteAutomata(vector<int> s, vector<char> a, vector<unordered_map<char, vector<int>>> t_f, int i, vector<int> a_s) {
            /*
                States = {0, 1, 2}
                Alphabet = {a, b}
                transition func = { {a : {1}, b : {2}} , {a : {2}, b : {1}} , {a : {1}, b : {1}} }
                init_state = 0
                accept_states = {2}
            */

            states = s; 
            alphabet = a; 
            transition_func = t_f; 
            init_state = i; 
            accept_states = a_s; 
        }


        bool process(string str) {
            
            // Check if DFA
            // If DFA, process
            // If not, peform conversion

            int curr = init_state;
        
            for (auto c : str) {
                unordered_map<char, vector<int>> available = transition_func[curr];
                if (available.find(c) == available.end()) {
                    return false;
                }
                curr = available[c][0]; // Should be a singleton at this point
            }
        
            if (find(accept_states.begin(), accept_states.end(), curr) != accept_states.end()) return true; 
            return false;
        }


    private: 
        vector<tuple<int>> get_transition_tuples() {
            /*
                Convert transition function to a vector of (p, e, r)            
            */

            vector<tuple<int>> nfa_transitions = {};

            for (int i = 0; i < transition_func.size(); i++) {
                unordered_map<char, vector<int>> s = transition_func[i]; 
                for (auto c : s) {
                    for (auto j : c.second) {
                        nfa_transitions.push_back((i, c.first, j)); // (this state, letter, dest state)
                    }
                }
            } 

            return nfa_transitions;           
        }    


        void convert_to_dfa() {
            vector<tuple<int>> nfa_transitions = get_transition_tuples();
            vector<tuple<int>> dfa_transitions = {};


            /*
            For any state, q, in the NFA : Define E(q) = {q}
            While there exists (p, e, r) in the transition function, with:
                p = a state in E(q)
                e = empty word arrow
                r = a state not in E(q)
            Do: E(q) + r
            */
       } 
};


/*
    States = {0, 1, 2}
    Alphabet = {a, b}
    transition func = { {a : {1,2}, b : {2}} , {a : {2}, b : {1}} , {a : {1}, b : {1}} }
    init_state = 0
    accept_states = {2}
*/
