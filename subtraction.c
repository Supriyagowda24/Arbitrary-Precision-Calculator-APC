#include "apc.h"

int compare_list(Dlist *head1, Dlist *head2)
{
    int length1 = list_length(head1);       // number of digits in number 1
    int length2 = list_length(head2);       // number of digits in number 2

    if (length1 > length2)                  // more digits means bigger number
        return 1;
    else if (length2 > length1)
        return 0;

    while (head1 != NULL && head2 != NULL)  // same length, compare digit by digit
    {
        if (head1->data == head2->data)     // same digit
        {
            head1 = head1->next;            // check next digit
            head2 = head2->next;
        }
        else if (head1->data > head2->data) // number 1 is bigger
            return 1;
        else                                // number 1 is smaller
            return 0;
    }
    return 1;                               // both are equal
}

int subtraction(Dlist *tail1, Dlist *tail2, Dlist **headR, Dlist **tailR)
{
    int result = 0;                         // answer of one column
    int borrow = 0;                         // 1 if we borrowed from the left digit

    while (tail1 != NULL)                   // number 1 is the bigger number
    {
        if (borrow == 1)                    // borrow was taken in the last column
        {
            tail1->data = tail1->data - 1;  // reduce this digit by 1
            borrow = 0;
        }

        if (tail2 != NULL)                  // number 2 still has a digit
        {
            if (tail1->data >= tail2->data) // top digit is big enough
            {
                result = tail1->data - tail2->data;     // simple subtraction
                borrow = 0;
            }
            else                            // top digit is small
            {
                result = (tail1->data + 10) - tail2->data;  // borrow 10 and subtract
                borrow = 1;                 // remember the borrow
            }
            tail2 = tail2->prev;            // move to left digit
        }
        else                                // number 2 is finished
        {
            if (tail1->data != -1)          // digit is fine
                result = tail1->data;       // copy the digit
            else                            // digit became -1 after borrow
            {
                result = tail1->data + 10;  // -1 + 10 = 9
                borrow = 1;                 // borrow again
            }
        }
        tail1 = tail1->prev;                // move to left digit

        if (insert_first(headR, tailR, result) == FAILURE)  // store the digit at the start
            return FAILURE;
    }

    remove_leading_zeros(headR);            // 001 -> 1
    return SUCCESS;
}
