#ifndef cqa
#define cqa

typedef struct {
    int* data;
    int size;
    int nums;
    int head;
    int tail;
} CQA;

CQA* new_cqa(int initial_size);
void push_head(CQA* q, int value);
void push_tail(CQA* q, int value);
void* pop_head(CQA* q);
void* pop_tail(CQA* q);

#endif