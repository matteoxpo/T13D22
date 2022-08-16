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

int Quest1(char *path);
int Quest2(char *path);
int Quest3(char *path, int shift);

int is_type_file(char *name, char type);
void code(FILE *src, FILE *res, int shift);

int main(int argc, char *argv[]) {
  int shift = 0;
  if (argc == 2) shift = atoi(argv[1]);
  shift++;
  shift--;

  menu(shift);

  return 0;
}

void menu(int shift) {
  int input = 0;
  char *path;
#ifdef LOGGING_CIPHER
  FILE *log = log_init("Quest5.log");
#endif
  while (input != -1) {
    while (!saveScan(&input)) {
      printf("n/a\n");
    }
    switch (input) {
      case 1:
        if (path != NULL) free(path);
        path = NULL;
        path = charInput(0);
        if (Quest1(path)) {
#ifdef LOGGING_CIPHER
          logcat(log, "Reading from file has been completed.\n\0", debug);
#endif
        } else {
#ifdef LOGGING_CIPHER
          logcat(log, "Reading from file has NOT been completed.\n\0", error);
#endif
          if (path != NULL) free(path);
          path = NULL;
        }
        break;
      case 2:
        if (Quest2(path)) {
#ifdef LOGGING_CIPHER
          logcat(log, "Writing in file has been completed.\n\0", debug);
#endif
        }
        break;
      case 3:
        if (path != NULL) free(path);
        path = NULL;

        path = charInput(0);
        if (Quest3(path, shift)) {
#ifdef LOGGING_CIPHER
          logcat(log, "Codin file has been completed.\n\0", debug);
#endif
        } else {
#ifdef LOGGING_CIPHER
          logcat(log, "Coding file has NOT been completed.\n\0", error);
#endif
        }
        if (path != NULL) free(path);
        path = NULL;
        break;
      case -1:
#ifdef LOGGING_CIPHER
        logcat(log, "EXIT.\n\0", debug);
#endif
        break;
      default:
#ifdef LOGGING_CIPHER
        logcat(log, "Unknow command.\n\0", warning);
#endif
        printf("n/a\n");
        break;
    }
  }
  if (path != NULL) free(path);
#ifdef LOGGING_CIPHER
  if (log != NULL) log_close(log);
#endif
}

int Quest1(char *path) {
  int res = 1;
  FILE *f = NULL;
  if (path == NULL) {
    printf("n/a\n");
    res = 0;
  } else {
    f = fopen(path, "r");
    if (f == NULL || fgetc(f) == EOF) {
      printf("n/a\n");
      res = 0;
    } else {
      rewind(f);
      char *data_from_file = charInputFromFile(f);

      str_output(data_from_file);

      if (data_from_file != NULL) free(data_from_file);
      fclose(f);
    }
  }
  return res;
}

int Quest2(char *path) {
  int res = 1;
  FILE *f = NULL;
  f = fopen(path, "r+");
  if (f == NULL) {
    printf("n/a\n");
    res = 0;
  } else {
    fseek(f, SEEK_SET, SEEK_END);
    char *write = charInput(1);
    if (write != NULL) {
      charInputInFile(f, write);
      if (write != NULL) free(write);
    } else {
      printf("n/a\n");
      res = 0;
    }
    fclose(f);
    Quest1(path);
  }
  return res;
}

int Quest3(char *path, int shift) {
  int res = 0;
  DIR *d;
  struct dirent *ent;
  char *slesh = "/\0";

  if ((d = opendir(path)) != NULL) {
    while ((ent = readdir(d)) != NULL) {
      if (is_type_file(ent->d_name, 'c') || is_type_file(ent->d_name, 'h')) {
        char *path_file = calloc(1000, sizeof(char));
        strcat(path_file, path);
        strcat(path_file, slesh);
        strcat(path_file, ent->d_name);

        if (ent->d_name[strlen(ent->d_name) - 1] == 'c') {
          FILE *file = fopen(path_file, "r");
          FILE *c_file = fopen(ent->d_name, "wb+");
          code(file, c_file, shift);
          fclose(file);
          fclose(c_file);
          res = 1;
        }
        if (ent->d_name[strlen(ent->d_name) - 1] == 'h') {
          FILE *h_file = fopen(ent->d_name, "wb+");
          fclose(h_file);
          res = 1;
        }

        if (path_file != NULL) free(path_file);
        path_file = NULL;
      }
    }
    closedir(d);
  } else {
    printf("n/a\n");
  }
  return res;
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
