#ifndef OPERATINGSYSTEM_H
#define OPERATINGSYSTEM_H

#include <string>
#include <list>

#include "process.h"
#include "scheduler.h"

using namespace std;

class OperatingSystem
{
    Scheduler scheduler;
    int *systemTimerPtr = nullptr;
    list<Process>  processHistory;
    bool nullOS = true;

public:
    OperatingSystem(int &time);
    OperatingSystem();
    bool fork(Process ps);
    pair<int, Process> run();
    Process getProcess(string pid);
    bool hasReadyProcess();
    list<Process> getProcessHistory();
};

#endif // OPERATINGSYSTEM_H
