#ifndef JOB_H
#define JOB_H

struct Job{
    char id;
    int arrivalTime;
    int cpuCycle;
    int timeRemaining;
    int completionTime;
    int waitingTime;
    int turnaroundTime;
    int startTime;

    Job(char i, int a, int c);
};
#endif
