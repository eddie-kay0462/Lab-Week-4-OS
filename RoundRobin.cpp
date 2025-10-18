#include "RoundRobin.h"
#include <algorithm>
#include <queue>

RoundRobin::RoundRobin(const std::vector<Job>& j, int q) 
    : SchedulerBase(j), quantum(q) {}

std::vector<Job> RoundRobin::schedule() {
    resetJobs();
    std::vector<Job> result = jobs;
    std::queue<int> readyQueue;
    std::vector<bool> inQueue(jobs.size(), false);
    
    int currentTime = 0;
    int completedCount = 0;
    int n = jobs.size();
    
    // Sort by arrival time for initial processing
    std::sort(result.begin(), result.end(),
         [](const Job& a, const Job& b) { return a.arrivalTime < b.arrivalTime; });
    
    // Add first arrived job
    int nextArrival = 0;
    if (result[0].arrivalTime <= currentTime) {
        readyQueue.push(0);
        inQueue[0] = true;
        nextArrival = 1;
    } else {
        currentTime = result[0].arrivalTime;
        readyQueue.push(0);
        inQueue[0] = true;
        nextArrival = 1;
    }
    
    while (completedCount < n) {
        if (readyQueue.empty()) {
            // Jump to next arrival
            currentTime = result[nextArrival].arrivalTime;
            readyQueue.push(nextArrival);
            inQueue[nextArrival] = true;
            nextArrival++;
        }
        
        int idx = readyQueue.front();
        readyQueue.pop();
        
        if (result[idx].startTime == -1) {
            result[idx].startTime = currentTime;
        }
        
        // Execute for quantum or remaining time
        int execTime = std::min(quantum, result[idx].timeRemaining);
        result[idx].timeRemaining -= execTime;
        currentTime += execTime;
        
        // Add newly arrived jobs to queue
        while (nextArrival < n && result[nextArrival].arrivalTime <= currentTime) {
            if (!inQueue[nextArrival]) {
                readyQueue.push(nextArrival);
                inQueue[nextArrival] = true;
            }
            nextArrival++;
        }
        
        // Check if job completed
        if (result[idx].timeRemaining == 0) {
            result[idx].completionTime = currentTime;
            completedCount++;
        } else {
            // Job not finished, add back to queue
            readyQueue.push(idx);
        }
    }
    
    calculateMetrics(result);
    return result;
}
