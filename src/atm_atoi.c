#include "stdbool.h"

int atm_atoi(const char *input) {
  int val = 0;
  int i = 0;
  int pos = 0;
  bool isNegative = false;
  while (input[i] != '\0') {
    if (input[i] == '-' && pos == 0) {
      isNegative = true;
    }
    if (input[i] >= '0' && input[i] <= '9') {
      val = val * 10 + (input[i] - '0');
    } else {
      return -1;
    }
    i++;
    pos++;
  }
  return isNegative == true ? (val * -1) : val;
}
