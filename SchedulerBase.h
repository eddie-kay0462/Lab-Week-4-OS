// base class for all schedulers

#ifndef SCHEDULERBASE_H
#define SCHEDULERBASE_H

#include <vector>
#include "Job.h"

class SchedulerBase{
    protected:
        std::vector<Job> jobs;

        void resetJobs();
        void calculateMetrics(std::vector<Job>& processedJobs);
    public:
        SchedulerBase(const std::vector<Job>& j);
        virtual ~SchedulerBase() {}
        virtual std::vector<Job> schedule() = 0;
};



#endif