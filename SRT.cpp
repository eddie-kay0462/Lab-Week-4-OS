#include "SRT.h"
#include <climits>

SRT::SRT(const std::vector<Job>& j) : SchedulerBase(j) {}

std::vector<Job> SRT::schedule() {
    resetJobs();
    std::vector<Job> result = jobs;
    std::vector<bool> completed(jobs.size(), false);
    
    int currentTime = 0;
    int completedCount = 0;
    int n = jobs.size();
    
    while (completedCount < n) {
        int shortest = -1;
        int minRemaining = INT_MAX;
        
        // Find job with shortest remaining time
        for (int i = 0; i < n; i++) {
            if (result[i].arrivalTime <= currentTime && !completed[i]) {
                if (result[i].timeRemaining < minRemaining) {
                    minRemaining = result[i].timeRemaining;
                    shortest = i;
                }
            }
        }
        
        if (shortest == -1) {
            // No job available, advance time
            currentTime++;
            continue;
        }
        
        // Execute job for 1 time unit
        if (result[shortest].startTime == -1) {
            result[shortest].startTime = currentTime;
        }
        
        result[shortest].timeRemaining--;
        currentTime++;
        
        // Check if job completed
        if (result[shortest].timeRemaining == 0) {
            result[shortest].completionTime = currentTime;
            completed[shortest] = true;
            completedCount++;
        }
    }
    
    calculateMetrics(result);
    return result;
}
