#include "queries.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "time.h"
#include <stdio.h>

void log_error(const char *error) {
  // Open a file in append mode
  FILE *file = fopen("./log/errors.log", "a");

  // check if the file is not null | can be opened
  if (file == NULL) {
    printf("Error opening log file");
    exit(0); // exit status code
  }

  time_t now = time(NULL); /* Initialize time */
  char *time_str = ctime(&now);

  /* Removes the new line charater from time_str */
  time_str[strlen(time_str) - 1] = '\0';

  fprintf(file, "%s Error: %s \n", time_str, error);
  fclose(file); /* close file stream */
}
