#include <iostream>
#include <string>
#include <vector>

#include "process.h"
#include "scheduler.h"

using namespace std;

// LifoScheduler
void LifoScheduler::addReadyProcess(Process &ps)
{
    readyProcessStack.push(&ps);
}
pair<int, Process> LifoScheduler::dispatch(int currentTime)
{
    if(readyProcessStack.empty()){
        return make_pair(currentTime, Process());
    }
    Process* ps = readyProcessStack.top();
    readyProcessStack.pop();

    int endTime = ps->run(currentTime);
    return make_pair(endTime, *ps);
}
bool LifoScheduler::hasReadyProcess()
{
    return !readyProcessStack.empty();
}

// FifoScheduler
void FifoScheduler::addReadyProcess(Process &ps)
{
    readyProcessQueue.push(&ps);
}
pair<int, Process> FifoScheduler::dispatch(int currentTime)
{
    if(readyProcessQueue.empty()){
        return make_pair(currentTime, Process());
    }
    Process* ps = readyProcessQueue.front();
    readyProcessQueue.pop();

    int endTime = ps->run(currentTime);
    return make_pair(endTime, *ps);
}
bool FifoScheduler::hasReadyProcess()
{
    return !readyProcessQueue.empty();
}

// SJFScheduler
void SJFScheduler::addReadyProcess(Process &ps)
{
    readyProcessQueue.push(&ps);
}
pair<int, Process> SJFScheduler::dispatch(int currentTime)
{
    if(readyProcessQueue.empty()){
        return make_pair(currentTime, Process());
    }
    Process* ps = readyProcessQueue.top();
    readyProcessQueue.pop();

    int endTime = ps->run(currentTime);
    return make_pair(endTime, *ps);
}
bool SJFScheduler::hasReadyProcess()
{
    return !readyProcessQueue.empty();
}

// SRTFScheduler
void SRTFScheduler::addReadyProcess(Process &ps)
{
    readyProcessQueue.push(&ps);
}
pair<int, Process> SRTFScheduler::dispatch(int currentTime)
{
    if(readyProcessQueue.empty()){
        return make_pair(currentTime, Process());
    }
    Process* ps = readyProcessQueue.top();
    readyProcessQueue.pop();

    int endTime = ps->run(currentTime, currentTime + 1);
    if(!ps->isFinished()){
        readyProcessQueue.push(ps);
    }
    return make_pair(endTime, *ps);
}
bool SRTFScheduler::hasReadyProcess()
{
    return !readyProcessQueue.empty();
}

// RR Scheduler
void RRScheduler::addReadyProcess(Process &ps)
{
    readyProcessQueue.push(&ps);
}
pair<int, Process> RRScheduler::dispatch(int currentTime)
{
    if(lastRunningProcess != nullptr){
        readyProcessQueue.push(lastRunningProcess);
    }
    if(readyProcessQueue.empty()){
        return make_pair(currentTime, Process());
    }
    Process* ps = readyProcessQueue.front();
    readyProcessQueue.pop();

    int endTime = ps->run(currentTime, currentTime + quantum);
    if(ps->isFinished()){
        lastRunningProcess = nullptr;
    }
    else{
        lastRunningProcess = ps;
    }
    return make_pair(endTime, *ps);
}
bool RRScheduler::hasReadyProcess()
{
    return !readyProcessQueue.empty() || lastRunningProcess != nullptr;
}

// createScheduler
Scheduler* createScheduler(SchedulerType type)
{
    if(type == LIFO)
        return new LifoScheduler();
    else if(type == FIFO)
        return new FifoScheduler();
    else if(type == SJF)
        return new SJFScheduler();
    else if(type == SRTF)
        return new SRTFScheduler();
    else if(type == RR)
        return new RRScheduler();
    else
        throw invalid_argument("Invalid scheduler type");
}

// getSchedulerType

string toUpper(string str)
{
    for(int i = 0; i < str.length(); i++){
        str[i] = toupper(str[i]);
    }
    return str;
}

SchedulerType getSchedulerType(string type)
{
    type = toUpper(type);
    if(type == "LIFO")
        return LIFO;
    else if(type == "FIFO")
        return FIFO;
    else if(type == "SJF")
        return SJF;
    else if(type == "SRTF")
        return SRTF;
    else if(type == "RR")
        return RR;
    else
        throw invalid_argument("Invalid scheduler type");
}

// valid scheduler types
string getValidSchedulerTypes()
{
    return "LIFO, FIFO, SJF, SRTF, RR";
}