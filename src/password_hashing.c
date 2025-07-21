#include <ctype.h>

// Function to perform ROT13 encryption
void rot13(char *str) {
  while (*str) {
    if (isalpha(*str)) {
      char base = islower(*str) ? 'a' : 'A';
      *str = (char)(((int)(*str - base + 13) % 26) + base);
    }
    str++;
  }
}
