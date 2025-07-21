#include <stdio.h>
#include <string.h>

// Function to read a string from standard input
void read_string(char *buffer, size_t size) {
  int c;
  // Clear any remaining newline characters from input buffer
  while ((c = getchar()) != '\n' && c != EOF)
    ;
  fgets(buffer, size, stdin); // Read the entire line, including spaces

  // Remove the trailing newline character, if present
  size_t len = strlen(buffer);
  if (len > 0 && buffer[len - 1] == '\n') {
    buffer[len - 1] = '\0';
  }
}
