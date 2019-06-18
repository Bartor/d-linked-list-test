#include "d-linked-list.h"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int SIZE = 50000;

int main(void) {
    srand(time(NULL));
    DLinkedList l = {NULL, NULL, NULL, -1, 0};
    for (int i = 0; i < SIZE; i++) {
        insert(&l, i);
    }
    clock_t time = clock();
    for (int i = 0; i < SIZE; i++) {
        get(&l, (rand()*rand() + rand()) % SIZE);
    }
    printf("get: %f s\n", (1.0*clock() - time)/CLOCKS_PER_SEC);

    time = clock();
    for (int i = 0; i < SIZE; i++) {
        cachedGet(&l, (rand()*rand() + rand()) % SIZE);
    }
    printf("cached get: %f s\n", (1.0*clock() - time)/CLOCKS_PER_SEC);

    //wiem, że main po sobie nie sprząta i nie dealokuje, ale to tylko zabawka i test
    return 0;
}