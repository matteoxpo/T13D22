#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
#ifdef LOGGING_CIPHER
#include "log_levels.h"
#include "logger.h"
#endif
*/
#include "log_levels.h"
#include "logger.h"
#include "module_io.h"

void menu(int shift);

void Quest1(char *path);
void Quest2(char *path);
void Quest3(char *path, int shift);

int is_type_file(char *name, char type);
void code(FILE *src, FILE *res, int shift);
char *s21_strcat(char *str1, char *str2);

int main(int argc, char *argv[]) {
  int shift = 0;
  if (argc == 2) shift = atoi(argv[1]);
  shift++;
  shift--;
#ifdef LOGGING_CIPHER
  FILE *log = log_init("Quest5.log");
  fclose(log);
#endif
  menu(shift);

  return 0;
}

void menu(int shift) {
  int input = 0;
  char *path;

  while (input != -1) {
    while (!saveScan(&input)) {
      printf("n/a\n");
#ifdef LOGGING_CIPHER
      FILE *log = fopen("Quest5.log", "r+");
      logcat(log, "Input error", error);
      fclose(log);
#endif
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
#ifdef LOGGING_CIPHER
        FILE *log = fopen("Quest5.log", "r+");
        logcat(log, "Unknown command", error);
        fclose(log);
#endif
        break;
    }
  }
}

void Quest1(char *path) {
  FILE *f = NULL;
  if (path == NULL) {
    printf("n/a\n");
#ifdef LOGGING_CIPHER
    FILE *log = fopen("Quest5.log", "r+");
    logcat(log, "Empty path to file", warning);
    fclose(log);
#endif
  } else {
    f = fopen(path, "r");
    if (f == NULL || fgetc(f) == EOF) {
      printf("n/a\n");
#ifdef LOGGING_CIPHER
      FILE *log = fopen("Quest5.log", "r+");
      logcat(log, "Missing file in the specified directory", error);
      fclose(log);
#endif
    } else {
      rewind(f);
      char *data_from_file = charInputFromFile(f);

      str_output(data_from_file);
#ifdef LOGGING_CIPHER
      FILE *log = fopen("Quest5.log", "r+");
      logcat(log, "Reading from file has been completed", debug);
      fclose(log);
#endif
      if (data_from_file != NULL) free(data_from_file);
      fclose(f);
    }
  }
}

void Quest2(char *path) {
  FILE *f = NULL;
  f = fopen(path, "r+");
  if (f == NULL) {
    printf("n/a\n");
#ifdef LOGGING_CIPHER
    FILE *log = fopen("Quest5.log", "r+");
    logcat(log, "Unknown command", error);
    fclose(log);
#endif
  } else {
    fseek(f, SEEK_SET, SEEK_END);
    char *write = charInput(1);
    if (write != NULL) {
      charInputInFile(f, write);
      free(write);
#ifdef LOGGING_CIPHER
      FILE *log = fopen("Quest5.log", "r+");
      logcat(log, "writing to the file has been completed ", debug);
      fclose(log);
#endif
    }
    fclose(f);
    Quest1(path);
  }
}

void Quest3(char *path, int shift) {
  DIR *d;
  struct dirent *ent;
  char *slesh = "/\0";
  if ((d = opendir(path)) != NULL) {
    while ((ent = readdir(d)) != NULL) {
      if (is_type_file(ent->d_name, 'c') || is_type_file(ent->d_name, 'h')) {
        char *path_file = calloc(1, sizeof(char));
        s21_strcat(path_file, path);
        s21_strcat(path_file, slesh);
        s21_strcat(path_file, ent->d_name);

        if (ent->d_name[strlen(ent->d_name) - 1] == 'c') {
          FILE *file = fopen(path_file, "r");
          FILE *c_file = fopen(ent->d_name, "wb+");
          code(file, c_file, shift);
#ifdef LOGGING_CIPHER
          FILE *log = fopen("Quest5.log", "r+");
          logcat(log, "Encoding of the file is completed", error);
          fclose(log);
#endif
          fclose(file);
          fclose(c_file);
        }
        if (ent->d_name[strlen(ent->d_name) - 1] == 'h') {
          FILE *h_file = fopen(ent->d_name, "wb+");
          fclose(h_file);
#ifdef LOGGING_CIPHER
          FILE *log = fopen("Quest5.log", "r+");
          logcat(log, "The header file has been cleared", error);
          fclose(log);
#endif
        }
        free(path_file);
      }
    }
  } else {
    printf("n/a\n");
  }
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

char *s21_strcat(char *str1, char *str2) {
  int size1 = strlen(str1);
  int size2 = strlen(str2);
  str1 = (char *)realloc(str1, size1 + size2);
  for (int i = size1, k = 0; i < size1 + size2; i++, k++) {
    str1[i] = str2[k];
  }
  return str1;
}

void code(FILE *src, FILE *res, int shift) {
  char buff;
  int flag;
  while (fread(&buff, sizeof(char), 1, src)) {
    flag = 0;
    if (buff >= 'A' && buff <= 'Z') {
      buff = buff + (shift % 26);
      if (buff > 'Z') buff = 'A' + (buff - 'Z') - 1;
      fprintf(res, "%c", buff);
      flag = 1;
    }
    if (buff >= 'a' && buff <= 'z') {
      buff = buff + (shift % 26);
      if (buff > 'z') buff = 'a' + (buff - 'z') - 1;
      fprintf(res, "%c", buff);
      flag = 1;
    }
    if (!flag) fprintf(res, "%c", buff);
  }
}