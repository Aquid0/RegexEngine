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

            convert_to_dfa();

            // int curr = init_state;
        
            // for (auto c : str) {
            //     unordered_map<char, vector<int>> available = transition_func[curr];
            //     if (available.find(c) == available.end()) {
            //         return false;
            //     }
            //     curr = available[c][0]; // Should be a singleton at this point
            // }
        
            // if (find(accept_states.begin(), accept_states.end(), curr) != accept_states.end()) return true; 
            // return false;
        }


    private: 
        unordered_map<pair<int, char>, int> get_transition_tuples() {
            /*
                Convert transition function to a vector of (p, e, r)            
            */
            unordered_map<pair<int, char>, int> nfa_transitions;

            for (int i = 0; i < transition_func.size(); i++) {
                unordered_map<char, vector<int>> s = transition_func[i]; 
                for (auto c : s) {
                    for (auto j : c.second) {
                        nfa_transitions[{i, c.first}] = j;
                    }
                }
            } 

          return nfa_transitions;
        }    


        void convert_to_dfa() {

            unordered_map<pair<int, char>, int> nfa_transitions = get_transition_tuples();
            unordered_map<pair<vector<int>, char>, set<int>> dfa_transitions = {};
            unordered_map<int, vector<int>> epsilon_closures = {};

            // Calculate epsilon closures
            for (auto s : states) {
                epsilon_closures[s] = {s};
                for (const auto& t : nfa_transitions) {
                    if (t.first.first == s && t.first.second == 'ε') {
                        epsilon_closures[s].push_back(t.second);
                    } 
                }
            } 

            
            for (char character : alphabet) {

                for (auto e : epsilon_closures) {
                    
                    int curr_e_state = e.first; 
                    vector<int> curr_e_comb = e.second;
                    set<int> transitions_on_e = {};
                    
                    for (auto s : curr_e_comb) { 
                        
                        for (auto t : nfa_transitions) {
                            
                            pair<int, char> this_transition_state = t.first;

                            if (this_transition_state.first == s && this_transition_state.second == character) {
                                
                                transitions_on_e.insert(t.second);

                            }

                        }

                    } 

                    for (auto s : transitions_on_e) {

                        for (auto elem : epsilon_closures[s]) {

                            transitions_on_e.insert(elem);

                        }
                    }

                    dfa_transitions[{curr_e_comb, character}] = transitions_on_e;
                }
            }

            // adding states that are not covered by the epsilon closures
            // optimisation: just get rid of the tuples and go back to the dictionaries
            for (auto transition : dfa_transitions) {
                if (find(dfa_transitions.begin(), dfa_transitions.end(), transition.second) == dfa_transitions.end()) {
                    
                    vector<int> adding_state(transition.second.begin(), transition.second.end());
                    
                    for (char character : alphabet) {

                        set<int> transitions_on_adding_state = {};

                        for (auto s : adding_state) {

                            for (auto t : nfa_transitions) { 

                                pair<int, char> this_transition_state = t.first;

                                if (this_transition_state.first == s && this_transition_state.second == character) {
                                    
                                    transitions_on_adding_state.insert(t.second);

                                }

                            }         

                        }                        

                        for (auto s : transitions_on_adding_state) {

                            for (auto elem : epsilon_closures[s]) {

                                transitions_on_adding_state.insert(elem);

                            }

                        }


                        dfa_transitions[{adding_state, character}] = transitions_on_adding_state;
                    }
                }    

                printDFATransitions(dfa_transitions);

            }
        }    


        // Helper function to print a vector<int>
        void printVector(const vector<int>& vec) {
            cout << "[";
            for (size_t i = 0; i < vec.size(); ++i) {
                cout << vec[i];
                if (i < vec.size() - 1) cout << ", ";
            }
            cout << "]";
        }

        // Helper function to print a set<int>
        void printSet(const set<int>& s) {
            cout << "{";
            for (auto it = s.begin(); it != s.end(); ++it) {
                cout << *it;
                if (next(it) != s.end()) cout << ", ";
            }
            cout << "}";
        }

        // Helper function to print a pair<vector<int>, char>
        void printPair(const pair<vector<int>, char>& p) {
            cout << "(";
            printVector(p.first);
            cout << ", '" << p.second << "')";
        }

        // Function to print the unordered_map
        void printDFATransitions(const unordered_map<pair<vector<int>, char>, set<int>>& transitions) {
            cout << "{\n";
            for (const auto& entry : transitions) {
                cout << "  ";
                printPair(entry.first);
                cout << " -> ";
                printSet(entry.second);
                cout << "\n";
            }
            cout << "}\n";
        }

};