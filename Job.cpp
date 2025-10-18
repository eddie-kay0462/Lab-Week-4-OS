#include "Job.h"

Job::Job(char i, int a, int c) : id(i), arrivalTime(a), cpuCycle(c), timeRemaining(c), completionTime(0), waitingTime(0), turnaroundTime(0), startTime(-1) {}