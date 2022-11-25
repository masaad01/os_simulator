#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stack>
#include <queue>
#include "process.h"

using namespace std;

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

class SJFScheduler: public Scheduler
{
    class Compare{
    public:
        bool operator()(Process* ps1, Process* ps2){
            return ps1->getProcessingTime() > ps2->getProcessingTime();
        }
    };
    priority_queue<Process*, vector<Process*>, Compare> readyProcessQueue;
public:
    void addReadyProcess(Process &ps);
    pair<int, Process> dispatch(int currentTime);
    bool hasReadyProcess();

};

class SRTFScheduler: public Scheduler
{
    class Compare{
    public:
        bool operator()(Process* ps1, Process* ps2){
            if(ps1->getRemainingTime() == ps2->getRemainingTime()){
                return ps1->getPid() > ps2->getPid();
            }
            return ps1->getRemainingTime() > ps2->getRemainingTime();
        }
    };
    priority_queue<Process*, vector<Process*>, Compare> readyProcessQueue;
public:
    void addReadyProcess(Process &ps);
    pair<int, Process> dispatch(int currentTime);
    bool hasReadyProcess();
};

class RRScheduler: public Scheduler
{
    queue<Process*> readyProcessQueue;
    int quantum;
    Process* lastRunningProcess;
public:
    RRScheduler(int quantum = 1): quantum(quantum), lastRunningProcess(nullptr){}
    void setQuantum(int quantum){this->quantum = quantum;}
    int getQuantum(){return quantum;}
    void addReadyProcess(Process &ps);
    pair<int, Process> dispatch(int currentTime);
    bool hasReadyProcess();
};


enum SchedulerType{
    LIFO,
    FIFO,
    SJF,
    SRTF,
    RR
};

Scheduler* createScheduler(SchedulerType type);
SchedulerType getSchedulerType(string type);
string getValidSchedulerTypes();

#endif // SCHEDULER_H