#include <stdio.h>
#include <ctype.h>
#include "header.h"

bool isNumeric(const char *str)
{
    // Check if the string contains only numeric characters
    for (int i = 0; str[i] != '\0'; ++i)
    {
        if (i != 0 && str[i] == '-')
        {
            return false;
        }
        if (!isdigit(str[i]) && str[i] != '.' && str[i] != '-')
        {
            return false;
        }
    }
    return true;
}

bool parseFloat(double *myDouble)
{
    char input[100];
    if (scanf("%99s", input) != 1 || !isNumeric(input))
    {
        // %99s specifies the maximum number of characters to read from the input.
        return false;
        // Handle the error or prompt the user again.
    }
    else
    {
        sscanf(input, "%lf", myDouble);
    }

    return true;
}