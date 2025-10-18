#include <iostream>
#include <vector>
#include "Job.h"
#include "FCFS.h"
#include "SJN.h"
#include "SRT.h"
#include "RoundRobin.h"
#include "OutputFormatter.h"

using namespace std;

int main() {
    // Test data from the lab document
    vector<Job> jobs = {
        Job('A', 0, 16),
        Job('B', 3, 2),
        Job('C', 5, 11),
        Job('D', 9, 6),
        Job('E', 10, 1),
        Job('F', 12, 9),
        Job('G', 14, 4),
        Job('H', 16, 14),
        Job('I', 17, 1),
        Job('J', 19, 8)
    };
    
    cout << "\n";
    cout << "========================================================" << endl;
    cout << "   CPU SCHEDULING ALGORITHMS SIMULATOR" << endl;
    cout << "   CS433 Operating Systems - Task 3" << endl;
    cout << "   Time Quantum for Round Robin: 4 ms" << endl;
    cout << "   Context Switching Time: 0 ms" << endl;
    cout << "========================================================" << endl;
    
    // Create scheduler instances
    FCFS fcfsScheduler(jobs);
    SJN sjnScheduler(jobs);
    SRT srtScheduler(jobs);
    RoundRobin rrScheduler(jobs, 4);
    
    // Run all algorithms
    vector<Job> fcfsResult = fcfsScheduler.schedule();
    vector<Job> sjnResult = sjnScheduler.schedule();
    vector<Job> srtResult = srtScheduler.schedule();
    vector<Job> rrResult = rrScheduler.schedule();
    
    // Print individual results
    OutputFormatter::printResults("FIRST COME FIRST SERVED (FCFS)", fcfsResult);
    OutputFormatter::printResults("SHORTEST JOB NEXT (SJN)", sjnResult);
    OutputFormatter::printResults("SHORTEST REMAINING TIME (SRT)", srtResult);
    OutputFormatter::printResults("ROUND ROBIN (Time Quantum = 4 ms)", rrResult);
    
    // Print comparison table
    OutputFormatter::printComparisonTable(fcfsResult, sjnResult, srtResult, rrResult);
    
    return 0;
}