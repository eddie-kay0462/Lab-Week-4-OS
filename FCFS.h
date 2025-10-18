#ifndef FCFS_H
#define FCFS_H


#include "SchedulerBase.h"

class FCFS : public SchedulerBase{
    public:
        FCFS(const std::vector<Job>& j);
        std::vector<Job> schedule() override;
};


#endif