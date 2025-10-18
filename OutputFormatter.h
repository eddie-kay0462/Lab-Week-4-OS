#ifndef OUTPUT_FORMATTER_H
#define OUTPUT_FORMATTER_H

#include <vector>
#include <string>
#include "Job.h"

class OutputFormatter {
public:
    static void printResults(const std::string& algorithm, const std::vector<Job>& result);
    static void printComparisonTable(const std::vector<Job>& fcfs, const std::vector<Job>& sjn,
                                   const std::vector<Job>& srt, const std::vector<Job>& rr);
};

#endif