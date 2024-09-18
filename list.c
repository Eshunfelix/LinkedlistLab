// list/list.c
// 
// Implementation for linked list.
//
// <Author>

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// #include "list.h"

// list_t *list_alloc() { 
//   list_t* mylist =  (list_t *) malloc(sizeof(list_t)); 
//   mylist->head = NULL;
// }

// void list_free(list_t *l) {}

// void list_print(list_t *l) {}

// char * listToString(list_t *l) {
//   char* buf = (char *) malloc(sizeof(char) * 1024);
//   char tbuf[20];

// 	node_t* curr = l->head;
//   while (curr != NULL) {
//     sprintf(tbuf, "%d->", curr->value);
//     curr = curr->next;
//     strcat(buf, tbuf);
//   }
//   strcat(buf, "NULL");
//   return buf;
// }

// int list_length(list_t *l) { return -1; }

// void list_add_to_back(list_t *l, elem value) {

// }
// void list_add_to_front(list_t *l, elem value) {
//      node_t* cur_node = (node_t *) malloc(sizeof(node_t));
//      cur_node->value = value;
//      cur_node->next = NULL;

//      /* Insert to front */

//      node_t* head = l->head;  // get head of list

//      cur_node->next = head;
//      head = cur_node;
// }

// void list_add_at_index(list_t *l, elem value, int index) {}

// elem list_remove_from_back(list_t *l) { return -1; }
// elem list_remove_from_front(list_t *l) { return -1; }
// elem list_remove_at_index(list_t *l, int index) { return -1; }

// bool list_is_in(list_t *l, elem value) { return false; }
// elem list_get_elem_at(list_t *l, int index) { return -1; }
// int list_get_index_of(list_t *l, elem value) { return -1; }


// list/list.c
// Implementation for linked list.
// <Author>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

// Allocates memory for the list and initializes it
list_t *list_alloc() { 
    list_t *mylist = (list_t *) malloc(sizeof(list_t)); 
    mylist->head = NULL;
    return mylist;
}

// Frees all the memory allocated for the list
void list_free(list_t *l) {
    node_t *current = l->head;
    node_t *next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    free(l);
}

// Prints the list in a human-readable format
void list_print(list_t *l) {
    node_t *current = l->head;
    while (current != NULL) {
        printf("%d -> ", current->value);
        current = current->next;
    }
    printf("NULL\n");
}

// Converts list to string
char *listToString(list_t *l) {
    char *buf = (char *) malloc(sizeof(char) * 1024);
    char tbuf[20];
    node_t *curr = l->head;
    strcpy(buf, "");  // Initialize the buffer
    while (curr != NULL) {
        sprintf(tbuf, "%d->", curr->value);
        strcat(buf, tbuf);
        curr = curr->next;
    }
    strcat(buf, "NULL");
    return buf;
}

// Returns the length of the list
int list_length(list_t *l) {
    int length = 0;
    node_t *current = l->head;
    while (current != NULL) {
        length++;
        current = current->next;
    }
    return length;
}

// Adds an element to the back of the list
void list_add_to_back(list_t *l, elem value) {
    node_t *new_node = (node_t *) malloc(sizeof(node_t));
    new_node->value = value;
    new_node->next = NULL;

    if (l->head == NULL) {
        l->head = new_node;
    } else {
        node_t *current = l->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
}

// Adds an element to the front of the list
void list_add_to_front(list_t *l, elem value) {
    node_t *new_node = (node_t *) malloc(sizeof(node_t));
    new_node->value = value;
    new_node->next = l->head;
    l->head = new_node;
}

// Adds an element at a specific index in the list
void list_add_at_index(list_t *l, elem value, int index) {
    if (index == 0) {
        list_add_to_front(l, value);
        return;
    }
    node_t *new_node = (node_t *) malloc(sizeof(node_t));
    new_node->value = value;
    node_t *current = l->head;
    int i;
    for (i = 0; i < index - 1 && current != NULL; i++) {
        current = current->next;
    }
    if (current == NULL) {
        free(new_node);
        return; // index out of bounds
    }
    new_node->next = current->next;
    current->next = new_node;
}

// Removes the last element from the list
elem list_remove_from_back(list_t *l) {
    if (l->head == NULL) return -1;

    node_t *current = l->head;
    if (current->next == NULL) { // Only one element
        elem value = current->value;
        free(current);
        l->head = NULL;
        return value;
    }

    while (current->next->next != NULL) {
        current = current->next;
    }
    elem value = current->next->value;
    free(current->next);
    current->next = NULL;
    return value;
}

// Removes the first element from the list
elem list_remove_from_front(list_t *l) {
    if (l->head == NULL) return -1;
    node_t *temp = l->head;
    elem value = temp->value;
    l->head = l->head->next;
    free(temp);
    return value;
}

// Removes the element at a specific index
elem list_remove_at_index(list_t *l, int index) {
    if (l->head == NULL || index < 0) return -1;
    if (index == 0) return list_remove_from_front(l);

    node_t *current = l->head;
    int i;
    for (i = 0; i < index - 1 && current->next != NULL; i++) {
        current = current->next;
    }

    if (current->next == NULL) return -1; // index out of bounds

    node_t *temp = current->next;
    elem value = temp->value;
    current->next = temp->next;
    free(temp);
    return value;
}

// Checks if the value is in the list
bool list_is_in(list_t *l, elem value) {
    node_t *current = l->head;
    while (current != NULL) {
        if (current->value == value) return true;
        current = current->next;
    }
    return false;
}

// Returns the element at the given index
elem list_get_elem_at(list_t *l, int index) {
    node_t *current = l->head;
    int count = 0;
    while (current != NULL) {
        if (count == index) return current->value;
        count++;
        current = current->next;
    }
    return -1; // index out of bounds
}

// Returns the index of the given value
int list_get_index_of(list_t *l, elem value) {
    node_t *current = l->head;
    int index = 0;
    while (current != NULL) {
        if (current->value == value) return index;
        current = current->next;
        index++;
    }
    return -1; // value not found
}
