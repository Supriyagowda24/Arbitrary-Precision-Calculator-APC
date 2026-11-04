/*
Name        : Supriya J
Date        : 26/10/2026

Project     : APC - Arbitrary Precision Calculator

Description : This program does +, -, x and / on very big numbers, which are too
              big for normal int or long variables. Each number is stored in a
              doubly linked list with one digit in every node. The calculation is
              done digit by digit, like we do on paper.
              Numbers can have a sign (+1234 or -1234). Division gives only the
              quotient (the whole number), not the decimal part.
              The program checks the input and shows an error for wrong input,
              for example 1ab4, a wrong operator or division by zero.

Sample input  : ./a.out 12345 x 123
Sample output :
---------------------------------
 Operand 1 : 12345
 Operand 2 : 123
 Operator  : x
---------------------------------
 Result    : 1518435
---------------------------------
*/

#include "apc.h"

static void show_operand(Dlist *head, int negative)
{
    if (negative && !is_zero(head))         // negative number (0 has no sign)
        printf("-");
    print_list(head);                       // print the digits
}

static int add_signed(Dlist *head1, Dlist *tail1, int neg1,
                      Dlist *head2, Dlist *tail2, int neg2,
                      Dlist **headR, Dlist **tailR, int *negative)
{
    if (neg1 == neg2)                       // same sign
    {
        *negative = neg1;                   // answer has the same sign
        return addition(tail1, tail2, headR, tailR);    // add the numbers
    }

    if (compare_list(head1, head2) == 1)    // different sign, number 1 is bigger
    {
        *negative = neg1;                   // answer has sign of number 1
        return subtraction(tail1, tail2, headR, tailR); // number 1 - number 2
    }

    *negative = neg2;                       // number 2 is bigger, answer has its sign
    return subtraction(tail2, tail1, headR, tailR);     // number 2 - number 1
}

int main(int argc, char *argv[])
{
    Dlist *head1 = NULL, *tail1 = NULL;     // list for operand 1
    Dlist *head2 = NULL, *tail2 = NULL;     // list for operand 2
    Dlist *headR = NULL, *tailR = NULL;     // list for result
    int neg1 = 0, neg2 = 0;                 // 1 if the operand has a '-' sign
    int negative = 0;                       // 1 if the result is negative
    int status = SUCCESS;                   // result of the operation

    if (validate_args(argc, argv) == FAILURE)   // check the input
        return FAILURE;

    if (store_operand(argv[1], &head1, &tail1) == FAILURE ||    // operand 1 -> list
        store_operand(argv[3], &head2, &tail2) == FAILURE)      // operand 2 -> list
    {
        printf("Error: Memory allocation failed.\n");
        free_list(&head1, &tail1);
        free_list(&head2, &tail2);
        return FAILURE;
    }

    remove_leading_zeros(&head1);           // 007 -> 7
    remove_leading_zeros(&head2);

    neg1 = (argv[1][0] == '-');             // operand 1 is negative
    neg2 = (argv[3][0] == '-');             // operand 2 is negative

    printf("\n---------------------------------\n");
    printf(" Operand 1 : ");
    show_operand(head1, neg1);              // print operand 1
    printf(" Operand 2 : ");
    show_operand(head2, neg2);              // print operand 2
    printf(" Operator  : %c\n", argv[2][0]);    // print the operator
    printf("---------------------------------\n");

    switch (argv[2][0])                     // check the operator
    {
        case '+':                           // addition
            status = add_signed(head1, tail1, neg1, head2, tail2, neg2,
                                &headR, &tailR, &negative);
            break;

        case '-':                           // subtraction : a - b = a + (-b)
            status = add_signed(head1, tail1, neg1, head2, tail2, !neg2,    // flip the sign of operand 2
                                &headR, &tailR, &negative);
            break;

        case 'x':                           // multiplication
            negative = (neg1 != neg2);      // signs are different, so result is negative
            status = multiplication(tail1, tail2, &headR, &tailR);
            break;

        case '/':                           // division
            negative = (neg1 != neg2);      // signs are different, so result is negative
            if (division(head1, head2, tail2, &headR, &tailR) == FAILURE)   // divide by zero or failure
            {
                printf("---------------------------------\n\n");
                free_list(&head1, &tail1);
                free_list(&head2, &tail2);
                free_list(&headR, &tailR);
                return FAILURE;
            }
            break;
    }

    if (status == SUCCESS && headR != NULL) // print the result
    {
        printf(" Result    : ");
        show_operand(headR, negative);      // result with its sign
        printf("---------------------------------\n\n");
    }

    free_list(&head1, &tail1);              // delete all the lists
    free_list(&head2, &tail2);
    free_list(&headR, &tailR);
    return status;
}