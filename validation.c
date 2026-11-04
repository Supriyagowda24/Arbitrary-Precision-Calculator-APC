#include "apc.h"

static int is_numeric(const char *str)
{
    int i = 0;                              // start from first character

    if (str[i] == '+' || str[i] == '-')     // sign is allowed at the start
        i++;                                // skip the sign

    if (str[i] == '\0')                     // nothing after the sign (or empty)
        return FAILURE;

    for (; str[i] != '\0'; i++)             // check every character
    {
        if (!isdigit((unsigned char)str[i]))    // not a digit 0-9
            return FAILURE;
    }
    return SUCCESS;
}

int validate_args(int argc, char *argv[])
{
    if (argc != 4)                          // need: program, operand1, operator, operand2
    {
        printf("Error: Invalid argument count.\n");
        printf("Usage: %s <operand1> <operator> <operand2>\n", argv[0]);
        return FAILURE;
    }

    if (is_numeric(argv[1]) == FAILURE || is_numeric(argv[3]) == FAILURE)   // both operands must be numbers
    {
        printf("Error: Operands must contain only numeric characters.\n");
        return FAILURE;
    }

    if (strlen(argv[2]) != 1 || strchr("+-/x", argv[2][0]) == NULL)         // operator must be + - / x
    {
        printf("Error: Invalid operator. Use + - / x\n");
        return FAILURE;
    }

    return SUCCESS;
}
