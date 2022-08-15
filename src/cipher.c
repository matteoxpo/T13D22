#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void menu();
int saveScan(int *input);
char **MenuInput();
char *charInput(int flag);
char *charInputFromFile(FILE *f);
int charInputInFile(FILE *f, char *write);
void str_output(char *str);
int main(char argc, char *argv[]) {
  menu();
  return 0;
}

void menu() {
  int input = 0;
  char *path;
  FILE *f = NULL;
  while (input != -1) {
    if (saveScan(&input)) {
      switch (input) {
        case 1:
          path = charInput(0);
          if (path == NULL) {
            printf("n/a\n");
            break;
          }
          f = fopen(path, "r");
          if (f == NULL || fgetc(f) == EOF) {
            printf("n/a\n");
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
          if (f == NULL) {
            printf("n/a\n");
            break;
          }
          fseek(f, SEEK_SET, SEEK_END);
          char *write = charInput(1);
          if (write != NULL) {
            charInputInFile(f, write);
            free(write);
          }
          fclose(f);

        case 3:

          break;

        case -1:
          break;
        default:
          printf("n/a\n");
          break;
      }
    } else {
      printf("n/a\n");
    }
  }
  // if (f != NULL) fclose(f);
  // if (path != NULL) free(path);
}

int saveScan(int *input) {
  int res;
  char sym;
  if (scanf("%d%c", input, &sym) == 2 && sym == '\n') {
    res = 1;
  } else {
    res = 0;
    fseek(stdin, 0, SEEK_END);
  }
  return res;
}

char *charInput(int flag) {
  char *res = malloc(sizeof(char));
  int i = 0;
  while (1) {
    scanf("%c", &(res[i]));
    char *tmp = realloc(res, sizeof(char));
    if (tmp != NULL) res = tmp;
    if (res != NULL) {
      if (res[i] == '\n') {
        if (!flag) res[i] = '\0';
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
    res = realloc(res, sizeof(char));
    res[counter] = buff;
    counter++;
  }
  return res;
}

int charInputInFile(FILE *f, char *write) {
  int res = 1;
  if (f == NULL && write == NULL) {
    res = 0;
  } else {
    for (int i = 0; i < strlen(write); i++) {
      fputc(write[i], f);
    }
  }
  return res;
}

void str_output(char *str) {
  for (int i = 0; i < strlen(str); i++) printf("%c", str[i]);
}