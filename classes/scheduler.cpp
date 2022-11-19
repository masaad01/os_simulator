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