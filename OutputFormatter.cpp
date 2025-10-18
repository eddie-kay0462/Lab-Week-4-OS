#include "OutputFormatter.h"
#include <iostream>
#include <iomanip>

using namespace std;

void OutputFormatter::printResults(const string& algorithm, const vector<Job>& result) {
    cout << "\n" << string(80, '=') << endl;
    cout << algorithm << " SCHEDULING" << endl;
    cout << string(80, '=') << endl;
    
    cout << left << setw(8) << "Job" 
         << setw(15) << "Arrival Time"
         << setw(15) << "CPU Cycle"
         << setw(18) << "Completion Time"
         << setw(18) << "Turnaround Time"
         << setw(15) << "Waiting Time" << endl;
    cout << string(80, '-') << endl;
    
    double totalWait = 0, totalTurnaround = 0;
    
    for (const auto& job : result) {
        cout << left << setw(8) << job.id
             << setw(15) << job.arrivalTime
             << setw(15) << job.cpuCycle
             << setw(18) << job.completionTime
             << setw(18) << job.turnaroundTime
             << setw(15) << job.waitingTime << endl;
        
        totalWait += job.waitingTime;
        totalTurnaround += job.turnaroundTime;
    }
    
    cout << string(80, '-') << endl;
    cout << fixed << setprecision(2);
    cout << "Average Waiting Time: " << totalWait / result.size() << " ms" << endl;
    cout << "Average Turnaround Time: " << totalTurnaround / result.size() << " ms" << endl;
}

void OutputFormatter::printComparisonTable(const vector<Job>& fcfs, const vector<Job>& sjn,
                                          const vector<Job>& srt, const vector<Job>& rr) {
    cout << "\n" << string(80, '=') << endl;
    cout << "COMPARISON TABLE - AVERAGE METRICS" << endl;
    cout << string(80, '=') << endl;
    
    auto calcAvg = [](const vector<Job>& jobs, bool isWait) {
        double sum = 0;
        for (const auto& j : jobs) {
            sum += isWait ? j.waitingTime : j.turnaroundTime;
        }
        return sum / jobs.size();
    };
    
    cout << left << setw(25) << "Algorithm"
         << setw(30) << "Average Waiting Time (ms)"
         << setw(25) << "Average Turnaround Time (ms)" << endl;
    cout << string(80, '-') << endl;
    
    cout << fixed << setprecision(2);
    cout << left << setw(25) << "FCFS"
         << setw(30) << calcAvg(fcfs, true)
         << setw(25) << calcAvg(fcfs, false) << endl;
    
    cout << left << setw(25) << "SJN"
         << setw(30) << calcAvg(sjn, true)
         << setw(25) << calcAvg(sjn, false) << endl;
    
    cout << left << setw(25) << "SRT"
         << setw(30) << calcAvg(srt, true)
         << setw(25) << calcAvg(srt, false) << endl;
    
    cout << left << setw(25) << "Round Robin (q=4ms)"
         << setw(30) << calcAvg(rr, true)
         << setw(25) << calcAvg(rr, false) << endl;
    
    cout << string(80, '=') << endl;
}