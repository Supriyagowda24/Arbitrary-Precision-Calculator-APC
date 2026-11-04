#include "apc.h"

int multiplication(Dlist *tail1, Dlist *tail2, Dlist **headR, Dlist **tailR)
{
    Dlist *temp1 = tail1;                   // moves through digits of number 1
    Dlist *temp2 = tail2;                   // moves through digits of number 2
    Dlist *headR1 = NULL, *tailR1 = NULL;   // result so far
    Dlist *headR2 = NULL, *tailR2 = NULL;   // one row (partial product)
    int carry = 0;                          // carry of multiplication
    int count = 0;                          // how many digits of number 2 are done
    int data = 0;                           // one digit x one digit

    while (temp2 != NULL)                   // take each digit of number 2
    {
        for (int i = 0; i < count; i++)     // add zeros at the end of the row
        {
            if (insert_first(&headR2, &tailR2, 0) == FAILURE)
                return FAILURE;
        }

        while (temp1 != NULL)               // multiply with each digit of number 1
        {
            data = temp1->data * temp2->data + carry;       // multiply and add carry
            if (insert_first(&headR2, &tailR2, data % 10) == FAILURE)   // store last digit
                return FAILURE;
            carry = data / 10;              // remaining part is the carry

            temp1 = temp1->prev;            // move to left digit
        }

        if (carry != 0)                     // carry left at the end of the row
        {
            if (insert_first(&headR2, &tailR2, carry) == FAILURE)   // add it at the start
                return FAILURE;
            carry = 0;                      // reset the carry
        }

        if (count == 0)                     // first row
        {
            headR1 = headR2;                // first row is the result so far
            tailR1 = tailR2;
            headR2 = NULL;                  // row list is free for next row
            tailR2 = NULL;
        }
        else                                // second row onwards
        {
            if (addition(tailR1, tailR2, headR, tailR) == FAILURE)  // result so far + this row
                return FAILURE;

            free_list(&headR1, &tailR1);    // delete the old result
            free_list(&headR2, &tailR2);    // delete the row

            headR1 = *headR;                // new sum is the result so far
            tailR1 = *tailR;
            *headR = NULL;                  // clear for the next addition
            *tailR = NULL;
        }

        temp2 = temp2->prev;                // next digit of number 2
        temp1 = tail1;                      // number 1 again from its last digit
        count++;                            // one more zero for the next row
    }

    remove_leading_zeros(&headR1);          // 000 -> 0

    *headR = headR1;                        // give the final result
    *tailR = tailR1;
    return SUCCESS;
}
