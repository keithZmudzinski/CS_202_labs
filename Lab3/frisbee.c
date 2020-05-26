#include "param.h"
#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
#include "fcntl.h"
#include "syscall.h"
#include "traps.h"
#include "memlayout.h"
#include "thread.h"

// Lab 3

struct arguments{
    int label;
    struct lock_t* lock;
    int* location;
    int numTimesToThrow;
    int numThreads;
};

void* throwFrisbee(void* inputArgs) {
    struct arguments* args = (struct arguments*)inputArgs;
    int numTimesThrown = 0;
    int numTimesIveThrown = 0;
    // exit();

    while(1) {
        lock_acquire(args->lock);
        if (*(args->location) == args->label) {
            int nextLocation = (args->label + 1) % args->numThreads;
            numTimesThrown = (numTimesIveThrown * args->numThreads) + args->label + 1;

            printf(1, "Pass number %d, Thread %d is passing to %d\n",
                numTimesThrown, args->label, nextLocation);

            *(args->location) = nextLocation;
            numTimesIveThrown += 1;
            if (numTimesIveThrown >= args->numTimesToThrow) {
                lock_release(args->lock);
                exit();
                // HERE BECAUSE RETURNING IN A THREAD CAUSES CRASHING AAAAAAAHHHH!!!!!!
                // while(1){
                //     asm("nop");
                // }
                // return 0;

            }
        }
        lock_release(args->lock);
    }
}

int calcNumTimesToThrow(int numThreads, int numThrows, int label) {
    int base = (numThrows / numThreads);
    if (label < (numThrows % numThreads)) {
        base += 1;
    }
    return base;
}

int main(int argc, char** argv) {
    int numThreads = atoi(argv[1]);
    int numThrows = atoi(argv[2]);
    struct arguments argList[numThreads];
    struct lock_t lock;

    // Initialize values
    lock_init(&lock);
    int location = 0;

    for (int i=0; i < numThreads; ++i) {
        argList[i].label = i;
        argList[i].lock = &lock;
        argList[i].location = &location;
        argList[i].numTimesToThrow = calcNumTimesToThrow(numThreads, numThrows, argList[i].label);
        argList[i].numThreads = numThreads;

        thread_create(&throwFrisbee, &(argList[i]));

    }

    exit();
}
