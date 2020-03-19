#include <stdio.h>
#include "list.h"

// I used an old linked list implentation I made, I know it's not the best

// Recieves a list and an index and inserts a new node into the nth index of the list
int list_insert(List *l, const int n) {
    Node new;
    new.value = 10;

    if (n == 0) { // Head
        new.next = l->head;
        l->head->last = &new;
        l->head = &new;
        new.last = NULL;

        l->length++;
        return 0;
    } else if (n == get_length(l)) { // Tail
        append(l, &new);
        return 0;
    } else {
        Node *current = l->head;
        int index = 0;

        while (current != NULL) {
            if (index == n) {
                current->last->next = &new;
                new.next = current;

                l->length++;
                return 0;
            }

            index++;
            current = current->next;
        }
    }
    return -1;
}

int main() {
    List list = init();
    Node head, tail, node;
    head.value = 7;
    tail.value = 2;
    node.value = 5;

    append(&list, &head);
    append(&list, &tail);
    append(&list, &node);

    printf("%d\n", list_insert(&list, 3));
    
    Node *current = list.head;
    while (current != NULL) {
        printf("%d->", current->value);
        current = current->next;
    } printf("\n");

    destroy(&list);

    return 0;
}