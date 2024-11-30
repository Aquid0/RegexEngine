#include "Regex.h"
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

/*
    things to do:
        - convert the regex expression to postfix notation using the shunting yard algorithm 

        - then convert to nfa



        Post-fix notation:
        aba = a?b?a
        a((b)) = a?((b))
        a(b(a)*a)bb = a?(b?(a)*?a)?b?b

        (a*)*?a

        Precedence from highest to lowest:
        1. a* kleene star
        2. a?b concatenation
        3. a+b union

*/

Regex::Regex(string regex) : regex(regex)
{
    to_pfn();
}

void Regex::to_pfn() {
    add_concatenation_ops();
    cout << "added concatenation symbols: " << regex << "\n";

    queue<char> out;
    stack<char> oper;
    unordered_map<char, int> precedence = {
        {'*', 3}, 
        {'?', 2},
        {'+', 1}
    };


    for (char c : regex) {
        if (isalnum(c)) {
            out.push(c);
        } else if ((c == '*' || c == '?' || c == '+') && (!oper.empty() && oper.top() == '(')) {
            oper.push(c);
        } else if (c == '*' || c == '?' || c == '+') {
            while (!oper.empty() && precedence[oper.top()] >= precedence[c]) {             
                char rm = oper.top();
                oper.pop();
                out.push(rm);
            }  
            oper.push(c);
        } else if (c == '(') {
            oper.push(c);
        } else if (c == ')') {
            while (oper.top() != '(') {
                char op = oper.top(); 
                oper.pop(); 
                out.push(op);
            }
            oper.pop(); // Removing '(' from the operations stack
        }
    }

    // Popping remaining operations
    while (!oper.empty()) {
        char op = oper.top(); 
        oper.pop(); 
        out.push(op);
    }


    while (!out.empty()) {
        pfn.push_back(out.front());
        out.pop();
    }


    // Printing pfn
    for (char c : pfn) {
        cout << c; 
    }

}

void Regex::add_concatenation_ops() {
    string res = "";

    for (int i = 0; i < regex.length()-1; i++) {
        char curr = regex[i];
        char next = regex[i+1];

        res += curr;

        if ((isalnum(curr) || curr == ')' || curr == '*') && 
           (isalnum(next) || next == '(')) {
            res += '?'; 
        }       
    }

    // Assuming regex is not empty
    res += regex.back();
    regex = res;
}

