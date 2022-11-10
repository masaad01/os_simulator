#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stack>
#include "process.h"

using namespace std;

class Scheduler
{
    stack<Process*> readyProcessStack;

public:
    Scheduler();
    void addReadyProcess(Process &ps);
    pair<int, Process> dispatch(int currentTime);
    bool hasReadyProcess();
};

#endif // SCHEDULER_H
