#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "emalloc.h"

#define MAX_LINE_LEN 5000

void inccounter(Patient *p, void *arg) {
    /* DO NOT CHANGE THIS FUNCTION. */
    int *ip = (int *)arg;
    (*ip)++;
}


void print_word(Patient *p, void *arg) {
    /* DO NOT CHANGE THIS FUNCTION. */
    char *fmt = (char *)arg;
    printf(fmt, p->name, p->birth_year, p->priority);
}


void dump(Patient *list) {
    /* DO NOT CHANGE THIS FUNCTION. */
    int len = 0;

    apply(list, inccounter, &len);    
    printf("Number of patients: %d\n", len);

    apply(list, print_word, "%s,%d,%d\n");
}

Patient *tokenize_line(char *line) {
  /*this method tokenizes a line sent by read lines and check if its enqueue
    or dequeue , if its enqueue it will assign a value to name year and 
    priority while making sure to convert a string into an integer 
    
 
  */
    char *name;
    int birth_year, priority;

    /*we will first assign a token to the string in the line , 
      the blank spaces would not count as we are using strtok
    */
    char *token = strtok(line, ",\n");

    /*we will now see if the token is a enqueue or dequeue or nothing 
      and do the corresponding operations to it 
    */
    if (strcmp(token, "enqueue") == 0) {
        name = strtok(NULL, ",");
        birth_year = atoi(strtok(NULL, ","));
        priority = atoi(strtok(NULL, ","));
        return new_patient(name, birth_year, priority);
    } else if (strcmp(token, "dequeue") == 0) {
        return NULL ;
    } else {
        exit(1);
    }
}


Patient *read_lines(Patient *list) {
  /*this method reads each line from a patient list and sends eahc line 
    one by one to the tokenizing line method , if the patient returned is not 
    NULL , therefore not dequeue then it will add with priority the patient 
    to the list , else it will remove the patient at the front of the list 

    Parameters: patient list pointer
    Returns: the final list
  */
    char line[MAX_LINE_LEN];
    while (fgets(line, sizeof(line), stdin) != NULL) {
        Patient *patient = tokenize_line(line);
        if (patient != NULL) {
            list = add_with_priority(list, patient);
        } else {
            list = remove_front(list);
        }
    }
    return list;
}



void deallocate_memory(Patient *list) {
  /* Deallocates memory for a linked list of Patient structure,
     the method frees the memory allocated for a linked list of 
     Patient structures,including the memory allocated for 
     each patient's name.
     Parameter: list A pointer to the head of the linked list.
 */

    while (list != NULL) {
        Patient *temp = list;
        list = list->next;
        free(temp->name);
        free(temp);
    }
}



int main(int argc, char *argv[]) {
    /* DO NOT CHANGE THE MAIN FUNCTION. YOU HAVE TO IMPLEMENT YOUR
        CODE TO FOLLOW THE SEQUENCE OF INSTRUCTIONS BELOW. */
    Patient *list = NULL;

    if (argc != 1) {
            printf("Usage: %s\n", argv[0]);
            printf("Should receive no parameters\n");
            printf("Read from the stdin instead\n");
            exit(1);
    }

    list = read_lines(list);
 
    dump(list);
    
    deallocate_memory(list);

    exit(0); 
}
