#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "grammars.h"
#include "symbolics.h"
#include "prototypes.h"



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

  #if debug
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

  struct Grammar* G = (struct Grammar*)malloc(sizeof(struct Grammar));
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

  fscanf(cfg, "%s\n", G->alphabet);
  fscanf(cfg, "%c\n", &G->start_symbol);

  #if debug
  printf("The alphabet is: %s\n", G->alphabet);
  printf("The srart symbol is: %c\n", G->start_symbol);
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

