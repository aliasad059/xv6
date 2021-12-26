#include "types.h"
#include "stat.h"
#include "user.h"
#define PGSIZE 4096

int stack[PGSIZE] __attribute__ ((__aligned__(PGSIZE)));
int x = 0;

int main(int argc, char const *argv[])
{
    // int tid = fork();
    int tid = thread_create(stack);

    if (tid < 0)
    {
        printf(2, "Error!\n");
    }
    else if (tid == 0)
    {
        for (;;)
        {
            x++;
            sleep(100);
        }
    }
    else
    {
        for (;;)
        {
            printf(1, "x = %d\n", x);
            sleep(100);
        }
    }

    exit();
}
