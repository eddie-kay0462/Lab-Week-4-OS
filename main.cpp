#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include "Job.h"
#include "FCFS.h"
#include "SJN.h"
#include "SRT.h"
#include "RoundRobin.h"
#include "OutputFormatter.h"

using namespace std;

struct AlgorithmStats {
    string name;
    double avgWaitingTime;
    double avgTurnaroundTime;
};

double calculateAverageWaitingTime(const vector<Job>& jobs) {
    double total = 0;
    for (const auto& job : jobs) total += job.waitingTime;
    return total / jobs.size();
}

double calculateAverageTurnaroundTime(const vector<Job>& jobs) {
    double total = 0;
    for (const auto& job : jobs) total += job.turnaroundTime;
    return total / jobs.size();
}

void printRankingTable(const vector<AlgorithmStats>& stats, const string& metric) {
    cout << string(90, '_') << endl;
    cout << "   RANKING BY " << metric << endl;
    cout << string(90, '_') << endl;
    cout << left << setw(5) << "Rank" << setw(25) << "Algorithm" << setw(20) << metric << endl;
    cout << string(90, '_') << endl;

    int rank = 1;
    for (const auto& s : stats) {
        cout << left << setw(5) << rank++ 
             << setw(25) << s.name 
             << setw(20) << fixed << setprecision(2) 
             << (metric == "Waiting Time" ? s.avgWaitingTime : s.avgTurnaroundTime)
             << endl;
    }
}

int main() {
    //jobs to be scheduled
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
    cout << string(90, '_') << endl;
    cout << "   CPU SCHEDULING ALGORITHMS SIMULATOR" << endl;
    cout << "   CS433 Operating Systems - Task 3" << endl;
    cout << "   Time Quantum for Round Robin: 4 ms" << endl;
    cout << "   Context Switching Time: 0 ms" << endl;
    cout << string(90, '_') << endl;

    //Instantiate schedulers
    FCFS fcfsScheduler(jobs);
    SJN sjnScheduler(jobs);
    SRT srtScheduler(jobs);
    RoundRobin rrScheduler(jobs, 4);

    //running all algorithms before the user chooses so the data is readily available 
    vector<Job> fcfsResult = fcfsScheduler.schedule();
    vector<Job> sjnResult = sjnScheduler.schedule();
    vector<Job> srtResult = srtScheduler.schedule();
    vector<Job> rrResult = rrScheduler.schedule();

    //storing the waiting and Turnaround times for comparison 
    vector<AlgorithmStats> stats = {
        {"FIRST COME FIRST SERVED (FCFS)", calculateAverageWaitingTime(fcfsResult), calculateAverageTurnaroundTime(fcfsResult)},
        {"SHORTEST JOB NEXT (SJN)", calculateAverageWaitingTime(sjnResult), calculateAverageTurnaroundTime(sjnResult)},
        {"SHORTEST REMAINING TIME (SRT)", calculateAverageWaitingTime(srtResult), calculateAverageTurnaroundTime(srtResult)},
        {"ROUND ROBIN (Quantum = 4ms)", calculateAverageWaitingTime(rrResult), calculateAverageTurnaroundTime(rrResult)}
    };

    //menu to pick which algorithm they want to use 
    cout << "\nSelect which algorithm you want to view:\n";
    cout << "1. FCFS\n2. SJN\n3. SRT\n4. Round Robin\n";
    cout << "Enter your choice (1-4): ";
    int choice;
    cin >> choice;

    vector<Job> selectedResult;
    string selectedName;

    switch (choice) {
        case 1:
            selectedResult = fcfsResult;
            selectedName = "FIRST COME FIRST SERVED (FCFS)";
            break;
        case 2:
            selectedResult = sjnResult;
            selectedName = "SHORTEST JOB NEXT (SJN)";
            break;
        case 3:
            selectedResult = srtResult;
            selectedName = "SHORTEST REMAINING TIME (SRT)";
            break;
        case 4:
            selectedResult = rrResult;
            selectedName = "ROUND ROBIN (Quantum = 4ms)";
            break;
        default:
            cout << "Invalid choice!" << endl;
            return 0;
    }

    //printing  the chosen algorithm's results
    OutputFormatter::printResults(selectedName, selectedResult);

    double avgWait = calculateAverageWaitingTime(selectedResult);
    double avgTurn = calculateAverageTurnaroundTime(selectedResult);

    cout << "\nAverage Waiting Time for " << selectedName << ": " << avgWait << " ms" << endl;
    cout << "Average Turnaround Time for " << selectedName << ": " << avgTurn << " ms" << endl;

    //sorting the  ranking by waiting time
    vector<AlgorithmStats> waitingRank = stats;
    sort(waitingRank.begin(), waitingRank.end(),
         [](const AlgorithmStats& a, const AlgorithmStats& b) {
             return a.avgWaitingTime < b.avgWaitingTime;
         });

    //sorting the  ranking by turnaround time
    vector<AlgorithmStats> turnaroundRank = stats;
    sort(turnaroundRank.begin(), turnaroundRank.end(),
         [](const AlgorithmStats& a, const AlgorithmStats& b) {
             return a.avgTurnaroundTime < b.avgTurnaroundTime;
         });

    //finding the rankings of the selected algorithm
    int waitingRankPos = 0, turnaroundRankPos = 0;
    for (int i = 0; i < waitingRank.size(); ++i) {
        //checking the raking in the the waitingRank
        if (waitingRank[i].name == selectedName) 
        {
            waitingRankPos = i + 1;
        }
        //checking the raking in the the turnaroundRank
        if (turnaroundRank[i].name == selectedName){
            turnaroundRankPos = i + 1;
        }
    }

    cout << "\nRanking for " << selectedName << ":\n";
    cout << " - Waiting Time Rank: " << waitingRankPos << " / " << waitingRank.size() << endl;
    cout << " - Turnaround Time Rank: " << turnaroundRankPos << " / " << turnaroundRank.size() << endl;

    cout << "\nWould you like to see the ranking tables? (y/n): ";
    char viewRank;
    cin >> viewRank;
    if (viewRank == 'y' || viewRank == 'Y') {
        printRankingTable(waitingRank, "Waiting Time");
        printRankingTable(turnaroundRank, "Turnaround Time");
    }

    cout << "\nGoodbye!" << endl;
    cout << string(90, '_') << endl;

    return 0;
}
