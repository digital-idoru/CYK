/**
   A CFG is a 4-tuple (T, N, P, S) where
   T -- A set of terminal symbols (output alphabet) 
   N -- A set of non-terminal symbols or variables. 
   P - A set of productions or Rules. 
   S -- The start symbol of the grammar. 
**/

#ifndef GRAMMARS_H
#define GRAMMARS_H

struct ProductionNode {
  
  char* lhs;
  struct ProductionNode* next;

};


struct Productions {

  /** 
      Struct to represent the productions of a grammer. 
      The RHS is a single non-terminal and is represented as a single char variable. 
      The LHS which will consist of uAv where u, v \in \Sigma^* and A \in T will be 
      represented as an array of strings. 
  **/


  char NT; //Left hand side of the rule
  struct ProductionNode* head; //Head of a linked list representing the LHSs of the production. 

};


struct Grammar {

  /** 
      Struct to represent the grammar as a whole. The output alphabet is represented as an array of char,
      the start symbol is given a special variable for easy access, and the set of productions is 
      repesented as an array of productions, each production is represented as a struct that contains a 
      RHS non-terminal symbol and a linked list representhing the LHSs of the rule. 
  **/
  
  char* alphabet;
  char start_symbol; 
  struct productions** P; 


};

#endif
