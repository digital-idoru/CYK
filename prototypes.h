/** Space for function prototypes **/
#ifndef prototypes_include
#define prototypes_includes

#include "grammars.h"

#endif

FILE* readInputFile(char*);
char** createCYKTable(int);
struct Grammar* parseCFG(FILE*);
