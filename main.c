#include "d-linked-list.h"
#include "super-dll.h"

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
    cleanUp(&l);

    for (int cache = 1; cache < 10; cache++) {
        sdll sl = {NULL, NULL, malloc(sizeof(Cache*)*cache), cache, 0};
        for (int i = 0; i < SIZE; i++) {
            sinsert(&sl, i);
        }

        time = clock();
        for (int i = 0; i < SIZE; i++) {
            scachedGet(&sl, (rand()*rand() + rand()) % SIZE);
        }
        printf("super%d cached get: %f s\n", cache, (1.0*clock() - time)/CLOCKS_PER_SEC);
        scleanUp(&sl);
    }
    
    return 0;
}