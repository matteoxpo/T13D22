#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void menu();
int saveScan(int *input);
char **MenuInput();
char *charInput();
char *charInputFromFile(FILE *f);
char *charInputInFile(FILE *f, char *write);
void str_output(char *str);
int main() {
  menu();
  return 0;
}

void menu() {
  int input = 0;
  char *path;
  FILE *f = NULL;
  while (input != -1 && saveScan(&input)) {
    switch (input) {
      case 1:
        path = charInput();
        f = fopen(path, "r");
        if (f == NULL || fgetc(f) == EOF) {
          printf("n/a");
          input = -1;
          break;
        }
        rewind(f);
        char *data_from_file = charInputFromFile(f);
        str_output(data_from_file);

        if (data_from_file != NULL) free(data_from_file);
        fclose(f);
        break;

      case 2:
        f = fopen(path, "r+");
        fseek(f, SEEK_SET, SEEK_END);
        char *write = charInput();
        if (write != NULL) {
        }
        break;
      case -1:
        break;
      default:
        printf("n/a");
        input = -1;
        break;
    }
  }
  // if (f != NULL) fclose(f);
  // if (path != NULL) free(path);
}

int saveScan(int *input) {
  int res;
  char sym;
  if (scanf("%d%c", input, &sym) == 2 && sym != '.')
    res = 1;
  else
    res = 0;
  return res;
}

char *charInput() {
  char *res = malloc(sizeof(char));
  int i = 0;
  while (1) {
    scanf("%c", &(res[i]));
    char *tmp = realloc(res, sizeof(char));
    if (tmp != NULL) res = tmp;
    if (res != NULL) {
      if (res[i] == '\n' || res[i] == ' ') {
        res[i] = '\0';
        break;
      }
      i++;
    } else {
      free(res);
    }
  }
  return res;
}

char *charInputFromFile(FILE *f) {
  char *res = malloc(sizeof(char));
  char buff;
  int counter = 0;
  while (fread(&buff, sizeof(char), 1, f)) {
    // char *temp = realloc()
    res = realloc(res, sizeof(char));
    res[counter] = buff;
    counter++;
  }
  return res;
}

char *charInputInFile(FILE *f, char *write) {}

void str_output(char *str) {
  for (int i = 0; i < strlen(str); i++) printf("%c", str[i]);
  printf("\n");
}