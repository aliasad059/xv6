#include "types.h"
#include "stat.h"
#include "user.h"

int main(void)
{
    int counter = getProcCount();
    printf(1,"%d\n",counter);
    exit();
    return 0;
}