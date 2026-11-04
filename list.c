#include "apc.h"

static Dlist *create_node(int data)
{
    Dlist *new = malloc(sizeof(Dlist));     // get memory for one node
    if (new == NULL)                        // memory not available
        return NULL;
    new->data = data;                       // store the digit
    new->prev = NULL;                       // nothing on the left yet
    new->next = NULL;                       // nothing on the right yet
    return new;
}

int insert_last(Dlist **head, Dlist **tail, int data)
{
    Dlist *new = create_node(data);         // make a new node
    if (new == NULL)                        // node not created
        return FAILURE;

    if (*head == NULL)                      // list is empty
    {
        *head = *tail = new;                // new node is first and last
        return SUCCESS;
    }

    new->prev = *tail;                      // new node points back to old last node
    (*tail)->next = new;                    // old last node points to new node
    *tail = new;                            // new node is the last node now
    return SUCCESS;
}

int insert_first(Dlist **head, Dlist **tail, int data)
{
    Dlist *new = create_node(data);         // make a new node
    if (new == NULL)                        // node not created
        return FAILURE;

    if (*head == NULL)                      // list is empty
    {
        *head = *tail = new;                // new node is first and last
        return SUCCESS;
    }

    new->next = *head;                      // new node points to old first node
    (*head)->prev = new;                    // old first node points back to new node
    *head = new;                            // new node is the first node now
    return SUCCESS;
}

int store_operand(const char *str, Dlist **head, Dlist **tail)
{
    int i = 0;                              // start from first character

    if (str[i] == '+' || str[i] == '-')     // sign is not a digit
        i++;                                // skip the sign

    for (; str[i] != '\0'; i++)             // go through every character
    {
        if (insert_last(head, tail, str[i] - '0') == FAILURE)   // char -> digit, store at end
            return FAILURE;
    }
    return SUCCESS;
}

int list_length(Dlist *head)
{
    int len = 0;                            // count starts from 0
    while (head)                            // go through every node
    {
        len++;                              // count this node
        head = head->next;                  // move to next node
    }
    return len;
}

void remove_leading_zeros(Dlist **head)
{
    while (*head != NULL && (*head)->data == 0 && (*head)->next != NULL)   // first digit 0 and more digits after it
    {
        Dlist *temp = *head;                // keep the zero node
        *head = (*head)->next;              // move head to next node
        (*head)->prev = NULL;               // new first node has nothing on the left
        free(temp);                         // delete the zero node
    }
}

int is_zero(Dlist *head)
{
    return head != NULL && head->data == 0 && head->next == NULL;  // only one digit and it is 0
}

void print_list(Dlist *head)
{
    while (head)                            // go through every node
    {
        printf("%d", head->data);           // print the digit
        head = head->next;                  // move to next node
    }
    printf("\n");                           // new line at the end
}

void free_list(Dlist **head, Dlist **tail)
{
    while (*head)                           // until the list is empty
    {
        Dlist *temp = *head;                // keep the first node
        *head = (*head)->next;              // move head to next node
        free(temp);                         // delete the old first node
    }
    *tail = NULL;                           // list is empty now
}
