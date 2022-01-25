#include "types.h"
#include "stat.h"
#include "user.h"
#define PROC_NUM 10

void printReport(int pid[PROC_NUM], int cts[PROC_NUM], int rts[PROC_NUM], int wts[PROC_NUM], int sts[PROC_NUM], int tts[PROC_NUM])
{
    int bt_avg = 0, tat_avg = 0, wt_avg = 0;
    printf(1, "PID\tCBT\tWT\tTAT\n");
    for (int i = 0; i < PROC_NUM; i++)
    {
        int bt = 0, tat = 0, wt = 0;
        bt = rts[i];
        tat = tts[i] - cts[i];
        wt = wts[i];
        printf(1, "|%d|%d|%d|%d|\n", pid[i], bt, wt, tat);
        bt_avg += bt;
        tat_avg += tat;
        wt_avg += wt;
    }
    printf(1, "AVG CBT\tAVG WT\tAVG TAT\n");
    printf(1, "|%d|%d|%d|\n", bt_avg / PROC_NUM, wt_avg / PROC_NUM, tat_avg / PROC_NUM);
}

void doSomeWork(int pid)
{
    for (int i = 1; i <= 1000; i++)
    {
        printf(1, "/%d/ : /%d/\n", pid, i);
    }
}

int main()
{
    int pid[PROC_NUM], cts[PROC_NUM], rts[PROC_NUM], wts[PROC_NUM], sts[PROC_NUM], tts[PROC_NUM], ps[PROC_NUM];

    change_policy(1); // change scheduling policy into round robin

    for (int i = 0; i < PROC_NUM; i++)
    {
        if (fork() == 0)
        {
            doSomeWork(getpid());
            exit();
        }
    }
    for (int i = 0; i < PROC_NUM; i++)
    {
        pid[i] = wait_and_init(&cts[i], &rts[i], &wts[i], &sts[i], &tts[i], &ps[i]);
    }

    printReport(pid, cts, rts, wts, sts, tts);

    exit();
    return 0;
}