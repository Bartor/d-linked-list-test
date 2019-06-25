#include "cqa.h"

#include <stdlib.h>
#include <stdio.h>

void printCQA(CQA* q) {
    printf("\thead at %d, tail at %d\n\
\tsize is %d, nums is %d\n", q->head, q->tail, q->size, q->nums);
    for (int i = 0; i < q->nums; i++) {
        printf("%d", q->data[(q->head + i + 1) % q->size]);
        if (i != q->nums - 1) printf(" | ");
    }
    printf("\n");
}

int main(void) {
    //just some testing
    CQA* q = new_cqa(2);
    push_head(q, 1);
    push_head(q, 2);
    printCQA(q);
    push_head(q, 3);
    push_head(q, 4);
    printCQA(q);
    printf("POPH: %d\n", pop_head(q));
    printf("POPT: %d\n", pop_tail(q));
    printf("POPH: %d\n", pop_head(q));
    printf("POPT: %d\n", pop_tail(q));
    printCQA(q);
    push_head(q, 1);
    push_head(q, 2);
    printCQA(q);
    push_head(q, 3);
    push_head(q, 4);
    printCQA(q);
    push_head(q, 5);
    push_head(q, 6);
    push_head(q, 7);
    push_tail(q, 0);
    push_tail(q, -1);
    push_tail(q, -2);
    printCQA(q);
    printf("POPH: %d\n", pop_head(q));
    printf("POPT: %d\n", pop_tail(q));
    printf("POPH: %d\n", pop_head(q));
    printf("POPT: %d\n", pop_tail(q));
    printf("POPH: %d\n", pop_head(q));
    printf("POPT: %d\n", pop_tail(q));
    printf("POPH: %d\n", pop_head(q));
    printCQA(q);

    return 0;
}
