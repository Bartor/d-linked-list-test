#include "d-linked-list.h"

#include <stdlib.h>

void insert(DLinkedList* list, int value) {
    Node* n = malloc(sizeof(Node));
    n->value = value;
    n->next = NULL;
    if (list->size == 0) {
        list->head = n;
        list->tail = n;
    } else {
        n->prev = list->tail;
        list->tail->next = n;
        list->tail = n;
    }
    list->size++;
}

Node* get(DLinkedList* list, int index) {
    if (index > list->size - 1 || index < 0) return NULL;
    if (index > list->size/2) {
        int i = list->size - 1;
        Node* current = list->tail;
        while (i-- != index) {
            current = current->prev;
        }
        return current;
    } else {
        int i = 0;
        Node* current = list->head;
        while (i++ != index) {
            current = current->next;
        }
        return current;
    }
}

Node* cachedGet(DLinkedList* list, int index) {
    if (index > list->size - 1 || index < 0) return NULL;
    if (list->last == NULL) {
        if (index > list->size/2) {
            int i = list->size - 1;
            Node* current = list->tail;
            while (i-- != index) {
                current = current->prev;
            }
            list->last = current;
            list->lastIdx = index;
            return current;
        } else {
            int i = 0;
            Node* current = list->head;
            while (i++ != index) {
                current = current->next;
            }
            list->last = current;
            list->lastIdx = index;
            return current;
        }
    } else {
        /**
         * H - - - - L - - - - - - - - - T
         *   1.    2.    3.        4.
         */
        if (index > list->lastIdx) {
            //3. and 4.
            if (index > list->lastIdx + (list->size - list->lastIdx)/2) {
                //4.
                int i = list->size - 1;
                Node* current = list->tail;
                while (i-- != index) {
                    current = current->prev;
                }
                list->last = current;
                list->lastIdx = index;
                return current;
            } else {
                //3.
                int i = list->lastIdx;
                Node* current = list->last;
                while (i++ != index) {
                    current = current->next;
                }
                list->last = current;
                list->lastIdx = index;
                return current;
            }
        } else {
            //1. and 2.
            if (index > list->lastIdx/2) {
                //2
                int i = list->lastIdx;
                Node* current = list->last;
                while (i-- != index) {
                    current = current->prev;
                }
                list->last = current;
                list->lastIdx = index;
                return current;
            } else {
                //1
                int i = 0;
                Node* current = list->head;
                while (i++ != index) {
                    current = current->next;
                }
                list->last = current;
                list->lastIdx = index;
                return current;
            }
        }
    }
}

void cleanUp(DLinkedList* list) {
    Node* temp = list->head, *last = list->head;
    while (last != NULL) {
        temp = last->next;
        free(last);
        last = temp;
    }   
}