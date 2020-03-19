#include "list.h"
#include <stdlib.h>
#include <stdio.h>

List init() {
    List new_list;
    new_list.head = new_list.tail = NULL;
    new_list.length = new_list.sum = 0;
    return new_list;
}

void destroy(List *list) {
    Node *current = list->head;
    Node *copy;

    while (current != NULL) {
        copy = current;
        current = current->next;
        copy->next = copy->last = NULL;
    }
}

void append(List *list, Node *node) {
    if (list->head == NULL) {
        list->head = list->tail = node;
    } else {
        list->tail->next = node;
        node->last = list->tail;
        list->tail = node;
    }

    list->tail->next = NULL;
    list->length++;
    list->sum += node->value;
}

int delete(List *list, Node *node) {
    if (list->head == node || list->tail == node) {
        if (list->head == node) {
            list->head = list->head->next;
            if (list->head != NULL) 
                list->head->last = NULL;
        }
        if (list->tail == node) {
            list->tail = list->tail->last;
            if (list->tail != NULL) 
                list->tail->next = NULL;
        }
    } else 
        node->last->next = node->next;
    
    node->next = node->last = NULL;

    list->length--;
    list->sum -= node->value;

    return node->value;
}

int get_length(List *list) {
    return list->length;
}

Node *get_head(List *list) {
    return list->head;
}

Node *get_tail(List *list) {
    return list->tail;
}

Node *get_next(Node *node) {
    return node->next;
}

Node *get_last(Node *node) {
    return node->last;
}

int get_value(Node *node) {
    return node->value;
}

float get_avg(List *list) {
    return list->sum / list->length;
}
