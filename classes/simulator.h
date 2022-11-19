#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <vector>

#include "table.h"
#include "operatingSystem.h"
#include "process.h"

using namespace std;

class Simulator{
    OperatingSystem os;
    vector<Process> inputProcesses;
    vector<Process> processesTimeline;
    int time = 0;
public:
    Simulator() : os(time){};
    void addProcess(Process ps);
    void forkNewProcess();
    void run();
    vector<Process> getProcessesTimeline();
    void drawTimeLine(ofstream &fout);
    string drawProcessRunning(Process ps, int size = 3, bool addInfo = false);
    void drawProcessTable(ofstream &fout);
};

#endif // SIMULATOR_H
