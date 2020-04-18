#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char** argv) {
    int value, value1, value2, value3, value4, value5, value6 = 0;
    int pid = 0;
    void* mem;

    // Test info(1)
    value = info(1);
    pid = fork();
    if (pid == 0) {
        exit();
    }
    value5 = info(1);
    wait();

    // Test info(2)
    value1 = info(2);
    for(int i = 0; i < 20; i++) {
        uptime();
    }
    value2 = info(2);

    // Test info(3)
    value3 = info(3);
    mem = malloc(24);
    value4 = info(3);
    free(mem);
    value6 = info(3);

    // Output info(1) info
    printf(1, "Called info(1), got %d processes.\nCalled fork, and then info(1) again from parent process.\n\
Got %d processes the second time.\n\n", value, value5);

    // Output info(2) info
    printf(1, "Called info(2), got %d system calls.\nThen called uptime() \
20 times, and called info(2) again.\nGot %d system calls the second time.\n\n", value1, value2);

    // Output info(3) info
    printf(1, "Called info(3), got %d pages.\nThen called malloc(24), \
and called info(3) again.\nGot %d pages the second time.\n\
Then called free(), and info(3) again.\n\
Got %d pages the third time.\n", value3, value4, value6);
    exit();
}
