#include <iostream>
#include <string>
#include <list>

#include "operatingSystem.h"

using namespace std;


OperatingSystem::OperatingSystem(int &time, SchedulerType type){
    systemTimerPtr = &time;
    if(type == LIFO)
        scheduler = new LifoScheduler();
    else if(type == FIFO)
        scheduler = new FifoScheduler();
    else
        throw exception("Invalid scheduler type");
}
OperatingSystem::~OperatingSystem(){
    delete scheduler;
    scheduler = nullptr;
}
bool OperatingSystem::fork(Process ps)
{
    try
    {
        processHistory.push_back(ps);
    }
    catch (int e)
    {
        return false;
    }
    scheduler->addReadyProcess(processHistory.back());

    return true;
}
pair<int, Process> OperatingSystem::run(){
    if(!hasReadyProcess()){
        return make_pair(*systemTimerPtr, Process());
    }
    return scheduler->dispatch(*systemTimerPtr);
}
Process OperatingSystem::getProcess(string name){
    Process ps;
    for(auto &it : processHistory){
        if(it.getName() == name){
            ps = it;
            break;
        }
    }
    return ps;
}
bool OperatingSystem::hasReadyProcess(){
    return scheduler->hasReadyProcess();
}
list<Process> OperatingSystem::getProcessHistory(){
    return processHistory;
}
