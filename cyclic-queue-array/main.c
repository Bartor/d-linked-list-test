#include "cqa.h"

#include <stdlib.h>
#include <stdio.h>

int main(void) {
    CQA* q = new_cqa(2);
    push_head(q, 1);
    push_head(q, 2);
    push_head(q, 3);
    push_head(q, 4);
    push_head(q, 5);
    push_head(q, 6);

    printf("%d\n", q->data[0]);
    printf("%d\n", q->data[1]);
    printf("%d\n", q->data[2]);
    printf("%d\n", q->data[3]);
    printf("%d\n", q->data[4]);
    printf("%d\n", q->data[5]);
    printf("%d\n", q->data[6]);
    return 0;
}
