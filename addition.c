#include "apc.h"

int addition(Dlist *tail1, Dlist *tail2, Dlist **headR, Dlist **tailR)
{
    int result = 0;                         // sum of one column
    int carry = 0;                          // carry to the next column

    while (tail1 != NULL || tail2 != NULL)  // until both numbers are finished
    {
        if (tail1 != NULL && tail2 != NULL) // both numbers have a digit
        {
            result = tail1->data + tail2->data + carry;     // add both digits and carry
            tail1 = tail1->prev;            // move to left digit
            tail2 = tail2->prev;            // move to left digit
        }
        else if (tail1 != NULL && tail2 == NULL)    // only number 1 has a digit
        {
            result = tail1->data + carry;   // digit and carry
            tail1 = tail1->prev;            // move to left digit
        }
        else                                // only number 2 has a digit
        {
            result = tail2->data + carry;   // digit and carry
            tail2 = tail2->prev;            // move to left digit
        }

        if (result > 9)                     // result has two digits
        {
            result = result % 10;           // keep the last digit
            carry = 1;                      // carry 1 to the next column
        }
        else
            carry = 0;                      // no carry

        if (insert_first(headR, tailR, result) == FAILURE)  // store the digit at the start
            return FAILURE;
    }

    if (carry == 1)                         // carry left at the end
    {
        if (insert_first(headR, tailR, carry) == FAILURE)   // add it at the start
            return FAILURE;
    }

    return SUCCESS;
}
