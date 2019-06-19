#ifndef dllh
#define dllh

typedef struct Node {
    struct Node* next;
    struct Node* prev;
    void* value;
} Node;

typedef struct {
    Node* ref;
    int idx;
} Cache;

typedef struct {
    Node* head;
    Node* tail;
    int size;
    Cache* cache;
    int cache_size;
} DLL;

DLL* new_dll(int cache_size);
void ins(DLL* list, void* value);
void* get(DLL* list, int idx);
void del(DLL* list, int idx);
void del_dll(DLL* list);

#endif