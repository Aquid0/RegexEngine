# RegexEngine
- Takes a Regex Expression and a string to process
- Applies the Shunting-Yard Algorithm to convert it to Post-Fix Notation
- Uses Thompson's Construction Algorithm to convert this expression into an equivalent nondeterministic finite automaton (NFA)
- NFA is then converted to its equivalent DFA for more efficient processing, and returns True/False if the string is accepting/rejecting 
