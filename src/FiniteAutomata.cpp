#include "FiniteAutomata.h"
#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <set>
#include <iomanip>

using namespace std;

FiniteAutomata::FiniteAutomata(vector<int> s, vector<char> a, vector<unordered_map<char, set<int>>> t_f, int i, vector<int> a_s) : states(s), alphabet(a), transition_func(t_f), init_state(i), accept_states(a_s)
{
}

bool FiniteAutomata::process(string str)
{
    convert_to_dfa();

    // int curr = init_state;

    // for (auto c : str) {
    //     unordered_map<char, set<int>> available = transition_func[curr];
    //     if (available.find(c) == available.end()) {
    //         return false;
    //     }
    //     curr = available[c][0]; // Should be a singleton at this point
    // }

    // if (find(accept_states.begin(), accept_states.end(), curr) != accept_states.end()) return true;
    return false;
}

void FiniteAutomata::convert_to_dfa()
{
    unordered_map<int, set<int>> epsilon_closures;
    for (int s = 0; s < transition_func.size(); s++)
    {
        epsilon_closures[s] = {s};
        unordered_map<char, set<int>> ts = transition_func[s];
        if (ts.find('\0') != ts.end())
        {
            for (int dest_state : transition_func[s]['\0'])
            {
                epsilon_closures[s].insert(dest_state);
            }
        }
    }

    // // Add all the epsilon closures to the first column of the transition_table
    int x = epsilon_closures.size();
    int y = alphabet.size();
    vector<vector<set<int>>> transition_table(x, vector<set<int>>(y + 1));

    //
    //     Transition Table:
    //      0      1    2
    //    states   a    b
    //    {1, 3}  {}   {}
    //     {2}    {}   {}
    //     {3}    {}   {}
    // */

    for (int i = 0; i < x; i++)
    {
        transition_table[i][0] = epsilon_closures[i];
    }


    for (int r = 0; r < transition_table.size(); r++)
    {
        set<int> lookup_states = transition_table[r][0];
        for (int c = 1; c < y + 1; c++)
        {
            char character = alphabet[c-1];
            for (auto s : lookup_states)
            {
                // If the character exists for this current state
                if (transition_func[s].find(character) != transition_func[s].end())
                {
                    set<int> state_char_transitions = transition_func[s][character];
                    for (auto dest_state : state_char_transitions)
                    {
                        transition_table[r][c].insert(dest_state);
                        // Add any e's
                        transition_table[r][c].insert(epsilon_closures[dest_state].begin(), epsilon_closures[dest_state].end());
                    }
                }
            }

            if (!check_states(transition_table, transition_table[r][c])) {
                vector<set<int>> new_row(y+1);
                new_row[0] = transition_table[r][c];
                transition_table.push_back(new_row);
            }

        }
    }


    print_table(transition_table);
}


void FiniteAutomata::print_table(vector<vector<set<int>>>& table) {
    // Print column headers
    std::cout << std::setw(10) << "State/Col";
    for (size_t col = 0; col < table[0].size(); ++col) {
        std::cout << std::setw(10) << "Col " + std::to_string(col);
    }
    std::cout << std::endl;

    std::cout << std::string(10 + table[0].size() * 10, '-') << std::endl;

    // Print rows with data
    for (size_t i = 0; i < table.size(); ++i) {
        std::cout << std::setw(10) << "Row " + std::to_string(i);
        for (size_t j = 0; j < table[i].size(); ++j) {
            std::cout << std::setw(10) << "{";

            // Add elements of the set
            for (auto it = table[i][j].begin(); it != table[i][j].end(); ++it) {
                std::cout << *it;
                if (std::next(it) != table[i][j].end()) {
                    std::cout << ",";
                }
            }
            std::cout << "}";
        }
        std::cout << std::endl;
    }
}

bool FiniteAutomata::check_states(vector<vector<set<int>>> table, set<int> state) {

    for (int r = 0; r < table.size(); r++) {
        if (table[r][0] == state) {
            return true;
        }
    }
    return false;
}