/**
 * Author: Bartosz Barnaba Rajczyk
 * 
 * Doubly linked list with heuristics on accessing particular index
 * with varying cache size.
 */

#include "dll.h"

#include <stdlib.h>

DLL* new_dll(int cache_size) {
    DLL* list = malloc(sizeof(DLL));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;

    Cache* cache = malloc(sizeof(Cache)*cache_size);
    list->cache = cache;
    list->cache_size = cache_size;

    return list;
}

void ins(DLL* list, void* value) {
    Node* node = malloc(sizeof(Node));
    node->value = value;
    node->next = NULL;
    if (list->size == 0) {
        list->head = node;
        list->tail = node;

        for (int i = 0; i < list->cache_size; i++) {
            list->cache[i].ref = node;
            list->cache[i].idx = 0;
        }
    } else {
        node->prev = list->tail;
        list->tail->next = node;
        list->tail = node;
    }
    list->size++;
}

Node* _get(DLL* list, int idx) {
    //we can't return anything outside the list
    if (idx < 0 || idx > list->size - 1) return NULL;

    Node* res = NULL;
    int res_idx = -1;

    //setting res for head or tail according to which one is closer
    if (idx < list->size/2) {
        res = list->head;
        res_idx = 0;
    } else {
        res = list->tail;
        res_idx = list->size - 1;
    }

    int mi = -1;
    if (list->cache_size > 0) {
        //binary search on sorted cache
        int lo = 0, hi = list->cache_size - 1;
        mi = (lo+hi)/2;
        while(lo <= hi) {
            if (idx > list->cache[mi].idx) {
                lo = mi + 1;
            } else {
                hi = mi - 1;
            }
            mi = (lo+hi)/2;
        }

        //get the result
        res_idx = list->cache[mi].idx;
        res = list->cache[mi].ref;
    }

    if (idx > res_idx) {
        while(res_idx++ != idx) res = res->next;
    } else if (idx != res_idx) {
        while(res_idx-- != idx) res = res->prev;
    }
    
    //if we found something closest in cache, we update its position in cache
    //that way the cache is always sorted (really!)
    if (mi != -1) {
        list->cache[mi].idx = idx;
        list->cache[mi].ref = res;
    }

    return res;
}

void* get(DLL* list, int idx) {
    Node* res = _get(list, idx);
    if (res == NULL) return NULL;
    return res->value;
}


void del(DLL* list, int idx) {
    Node* toDelete = _get(list, idx);
    for (int i = 0; i < list->cache_size; i++) {
        if (list->cache[i].idx > idx) {
            //we decrement the id of every cached element after deleted element
            list->cache[i].idx--;
        } else if (list->cache[i].idx == idx) {
            //if we have deleted element cached
            if (list->cache_size > 1) {
                //if the cache is more than one element
                if (i == list->cache_size - 1 && i != 0) {
                    //if it's the last one in cache, copy previous record
                    list->cache[i].idx = list->cache[i-1].idx;
                    list->cache[i].ref = list->cache[i-1].ref;
                } else {
                    //if it'n not the last one, copy next
                    list->cache[i].idx = list->cache[i+1].idx;
                    list->cache[i].ref = list->cache[i+1].ref;
                }
            } else {
                //if the cache was one element
                if (list->size == 1) {
                    //if we're deleting the only element
                    //todo think of something clever
                } else {
                    //if there are more elements, just replace it with middle element
                    list->cache[i].idx = list->size/2;
                    list->cache[i].ref = _get(list, list->size/2);
                }
            }
        }
    }

    if (list->head == toDelete) {
        list->head = toDelete->next;
    }

    if (list->tail == toDelete) {
        list->tail = toDelete->prev;
    }

    toDelete->prev->next = toDelete->next;
    toDelete->next->prev = toDelete->prev;

    free(toDelete);
}

void del_dll(DLL* list) {
    Node* temp = list->head, *last = list->head;

    while (last != NULL) {
        temp = last->next;
        free(last);
        last = temp;
    }

    free(list->cache);
    free(list);
}