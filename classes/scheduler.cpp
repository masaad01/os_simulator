#include <string>
#include <vector>

#include "process.h"
#include "scheduler.h"

using namespace std;


Scheduler::Scheduler(){

}
void Scheduler::addReadyProcess(Process &ps)
{
    readyProcessStack.push(&ps);
}
pair<int, Process> Scheduler::dispatch(int currentTime)
{
    if(readyProcessStack.empty()){
        return make_pair(currentTime, Process());
    }
    Process* ps = readyProcessStack.top();
    readyProcessStack.pop();

    int endTime = ps->run(currentTime);
    return make_pair(endTime, *ps);
}
bool Scheduler::hasReadyProcess()
{
    return !readyProcessStack.empty();
}
