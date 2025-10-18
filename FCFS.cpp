#include "FCFS.h"
#include <algorithm>

FCFS::FCFS(const std::vector<Job>& j) : SchedulerBase(j) {}

std::vector<Job> FCFS::schedule() {
    resetJobs();
    std::vector<Job> result = jobs;
    std::sort(result.begin(), result.end(), [](const Job& a, const Job& b) {
        return a.arrivalTime < b.arrivalTime; });

    int currTime = 0;
    for (auto& job : result) {
        if (currTime < job.arrivalTime) {
            currTime = job.arrivalTime;
        }
        job.startTime = currTime;
        currTime += job.cpuCycle;
        job.completionTime = currTime;
    }
    calculateMetrics(result);
    return result;
}