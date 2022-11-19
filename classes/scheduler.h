#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stack>
#include <queue>
#include "process.h"

using namespace std;

enum SchedulerType{
    LIFO,
    FIFO
};

class Scheduler
{
public:
    virtual void addReadyProcess(Process &ps) = 0;
    virtual pair<int, Process> dispatch(int currentTime) = 0;
    virtual bool hasReadyProcess() = 0;
};

class LifoScheduler: public Scheduler
{
    stack<Process*> readyProcessStack;
public:
    void addReadyProcess(Process &ps);
    pair<int, Process> dispatch(int currentTime);
    bool hasReadyProcess();
};

class FifoScheduler: public Scheduler
{
    queue<Process*> readyProcessQueue;
public:
    void addReadyProcess(Process &ps);
    pair<int, Process> dispatch(int currentTime);
    bool hasReadyProcess();
};
#endif // SCHEDULER_H
