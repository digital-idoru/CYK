# CYK Description
CYK Algorithm for solving the membership problem of CFGs. Currently only supports CFGs presented in Chomsky Normal Form. Future updates will include support for converting any given CFG into an equivalent CFG in Chomsky Normal Form. 
The algorithm checks if given an input string w \in \Sigma^* that it can be generated from the given grammar. This algorithm is supposed to run in O(n^3) time. 

# Input Protocol 
The input for the algorithm will be a file containing the alphabet on a line by itself, and then the following lines will contain the start symbol of the grammar followed by productions of the grammar each on a line by themselves
as follows: 

If A -> uBv | xCy are productions with LHS A, then 

A, uBv, xCy is on a line by itself in the file. 

For example, the following grammar: 

S -> aSa | aSS | B
B -> bB | e 

is represented by the following: 

a,b
S
S, aSa, aSS, B
B, bB, e 

where e represents \epsilon, or \lambda the empty string. 