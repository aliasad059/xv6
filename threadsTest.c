#include "types.h"
#include "stat.h"
#include "user.h"

void childPrint(void *args)
{
    printf(1, "hi, children function executed properly with argument : %d\n", *(int *)args);
}

int main(int argc, char const *argv[])
{
    int argument = 0x0F01;
    int thread_id = thread_creator(&childPrint, (void *)&argument);
    if (thread_id < 0)
        printf(1, "failure\n");

    thread_wait();

    printf(1, "thread_id is : %d\n", thread_id);

    return 0;
}
