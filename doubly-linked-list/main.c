#include "dll.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int SIZE = 50000;
int MULT = 20;  
int CACH = 200;
int SMPL = 10;

int main(void) {    
    float times[CACH];
    memset(times, 0.0, CACH*sizeof(float));

    for (int t = 0; t < SMPL; t++) {
        for (int cache = 0; cache < CACH; cache++) {
            printf("RUN #%d CACHE=%d", t + 1, MULT*cache);

            DLL* list = new_dll(MULT*cache);
            srand(time(NULL));
            printf(".");

            for (int i = 0; i < SIZE; i++) {
                ins(list, i);
            }
            printf(".");

            clock_t time = clock();
            for (int i = 0; i < SIZE; i++) {
                int id = (rand() * rand() + rand()) % SIZE;
                get(list, id);
            }
            times[cache] += (1.0*clock() - time)/(CLOCKS_PER_SEC*SMPL);
            printf(".");

            del_dll(list);
            printf(" done\n");
        }
    }

    for (int i = 0; i < CACH; i++) {
        printf("%d; %f\n", MULT*i, times[i]);
    }

    return 0;
}