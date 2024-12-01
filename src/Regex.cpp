#include "../include/Regex.h"
#include "../include/FiniteAutomata.h"

#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <set>
#include <iomanip>
#include <queue>
#include <stack>


using namespace std;

Regex::Regex(string regex) : regex(regex)
{
    to_pfn();
    to_nfa();
}

enum
{
    Split = 257,
    Match = 256
};

struct State
{
    int c;                 // Represents a character as an integer, or a special token (split)
                           // c < 256 = Labelled arrow with character c to out
                           // c == 256 = Accepting state
                           // c == 257 = unlabelled arrows to out AND out1
    State *out = NULL;     // Pointer to another state, direct transition
    State *out1 = NULL;    // Pointer to a split transition

    State(int c, State *out = NULL, State *out1 = NULL) : c(c), out(out), out1(out1) {}
};
// Use: s1.out = &s2;

struct Frag
{
    State *start;        // Pointer to a state
    vector<State *> out; // Vector of uninitialised state pointers

    Frag(State *start, vector<State *> out) : start(start), out(out) {}
};

void patch(vector<State *> &l1, State *s)
{
    for (State *state : l1)
    {
                     // Update each unresolved pointer to point to the specified state
                     // Copies the value of the object s points to, into the value of the object state points to
        state = s;
    }
}

vector<State *> append(vector<State *> &v1, vector<State *> &v2)
{
    v1.insert(v1.end(), v2.begin(), v2.end());
    return v1;
}

void Regex::to_nfa()
{
    stack<Frag> stack;
    State *s;

    while (!pfn.empty())
    {
        char p = pfn.front();
        pfn.pop();

        switch (p)
        {
        default:
        {
            s = new State(p, NULL, NULL);
            stack.push(Frag(s, {s->out}));
            break;
        }
        case '?':
        { // Concatenation
            Frag e2 = stack.top();
            stack.pop();
            Frag e1 = stack.top();
            stack.pop();
            patch(e1.out, e2.start);
            stack.push(Frag(e1.start, e2.out));
            break;
        }
        case '+':
        { // Alternation
            Frag e2 = stack.top();
            stack.pop();
            Frag e1 = stack.top();
            stack.pop();
            s = new State(Split, e1.start, e2.start);
            stack.push(Frag(s, append(e1.out, e2.out)));
            break;
        }
        case '*':
        { // Kleene Star
            Frag e = stack.top();
            stack.pop(); 
            s = new State(Split, e.start, NULL);
            patch(e.out, s);
            stack.push(Frag(s, {s->out1}));
            break;
        }
        }
    }

    Frag e = stack.top();
    stack.pop();

    patch(e.out, new State(Match));

    State *fa_start_state = e.start;
    
    // Convert to nfa structure



}

bool Regex::process(string str)
{
    // return nfa.process(str);
    return false; 
}

void Regex::to_pfn()
{
    add_concatenation_ops();
    cout << "added concatenation symbols: " << regex << "\n";
    cout << "\n";

    stack<char> oper;
    unordered_map<char, int> precedence = {
        {'*', 3},  // Kleene Star - Zero or more
        {'?', 2},  // Concatenation
        {'+', 1}}; // Alternation - Union

    for (char c : regex)
    {
        if (isalnum(c))
        {
            pfn.push(c);
        }
        else if ((c == '*' || c == '?' || c == '+') && (!oper.empty() && oper.top() == '('))
        {
            oper.push(c);
        }
        else if (c == '*' || c == '?' || c == '+')
        {
            while (!oper.empty() && precedence[oper.top()] >= precedence[c])
            {
                char rm = oper.top();
                oper.pop();
                pfn.push(rm);
            }
            oper.push(c);
        }
        else if (c == '(')
        {
            oper.push(c);
        }
        else if (c == ')')
        {
            while (oper.top() != '(')
            {
                char op = oper.top();
                oper.pop();
                pfn.push(op);
            }
            oper.pop(); // Removing '(' from the operations stack
        }
    }

    // Popping remaining operations
    while (!oper.empty())
    {
        char op = oper.top();
        oper.pop();
        pfn.push(op);
    }

    // Printing queue
    queue<char> temp = pfn;
    while (!temp.empty())
    {
        cout << temp.front();
        temp.pop();
    }
    cout << "\n"; 
}

void Regex::add_concatenation_ops()
{
    string res = "";

    for (int i = 0; i < regex.length() - 1; i++)
    {
        char curr = regex[i];
        char next = regex[i + 1];

        res += curr;

        if ((isalnum(curr) || curr == ')' || curr == '*') &&
            (isalnum(next) || next == '('))
        {
            res += '?';
        }
    }

    res += regex.back(); // Assuming regex is not empty
    regex = res;
}
