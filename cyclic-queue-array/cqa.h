#ifndef cqa
#define cqa

typedef struct {
    int* data;
    int size;
    int nums;
    int head;
    int tail;
} CQA;

/**
 * Structure of the CQA
 * 
 * 1. Regular
 *      _ | a | b | c | d | _ | _ | _
 *      H                   T
 * 2. Reversed
 *      c | d | _ | _ | _ | _ | a | b
 *              T           H
 * size = 8, nums = 4
 * 
 * [H]ead and [T]ail always point to the NEXT
 * field to be written to and they wrap around
 * the array.
 */

CQA* new_cqa(int initial_size);
void push_head(CQA* q, int value);
void push_tail(CQA* q, int value);
int pop_head(CQA* q);
int pop_tail(CQA* q);

#endif