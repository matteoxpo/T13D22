#ifndef SRC_MODULE_IO_H_
#define SRC_MODULE_IO_H_

#include <stdio.h>
char *charInput(int flag);
char *charInputFromFile(FILE *f);
int charInputInFile(FILE *f, char *write);
void str_output(char *str);

#endif  // SRC_MODULE_IO_H_
