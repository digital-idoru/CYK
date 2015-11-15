#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "grammars.h"
#include "symbolics.h"
#include "prototypes.h"

//Current todo 2015/11/15 -- Create functions for displaying the completely parsed grammar.//


int main(int argc, const char** argv) {

  int string_size = 0;
  char* input_string = NULL;
  char** Table = NULL; 
  FILE* grammar_file = NULL;
  struct Grammar* G = NULL;

  //Check for correct command line arguments. 
  if(argc != ARGS) {
    fprintf(stderr, "Useage: CYK [grammar file]\n");
    exit(FAIL);
  }

  grammar_file = readInputFile(argv[1]);
  printf("Now parsing input file: %s\n", argv[1]);
  G = parseCFG(grammar_file); 
  printf("Parsing complete!\n");

  #if MAINDEBUG
  printf("Please enter a string size: ");
  scanf("%d", &string_size);

  printf("Creating CYK Table.\n");
  Table = createCYKTable(string_size);
  Table[1][1] = 'h';
  printf("%c\n", Table[1][1]);
  #endif


  fclose(grammar_file);
  return 0;

}

//Simple function for opening a file. Probably shouldn't even be a function. 
//Input -- path - A string representing the path to the file to open for reading. 
//Return -- f - a pointer to the open file. 
FILE* readInputFile(char* path) {
  
  FILE* f = NULL;
  f = fopen(path, "r");
  
  if(f == NULL) {
    fprintf(stderr, "Could not open grammar file for reading!\n");
    exit(FAIL);
  }
  
  return f;
}

struct Grammar* parseCFG(FILE* cfg) {
  
  //These values are fixed for now for debugging purposes. 
  int max_alphabet_size = 30;
  int max_num_productions = 30; 
  int max_production_size = 100;
  int i = 0; 

  //Variables pertaining to the Grammar
  struct Grammar* G = NULL;
  char* line = NULL;
  struct Productions* tmp = NULL;
  struct ProductionNode* nodeTmp = NULL;
  char* token = NULL;

  line = (char*)malloc(sizeof(char)*max_production_size);
  if(line == NULL) {
    fprintf(stderr, "Could not allocate space for production string parsing.\n");
    exit(FAIL);
  }
  memset((void*)line, 0, max_production_size);

  G = (struct Grammar*)malloc(sizeof(struct Grammar));
  if (G == NULL) {
    fprintf(stderr, "Could not allocate grammar struct!\n");
    exit(FAIL);
  }

  G->alphabet = (char*)malloc(sizeof(char)*max_alphabet_size);
  if(G->alphabet == NULL) {
    fprintf(stderr, "Could not allocate alphabet space.\n");
    exit(FAIL);
  }

  memset((void*)G->alphabet, 0, (size_t)max_alphabet_size); 
  
  G->P = (struct Productions**)malloc(sizeof(struct Productions*)*max_num_productions);
  if(G->P == NULL) {
    fprintf(stderr, "Could not allocate space for Productions array\n");
    exit(FAIL);
  }

  //Read the alphabet from the input file. 
  fscanf(cfg, "%s\n", G->alphabet);

  //Read the start symbol from the input file. 
  fscanf(cfg, "%c\n", &G->start_symbol);

  //Read the productions and populate the data structures. 
  do {

    //Scan the line to read the productions. 
    fscanf(cfg, "%s\n", line);
    
    //Allocate the struct and initialize fields to starting values.  
    tmp = (struct Productions*)malloc(sizeof(struct Productions));
    if(tmp == NULL) {
      fprintf(stderr, "Could not allocate Productions struct.\n");
      exit(FAIL);
    }
    tmp->lhs = '0';
    tmp->head = NULL; 

    //Tokenize the input string to produce the productions.//
    
    //First capture the LHS of the production. 
    token = strtok(line, ",");
    tmp->lhs = token[0];
    
    //Get the RHS of the current production. 
    while((token = strtok(NULL, ",")) != NULL) {

      //Allocate a node for the linked list. 
      nodeTmp = (struct ProductionNode*)malloc(sizeof(struct ProductionNode));
      if(nodeTmp == NULL) {
	fprintf(stderr, "Could not allocate production node for RHS of rule.\n");
	exit(FAIL);
      }
      
      //Allocate for string representing the RHS of the current production. 
      nodeTmp->rhs = (char*)malloc(sizeof(char)*max_production_size);
      if(nodeTmp->rhs == NULL) {
	fprintf(stderr, "Could not allocate memory for string RHS of rile.\n");
	exit(FAIL);
      }
      memset((void*)nodeTmp->rhs, 0, (size_t)max_production_size);
      
      //Copy the string to the rhs. 
      strcpy(nodeTmp->rhs, token);

      //Add the rhs to the linked list. 
      if(tmp->head == NULL) {
	tmp->head = nodeTmp;
      }	else {
	nodeTmp->next = tmp->head;
	tmp->head = nodeTmp;
      }

    }
    
    //Add the new production to the array. 
    G->P[i] = tmp;
    i++;
  } while(!feof(cfg));


  #if GRAMMARDEBUG
  printf("The alphabet is: %s\n", G->alphabet);
  printf("The start symbol is: %c\n", G->start_symbol);
  printf("The RHS of the first rule is: %c\n", (G->P[0])->lhs);
  #endif

  return G;
}


//A function to allocate space for the CYK table (an nxn matrix where 
//n is the length of the input string). 
//Input -- size - An integer representing the dimensions of the matrix. 
//Returns -- t - A double pointer to the matrix. 
char** createCYKTable(int size) {
  char** t = NULL; //Pointer to the matrix. 
  int i, j = 0; 
  
  t = (char**)malloc(sizeof(char*)*size);
  if (t == NULL) {
    fprintf(stderr, "Could not allocate initial rows for CYK table.\n");
    exit(1);
  }

  for(i = 0; i < size; i++) {
    t[i] = (char*)malloc(sizeof(char)*size);
    if(t[i] == NULL) {
      fprintf(stderr, "Could not allocate space for row: %d", i);
      exit(FAIL);
    }
  }

  return t;
}

