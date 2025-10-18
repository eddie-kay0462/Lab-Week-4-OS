#ifndef SJN_H
#define SJN_H


#include "SchedulerBase.h"


class SJN : public SchedulerBase{
    public:
        SJN(const std::vector<Job>& j);
        std::vector<Job> schedule() override;

};

#endif