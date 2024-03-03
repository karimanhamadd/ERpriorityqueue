/*
 * linkedlist.c
 *
 * Based on the implementation approach described in "The Practice 
 * of Programming" by Kernighan and Pike (Addison-Wesley, 1999).
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "emalloc.h"
#include "list.h"


Patient *new_patient(char *name, int birth_year, int priority) {
    assert( name != NULL);

    Patient *temp = (Patient *)emalloc(sizeof(Patient));

    temp->name       = strdup(name);
    temp->birth_year = birth_year;
    temp->priority   = priority;
    temp->next       = NULL;

    return temp;
}


Patient *add_front(Patient *list, Patient *new) {
    new->next = list;
    return new;
}


Patient *add_end(Patient *list, Patient *new) {
    Patient *curr;

    if (list == NULL) {
        new->next = NULL;
        return new;
    }

    for (curr = list; curr->next != NULL; curr = curr->next);
    curr->next = new;
    new->next = NULL;
    return list;
}


Patient *add_with_priority(Patient *list, Patient *new_patient) {
  /*This method adds a new patient to a linked list of patients
    in a sorted order based on priority.It takes a linked list of patients
    and a new patient, and inserts the new patient into the list in
    such a way that the resulting list remains sorted by priority 
    in ascending order.
    
    Parameters:
    - list  pointer to the head of the linked list of patients. 
    If the list is empty (NULL), the new patient becomes the head of the list.
    - new_patient A pointer to the new patient to be added to the list. The 
    new patient should have its priority field set.

    return:  pointer to the head of the modified linked list after
    inserting the new patient.
  */


    // If the list is empty or the new patient has higher priority than the head,
    // insert the new patient at the beginning and update the head.
    if (list == NULL || new_patient->priority < list->priority) {
        new_patient->next = list;
        return new_patient;
    }

    Patient *current = list;

    while (current->next != NULL && new_patient->priority >= current->next->priority) {
        current = current->next;
    }

    new_patient->next = current->next;
    current->next = new_patient;

    return list; // Return the head of the modified list
}


Patient *peek_front(Patient *list) {
    return list;
}


Patient *remove_front(Patient *list) {
    if (list == NULL) {
        return NULL;
    }

    return list->next;
}


void apply(Patient *list,
           void (*fn)(Patient *list, void *),
           void *arg)
{
    for ( ; list != NULL; list = list->next) {
        (*fn)(list, arg);
    }
}
