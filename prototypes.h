/** Space for function prototypes **/

#ifndef PROTOTYPES_H
#define PROTOTYPES_H

#include "grammars.h"

FILE* readInputFile(char*);
char** createCYKTable(int);
struct Grammar* parseCFG(FILE*);

#endif
