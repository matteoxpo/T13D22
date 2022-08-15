#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void menu(int shift);
int saveScan(int *input);
void Quest1(char *path);
void Quest2(char *path);
void Quest3(char *path, int shift);
char *charInput(int flag);
char *charInputFromFile(FILE *f);
int charInputInFile(FILE *f, char *write);
void str_output(char *str);
int is_type_file(char *name, char type);

char *s21_strcat(char *str1, char *str2) {
  int size1 = strlen(str1);
  int size2 = strlen(str2);

  str1 = (char *)realloc(str1, size1 + size2);
  for (int i = size1, k = 0; i < size1 + size2; i++, k++) {
    str1[i] = str2[k];
  }
  return str1;
}

int main(char argc, char *argv[]) {
  // menu();
  // system("ls ai_modules/*.c");
  int shift = 0;
  if (argc == 2) shift = atoi(argv[1]);
  char *path = "1123";
  char *res = createCommand(path, 'c');
  str_output(res);
  // menu(shift);
  return 0;
}

void menu(int shift) {
  int input = 0;
  char *path;

  while (input != -1) {
    while (!saveScan(&input)) {
      printf("n/a\n");
    }
    switch (input) {
      case 1:
        path = charInput(0);
        Quest1(path);
        break;
      case 2:
        Quest2(path);
        break;
      case 3:
        path = charInput(0);
        Quest3(path, shift);
        break;

      case -1:
        break;
      default:
        printf("n/a\n");
        break;
    }
  }
}

void Quest1(char *path) {
  FILE *f = NULL;
  if (path == NULL) {
    printf("n/a\n");
  } else {
    f = fopen(path, "r");
    if (f == NULL || fgetc(f) == EOF) {
      printf("n/a\n");
    }
    rewind(f);
    char *data_from_file = charInputFromFile(f);

    str_output(data_from_file);
    if (data_from_file != NULL) free(data_from_file);
    fclose(f);
  }
}

void Quest2(char *path) {
  FILE *f = NULL;
  f = fopen(path, "r+");
  if (f == NULL) {
    printf("n/a\n");

  } else {
    fseek(f, SEEK_SET, SEEK_END);
    char *write = charInput(1);
    if (write != NULL) {
      charInputInFile(f, write);
      free(write);
    }
    fclose(f);
    Quest1(path);
  }
}

void Quest3(char *path, int shift) {
  DIR *d;
  struct dirent *ent;
  char slesh = '/';
  if (opendir(path) != NULL) {
    while (ent = readdir(d)) {
      if (is_type_file(ent->d_name, 'c')) {
        char *path_file = malloc(sizeof(char));
        s21_strcat(path_file, &slesh);
      }
    }
  }
  stdout = freopen("c_files", "wb+", stdout);
  system("ls ai_modules/*.c");

  stdout = freopen("h_files", "wb+", stdout);
  system("ls ai_modules/*.h");

  stdout = freopen("/dev/tty", "r", stdout);
  printf("Hello!");
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

int is_type_file(char *name, char type) {
  int res = 0;
  int size = strlen(name);
  if (size > 2) {
    if (name[size - 1] == type && name[size - 2] == '.') {
      int dotsCount = 0;
      for (int i = 0; i < size; i++)
        if (name[i] == '.') dotsCount++;
      if (dotsCount == 1) res = 1;
    }
  }
  return res;
}