#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

int
sys_getHelloWorld(void)
{
  return getHelloWorld();
}

int 
sys_getProcCount(void)
{
  return getProcCount();
}

int
sys_getReadCount(void)
{
  return getReadCount();
}

int
sys_thread_create(void)
{
  int stack;
  if(argint(0,&stack) < 0){
    return -1;
  }
  return thread_create((void *)stack);
}

int
sys_thread_wait(void)
{
  return thread_wait();
}

int
sys_set_priority(void){
  int pid, priority;
  if((argint(0, &priority) < 0) || (argint(1, &pid) < 0))
    return -1;
  return set_priority(priority, pid);
}

int
sys_change_policy(void){
  int new_policy;
  if (argint(0, &new_policy) < 0)
    return -1;
  return change_policy(new_policy);
}

int
sys_wait_and_init(void){
  int *creationtime, *runtime, *waittime, *sleepingtime, *terminationtime, *priority;
  if(argptr(0, (void*)&creationtime, sizeof(creationtime)) < 0)
    return -1;
  if(argptr(1, (void*)&runtime, sizeof(runtime)) < 0)
    return -1;
  if(argptr(2, (void*)&waittime, sizeof(waittime)) < 0)
    return -1;
  if(argptr(3, (void*)&sleepingtime, sizeof(sleepingtime)) < 0)
    return -1;
  if(argptr(4, (void*)&terminationtime, sizeof(terminationtime)) < 0)
    return -1;
  if(argptr(5, (void*)&priority, sizeof(priority)) < 0)
    return -1;
  return wait_and_init(creationtime, runtime, waittime, sleepingtime, terminationtime, priority);
}