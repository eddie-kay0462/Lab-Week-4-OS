#ifndef ROUND_ROBIN_H
#define ROUND_ROBIN_H

#include "SchedulerBase.h"

class RoundRobin : public SchedulerBase {
private:
    int quantum;
    
public:
    RoundRobin(const std::vector<Job>& j, int q);
    std::vector<Job> schedule() override;
};

#endif