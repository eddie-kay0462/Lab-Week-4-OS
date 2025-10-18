#include "SJN.h"
#include <algorithm>


SJN::SJN(const std::vector<Job>& j) : SchedulerBase(j) {}

std::vector<Job> SJN::schedule() {
    resetJobs();
    std::vector<Job> result;
    std::vector<Job> ready;
    std::vector<Job> remaining = jobs;

    int currTime = 0;
    while (!remaining.empty() || !ready.empty()) {
        //add jobs to ready queue if they have arrived
        auto it = remaining.begin();

        while (it != remaining.end()){
            if (it->arrivalTime <= currTime) {
                ready.push_back(*it);
                it = remaining.erase(it);
            } else {
                ++it;
            }
        }

        if (ready.empty()) {
            //no ready jobs, wait for next arrival
            currTime = remaining[0].arrivalTime;
            continue;
        }

        //select the job with the shortest CPU cycle
        auto shortest = std::min_element(ready.begin(), ready.end(), [](const Job& a, const Job& b) {
            return a.cpuCycle < b.cpuCycle; });

            Job current = *shortest;
            ready.erase(shortest);

            current.startTime = currTime;
            currTime += current.cpuCycle;
            current.completionTime = currTime;
            result.push_back(current);
        }

        calculateMetrics(result);
        return result;
}