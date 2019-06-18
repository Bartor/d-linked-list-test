#include "super-dll.h"

#include <stdlib.h>
#include <stdio.h>

void sinsert(sdll* list, int value) {
    Node* n = malloc(sizeof(Node));
    n->value = value;
    n->next = NULL;
    if (list->size == 0) {
        list->head = n;
        list->tail = n;

        //fill up the cache with any available data
        for (int i = 0; i < list->cacheSize; i++)  {
            list->cache[i] = malloc(sizeof(Cache));
            list->cache[i]->node = n;
            list->cache[i]->index = 0;
        }
    } else {
        n->prev = list->tail;
        list->tail->next = n;
        list->tail = n;
    }
    list->size++;
}

void shiftBack(Cache** array, int size, Cache* new) {
    free(array[size-1]);
    for (int i = 0; i < size - 1; i++) {
        array[i] = array[i+1];
    }
    array[size-1] = new;
}

Node* scachedGet(sdll* list, int index) {
    if (index > list->size - 1 || index < 0) return NULL;
    Node* current = NULL;
    //id is the index of current node
    //distance is the distance from index = abs(index - id) basically
    int id = -1, distance = -1;
    if (index > list->size/2) {
        current = list->tail;
        id = list->size -1;
        distance = list->size - index;
    } else {
        current = list->head;
        id = 0;
        distance = index;
    }
    for (int i = 0; i < list->cacheSize; i++) {
        if (abs(index - list->cache[i]->index) < distance) {
            current = list->cache[i]->node;
            id = list->cache[i]->index;
            distance = abs(index - list->cache[i]->index);
        }
    }

    if (index - id > 0) {
        while (id++ != index) {
            current = current->next;
        }
        Cache* last = malloc(sizeof(Cache));
        last->index = index;
        last->node = current;
        shiftBack(list->cache, list->cacheSize, last);
        return current;
    } else {
        while (id-- != index) {
            current = current->prev;
        }
        Cache* last = malloc(sizeof(Cache));
        last->index = index;
        last->node = current;
        shiftBack(list->cache, list->cacheSize, last);
        return current;
    }
}

void cleanUp(sdll* list) {
    Node* temp = list->head, *last = list->head;
    while (last != NULL) {
        temp = last->next;
        free(last);
        last = temp;
    }
    for (int i = 0; i < list->cacheSize; i++) free(list->cache[i]);
    free(list->cache);
}