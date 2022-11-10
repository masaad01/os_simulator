#include <iostream>
#include <string>
#include <list>

#include "operatingSystem.h"

using namespace std;


OperatingSystem::OperatingSystem(int &time){
    scheduler = Scheduler();
    this->systemTimerPtr = &time;
    nullOS = false;
}
OperatingSystem::OperatingSystem(){
    nullOS = true;
}
bool OperatingSystem::fork(Process ps)
{
    if(nullOS){
        throw invalid_argument("OperatingSystem is not initialized");
    }
    try
    {
        processHistory.push_back(ps);
    }
    catch (int e)
    {
        return false;
    }
    scheduler.addReadyProcess(processHistory.back());

    return true;
}
pair<int, Process> OperatingSystem::run(){
    if(nullOS){
        throw invalid_argument("OperatingSystem is not initialized");
    }
    if(!hasReadyProcess()){
        return make_pair(*systemTimerPtr, Process());
    }
    return scheduler.dispatch(*systemTimerPtr);
}
Process OperatingSystem::getProcess(string pid){
    if(nullOS){
        throw invalid_argument("OperatingSystem is not initialized");
    }
    Process ps;
    for(auto &it : processHistory){
        if(it.getPid() == pid){
            ps = it;
            break;
        }
    }
    return ps;
}
bool OperatingSystem::hasReadyProcess(){
    if(nullOS){
        throw invalid_argument("OperatingSystem is not initialized");
    }
    return scheduler.hasReadyProcess();
}
list<Process> OperatingSystem::getProcessHistory(){
    if(nullOS){
        throw invalid_argument("OperatingSystem is not initialized");
    }
    return processHistory;
}
