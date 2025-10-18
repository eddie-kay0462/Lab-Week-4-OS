// common functionality for all schedulers

#include "SchedulerBase.h"

SchedulerBase::SchedulerBase(const std::vector<Job>& j) : jobs(j) {}

void SchedulerBase::resetJobs() {
    for (auto& job : jobs) {
        job.timeRemaining = job.cpuCycle;
        job.completionTime = 0;
        job.waitingTime = 0;
        job.turnaroundTime = 0;
        job.startTime = -1;
    }
}

void SchedulerBase::calculateMetrics(std::vector<Job>& processedJobs) {
    for (auto& job : processedJobs) {
        job.turnaroundTime = job.completionTime - job.arrivalTime;
        job.waitingTime = job.turnaroundTime - job.cpuCycle;
    }
}