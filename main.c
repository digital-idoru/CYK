#include <stdio.h>
#include <stdlib.h>

#include "grammars.h"
#include "symbolics.h"
#include "prototypes.h"




int main(int argc, const char** argv) {

  int string_size = 0;
  char* input_string = NULL;
  char** Table = NULL; 
  FILE* grammar_file = NULL;

  //Check for correct command line arguments. 
  if(argc != ARGS) {
    fprintf(stderr, "Useage: CYK [grammar file]\n");
    exit(1);
  }

  grammar_file = readInputFile(argv[1]);
  

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

FILE* readInputFile(char* path) {
  
  FILE* f = NULL;
  f = fopen(path, "r");
  
  if(f == NULL) {
    fprintf(stderr, "Could not open grammar file for reading!\n");
    exit(1);
  }
  
  return f;
}


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
      exit(1);
    }
  }

  return t;
}

