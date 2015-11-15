/**
   A CFG is a 4-tuple (T, N, P, S) where
   T -- A set of terminal symbols (output alphabet) 
   N -- A set of non-terminal symbols or variables. 
   P - A set of productions or Rules. 
   S -- The start symbol of the grammar. 

   The grammar G is represented as linked list of linked lists. Each node in the initial linked list
   will represent the LHS of a production, and the linked list associated with that node will contain
   all of the productions on the RHS of that non-terminal. 

   There are probably better data structures for representing grammars, but right now I just want to 
   get something working. After everything is operational I can change the data structure with hopefully
   minimal interference with the actual CYK algorithm. 


**/

#ifndef GRAMMARS_H
#define GRAMMARS_H

struct ProductionNode {
  
  /**
     This structure represents the RHS of productions in G. It will be associated
     with a LHS node that contains the nonterminal and the head pointer to the linked
     list. 
  **/


  //Right hand side of a production in G. 
  char* rhs;

  //Pointer to the next node in the linked list. 
  struct ProductionNode* next;

};


struct Productions {

  /** 
      Struct to represent the productions of a grammer. 
      The LHS is a single non-terminal and is represented as a single char variable. 
      The RHS which will consist of uAv where u, v \in \Sigma^* and A \in T will be 
      represented as a linked list. 
  **/


  char lhs; //Left hand side of the rule
  struct ProductionNode* head; //Head of a linked list representing the RHSs of the production. 

};


struct Grammar {

  /** 
      Struct to represent the grammar as a whole. The output alphabet is represented as an array of char,
      the start symbol is given a special variable for easy access, and the set of productions is 
      repesented as an array of productions, each production is represented as a struct that contains a 
      LHS non-terminal symbol and a linked list representhing the RHSs of the rule. 
  **/
  
  char* alphabet;
  char start_symbol; 
  struct Productions** P; 


};

#endif
