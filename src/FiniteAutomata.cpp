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
    if (!is_dfa())
    {
        convert_to_dfa();
    }

    int curr = init_state;

    for (auto c : str)
    {
        unordered_map<char, set<int>> available = transition_func[curr];
        if (available.find(c) == available.end())
        {
            return false;
        }
        curr = *available[c].begin();
    }

    if (find(accept_states.begin(), accept_states.end(), curr) != accept_states.end())
        return true;
    return false;
}

bool FiniteAutomata::is_dfa()
{
    for (int s = 0; s < transition_func.size(); s++)
    {
        if (transition_func[s].size() != alphabet.size())
        {
            return false;
        }
    }
    return true;
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
            char character = alphabet[c - 1];
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

            if (!check_states(transition_table, transition_table[r][c]))
            {
                vector<set<int>> new_row(y + 1);
                new_row[0] = transition_table[r][c];
                transition_table.push_back(new_row);
            }
        }
    }

    // print_table(transition_table);
    // cout << "\n";

    // Converting to transition_function
    int num_states = transition_table.size();
    vector<set<int>> conversion_table(num_states);
    transition_func.clear();
    transition_func.resize(num_states);

    // Initial state is initial epsilon enclosure
    // Converting all sets to integers to fit into transition_func

    for (int r = 0; r < num_states; r++)
    {
        conversion_table[r] = transition_table[r][0];
    }

    vector<int> temp_a_s = accept_states;
    accept_states.clear();

    for (int r = 0; r < num_states; r++)
    {
        if (intersects(transition_table[r][0], temp_a_s))
        {
            accept_states.push_back(find_index(conversion_table, transition_table[r][0]));
        }
    }

    for (int r = 0; r < num_states; r++)
    {
        for (int c = 1; c < transition_table[0].size(); c++)
        {
            transition_func[r][alphabet[c - 1]] = {find_index(conversion_table, transition_table[r][c])};
        }
    }

    // print_tf(transition_func);
}

bool FiniteAutomata::intersects(set<int> s, vector<int> v)
{
    for (int elem : s)
    {
        if (find(v.begin(), v.end(), elem) != v.end())
        {
            return true;
        }
    }
    return false;
}

int FiniteAutomata::find_index(vector<set<int>> c, set<int> t)
{
    for (int i = 0; i < c.size(); i++)
    {
        if (c[i] == t)
        {
            return i;
        }
    }
    return -1;
}

void FiniteAutomata::print_table(vector<vector<set<int>>> &table)
{
    // Print column headers
    cout << setw(10) << "State/Col";
    for (size_t col = 0; col < table[0].size(); ++col)
    {
        cout << setw(10) << "Col " + to_string(col);
    }
    cout << endl;

    cout << string(10 + table[0].size() * 10, '-') << endl;

    // Print rows with data
    for (size_t i = 0; i < table.size(); ++i)
    {
        cout << setw(10) << "Row " + to_string(i);
        for (size_t j = 0; j < table[i].size(); ++j)
        {
            cout << setw(10) << "{";

            // Add elements of the set
            for (auto it = table[i][j].begin(); it != table[i][j].end(); ++it)
            {
                cout << *it;
                if (next(it) != table[i][j].end())
                {
                    cout << ",";
                }
            }
            cout << "}";
        }
        cout << endl;
    }
}

void FiniteAutomata::print_tf(vector<unordered_map<char, set<int>>> &data)
{
    for (int i = 0; i < data.size(); i++)
    {
        cout << "State " << i << ": ";
        for (const auto &p : data[i])
        {
            cout << p.first << " : {" << *p.second.begin() << "}, ";
        }
        cout << "\n";
    }
}

bool FiniteAutomata::check_states(vector<vector<set<int>>> table, set<int> state)
{

    for (int r = 0; r < table.size(); r++)
    {
        if (table[r][0] == state)
        {
            return true;
        }
    }
    return false;
}