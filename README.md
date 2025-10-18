# CPU Scheduling Algorithms Simulator

A C++ implementation of various CPU scheduling algorithms for Operating Systems coursework.

## Overview

This project simulates and compares four different CPU scheduling algorithms:
- **FCFS (First Come First Served)**
- **SJN (Shortest Job Next)**
- **SRT (Shortest Remaining Time)**
- **Round Robin (Time Quantum = 4ms)**

## Features

- Implements four classic CPU scheduling algorithms
- Calculates and displays completion time, turnaround time, and waiting time for each job
- Provides detailed results for each algorithm
- Includes a comparison table showing average metrics across all algorithms
- Clean, formatted output with professional presentation

## Test Data

The simulator uses the following test data:
- Job A: Arrival Time = 0ms, CPU Cycle = 16ms
- Job B: Arrival Time = 3ms, CPU Cycle = 2ms
- Job C: Arrival Time = 5ms, CPU Cycle = 11ms
- Job D: Arrival Time = 9ms, CPU Cycle = 6ms
- Job E: Arrival Time = 10ms, CPU Cycle = 1ms
- Job F: Arrival Time = 12ms, CPU Cycle = 9ms
- Job G: Arrival Time = 14ms, CPU Cycle = 4ms
- Job H: Arrival Time = 16ms, CPU Cycle = 14ms
- Job I: Arrival Time = 17ms, CPU Cycle = 1ms
- Job J: Arrival Time = 19ms, CPU Cycle = 8ms

## Compilation

To compile the project, use the following command:

```bash
g++ -o scheduler main.cpp Job.cpp FCFS.cpp SJN.cpp SRT.cpp RoundRobin.cpp OutputFormatter.cpp SchedulerBase.cpp
```

## Running the Program

After compilation, run the executable:

```bash
./scheduler.exe
```

## Output

The program will display:
1. Individual results for each scheduling algorithm
2. Detailed metrics for each job (completion time, turnaround time, waiting time)
3. Average waiting time and turnaround time for each algorithm
4. A comparison table showing average metrics across all algorithms

## Project Structure

- `main.cpp` - Main program entry point
- `Job.h/cpp` - Job class definition and implementation
- `SchedulerBase.h/cpp` - Base scheduler class
- `FCFS.h/cpp` - First Come First Served implementation
- `SJN.h/cpp` - Shortest Job Next implementation
- `SRT.h/cpp` - Shortest Remaining Time implementation
- `RoundRobin.h/cpp` - Round Robin implementation
- `OutputFormatter.h/cpp` - Output formatting utilities

## Course Information

- **Course**: CS433 Operating Systems
- **Task**: Task 3 - CPU Scheduling Algorithms
- **Time Quantum**: 4ms (for Round Robin)
- **Context Switching Time**: 0ms

## Requirements

- C++ compiler with C++11 support or later
- Standard C++ libraries
