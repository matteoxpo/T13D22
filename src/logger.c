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
  char act[10] = "\0";
  switch (level) {
    case debug:
      strcat(act, "debug");
      break;
    case trace:
      strcat(act, "trace");
      break;
    case info:
      strcat(act, "info");
      break;
    case warning:
      strcat(act, "warning");
      break;
    case error:
      strcat(act, "error");
      break;
  }
  time_t t = time(NULL);
  struct tm* aTm = localtime(&t);
  char timed[11] = "\0";
  timed[0] = '\0';
  sprintf(timed, " %02d:%02d:%02d ", aTm->tm_hour, aTm->tm_min, aTm->tm_sec);
  char res[1000] = "\0";
  char lBrackets[] = "[\0";
  char rBrackets[] = "]\0";

  strcat(res, lBrackets);
  strcat(res, act);
  strcat(res, rBrackets);
  strcat(res, timed);
  strcat(res, message);

  charInputInFile(log_file, res);

  return 1;
}

int log_close(FILE* log_file) { return fclose(log_file); }
