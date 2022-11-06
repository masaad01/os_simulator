#include <string>
#include <list>

#include "process.h"
#include "scheduler.h"

using namespace std;


class OperatingSystem
{
    Scheduler scheduler;
    int time = 0;
    list<Process>  processHistory;

public:
    OperatingSystem(int time = 0);
    bool fork(Process ps);
    pair<int, Process> run();
    Process getProcess(string pid);
    bool hasReadyProcess();
    void setTimer(int time);
    list<Process> getProcessHistory();
};

