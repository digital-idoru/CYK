# CYK
CYK Algorithm for solving the membership problem of CFGs. Currently only supports CFGs presented in Chomsky Normal Form. Future updates will include support for converting any given CFG into an equivalent CFG in Chomsky Normal Form. 
The algorithm checks if given an input string w \in \Sigma^* that it can be generated from the given grammar. This algorithm uses dynamic programming to build up solutions to each possible substring of the input string. By doing this
the algorithm is able to check if the grammar generates the entire string. This algorithm is supposed to run in O(n^3) time. 
