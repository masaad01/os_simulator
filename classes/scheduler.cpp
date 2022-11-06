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
    Process* ps = readyProcessStack.top();
    readyProcessStack.pop();

    int endTime = ps->run(currentTime);
    return pair<int, Process>(endTime, *ps);
}
bool Scheduler::hasReadyProcess()
{
    return !readyProcessStack.empty();
}
