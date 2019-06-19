#ifndef superdll
#define superdll

#include "d-linked-list.h"

typedef struct {
    Node* node;
    int index;
} Cache;

typedef struct {
    Node* head;
    Node* tail;
    Cache** cache;
    int cacheSize;
    int size;
} sdll;

void sinsert(sdll* list, int value);
Node* scachedGet(sdll* list, int index);
void scleanUp(sdll* list);

#endif