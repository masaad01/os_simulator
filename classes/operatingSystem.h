#ifndef OPERATINGSYSTEM_H
#define OPERATINGSYSTEM_H

#include <string>
#include <list>

#include "process.h"
#include "scheduler.h"

using namespace std;

class OperatingSystem
{
    Scheduler *scheduler = nullptr;
    int *systemTimerPtr = nullptr;
    list<Process>  processHistory;

public:
    OperatingSystem(int &time, SchedulerType type = FIFO);
    ~OperatingSystem();
    bool fork(Process ps);
    pair<int, Process> run();
    Process getProcess(string name);
    bool hasReadyProcess();
    list<Process> getProcessHistory();
};

#endif // OPERATINGSYSTEM_H
