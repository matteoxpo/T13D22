#include "logger.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "module_io.h"

FILE* log_init(char* filename) {
  FILE* new_file = fopen(filename, "wb+");
  return new_file;
}
int logcat(FILE* log_file, char* message, enum log_level level) {
  char* act = getAct(level);
  char* timed = getTime();
  char* res = malloc(1000 * sizeof(char));
  res[0] = '[';
  strcat(res, act);
  res[strlen(res) - 1] = ']';
  strcat(res, timed);
  strcat(res, message);
  charInputInFile(log_file, res);

  free(act);
  free(timed);
  free(res);
  return 1;
}

char* getTime() {
  time_t t = time(NULL);
  struct tm* aTm = localtime(&t);
  char timed[11];
  sprintf(timed, " %02d:%02d:%02d ", aTm->tm_hour, aTm->tm_min, aTm->tm_sec);
  char* res = calloc(11, sizeof(char));
  strcat(res, timed);
  return res;
}

char* getAct(enum log_level level) {
  char* res = malloc(8 * sizeof(char));
  if (res) {
    switch (level) {
      case debug:
        strcat(res, "debug");
        break;
      case trace:
        strcat(res, "trace");
        break;
      case info:
        strcat(res, "info");
        break;
      case warning:
        strcat(res, "warning");
        break;
      case error:
        strcat(res, "error");
        break;
    }
  }
  return res;
}

int log_close(FILE* log_file);