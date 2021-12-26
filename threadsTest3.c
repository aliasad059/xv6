#include "types.h"
#include "stat.h"
#include "user.h"
#define PGSIZE 4096

int stack[PGSIZE] __attribute__((__aligned__(PGSIZE)));
int x = 0;

void test(void)
{
    int tid = thread_create(stack);

    if (tid < 0)
    {
        printf(2, "Error!\n");
    }
    else if (tid == 0)
    {
        sleep(200);
        printf(1, "\nI'm child!\nI'm going to increase x 5 times!\n");
        sleep(100);
        for (int i = 0; i < 5; i++)
        {
            printf(1, "x is %d\n", ++x);
            sleep(100);
        }
        printf(1, "\nI'm child!\nI did my jobs!\n");
        sleep(100);
        exit();
    }
    else
    {
        printf(1, "\nI'm parent!\nI'm waiting for the child to do its jobs!\n");
        thread_wait();
    }
}

int main(int argc, char const *argv[])
{
    test();
    printf(1, "\nTesting for another thread...\n");
    test();

    printf(1, "\nI'm parent!\nI'm going to do my jobs right now!\n");
    printf(1, "x is now %d\n", x);
    exit();
}
