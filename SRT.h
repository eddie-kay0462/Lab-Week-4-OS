#ifndef SRT_H
#define SRT_H

#include "SchedulerBase.h"

class SRT : public SchedulerBase {
public:
    SRT(const std::vector<Job>& j);
    std::vector<Job> schedule() override;
};

#endif