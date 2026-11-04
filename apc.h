#ifndef APC_H                               // run this file only once
#define APC_H

#include <stdio.h>                          // printf
#include <stdlib.h>                         // malloc, free
#include <string.h>                         // strlen, strchr
#include <ctype.h>                          // isdigit

#define SUCCESS 0                           // function worked
#define FAILURE -1                          // function failed

typedef struct dlist                        // one node = one digit
{
    int data;                               // the digit
    struct dlist *prev;                     // node on the left side
    struct dlist *next;                     // node on the right side
} Dlist;

int validate_args(int argc, char *argv[]);  // validation.c : check the input

int insert_last(Dlist **head, Dlist **tail, int data);      // list.c : add node at the end
int insert_first(Dlist **head, Dlist **tail, int data);     // list.c : add node at the start
int store_operand(const char *str, Dlist **head, Dlist **tail); // list.c : string -> list
int list_length(Dlist *head);               // list.c : count the nodes
void remove_leading_zeros(Dlist **head);    // list.c : 007 -> 7
int is_zero(Dlist *head);                   // list.c : is the number 0
void print_list(Dlist *head);               // list.c : print the number
void free_list(Dlist **head, Dlist **tail); // list.c : delete the list

int addition(Dlist *tail1, Dlist *tail2, Dlist **headR, Dlist **tailR);        // addition.c

int compare_list(Dlist *head1, Dlist *head2);                                   // subtraction.c : which is bigger
int subtraction(Dlist *tail1, Dlist *tail2, Dlist **headR, Dlist **tailR);      // subtraction.c

int multiplication(Dlist *tail1, Dlist *tail2, Dlist **headR, Dlist **tailR);  // multiplication.c

int division(Dlist *head1, Dlist *head2, Dlist *tail2, Dlist **headR, Dlist **tailR); // division.c

#endif
