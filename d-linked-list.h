#ifndef dlinkedlist
#define dlinkedlist

typedef struct Node {
    struct Node* prev;
    struct Node* next;
    int value;
} Node;

typedef struct {
    Node* head;
    Node* tail;
    Node* last;
    int lastIdx;
    int size;
} DLinkedList;

void insert(DLinkedList* list, int value);
Node* get(DLinkedList* list, int index);
Node* cachedGet(DLinkedList* list, int index);

#endif