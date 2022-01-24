#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char* argv[])
{
  if(argc != 2){
    printf(2, "Usage: changePolicy <new_policy>");
    exit();
  }
  change_policy(atoi(argv[1]));
  exit();
}