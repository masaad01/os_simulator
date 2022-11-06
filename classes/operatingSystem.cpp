#include <string>
#include <list>

#include "operatingSystem.h"

using namespace std;


OperatingSystem::OperatingSystem(int time){
    scheduler = Scheduler();
    this->time = time;
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
    scheduler.addReadyProcess(processHistory.back());

    return true;
}
pair<int, Process> OperatingSystem::run(){
    auto res = scheduler.dispatch(time);
    time = res.first;
    return res;
}
Process OperatingSystem::getProcess(string pid){
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
    return scheduler.hasReadyProcess();
}
void OperatingSystem::setTimer(int time){
    this->time = time;
}
list<Process> OperatingSystem::getProcessHistory(){
    return processHistory;
}
