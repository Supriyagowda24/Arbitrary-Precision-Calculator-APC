#include "apc.h"

int division(Dlist *head1, Dlist *head2, Dlist *tail2, Dlist **headR, Dlist **tailR)
{
    Dlist *temp = head1;                    // moves through digits of the dividend
    Dlist *head3 = NULL, *tail3 = NULL;     // list3 : part of the dividend taken so far
    int count = 0;                          // how many times the divisor is subtracted
    int started = 0;                        // becomes 1 after the first subtraction

    if (is_zero(head2))                     // divisor is 0
    {
        printf("Error: Division by zero.\n");
        return FAILURE;
    }

    while (temp != NULL)                    // take each digit of the dividend
    {
        if (insert_last(&head3, &tail3, temp->data) == FAILURE)     // add the digit to list3
        {
            free_list(&head3, &tail3);
            return FAILURE;
        }
        remove_leading_zeros(&head3);       // 05 -> 5

        if (compare_list(head3, head2) == 1)    // list3 >= divisor
        {
            while (compare_list(head3, head2) == 1)     // subtract until list3 < divisor
            {
                Dlist *headS = NULL, *tailS = NULL;     // answer of the subtraction

                if (subtraction(tail3, tail2, &headS, &tailS) == FAILURE)   // list3 - divisor
                {
                    free_list(&head3, &tail3);
                    return FAILURE;
                }

                free_list(&head3, &tail3);  // delete the old list3
                head3 = headS;              // answer becomes the new list3
                tail3 = tailS;

                count++;                    // one more subtraction done
            }

            if (insert_last(headR, tailR, count) == FAILURE)    // count is the quotient digit
            {
                free_list(&head3, &tail3);
                return FAILURE;
            }
            count = 0;                      // reset for the next digit
            started = 1;                    // quotient has started
        }
        else if (started == 1)              // list3 < divisor after the quotient started
        {
            if (insert_last(headR, tailR, 0) == FAILURE)        // quotient digit is 0
            {
                free_list(&head3, &tail3);
                return FAILURE;
            }
        }

        temp = temp->next;                  // take the next digit
    }

    free_list(&head3, &tail3);              // delete list3 (remainder is not needed)

    if (*headR == NULL)                     // dividend is smaller than divisor
    {
        if (insert_last(headR, tailR, 0) == FAILURE)    // quotient is 0
            return FAILURE;
    }

    return SUCCESS;
}
