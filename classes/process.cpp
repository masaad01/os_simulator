#include <iostream>
#include <string>
#include <vector>

#include "process.h"

using namespace std;

int Process::pidCounter = 0;

Process::Process() {
    nullProcess = true;
}
Process::Process(string name, int arrivalTime, int processTime, int priority)
{
    set(name, arrivalTime, processTime, priority);
    pid = pidCounter++;
}

// setters
void Process::setName(string n)
{
    name = n;
}
void Process::setArrivalTime(int at)
{
    if (at >= 0)
        arrivalTime = at;
    else
        throw invalid_argument("processingTime must be > 0");
}
void Process::setProcessingTime(int pt)
{
    if (pt >= 0)
    {
        processingTime = pt;
        remainingTime = pt;
    }
    else
        throw invalid_argument("arrivalTime must be > 0");
}
void Process::setPriority(int p){
    priority = p;
}

void Process::set(string name, int arrivalTime, int processTime, int priority)
{
    setName(name);
    setArrivalTime(arrivalTime);
    setProcessingTime(processTime);
    setPriority(priority);
    nullProcess = false;
}

// property getters
string Process::getName()
{
    if(!isAdmitted()){
        throw invalid_argument("Process is not admitted");
    }
    return name;
}
int Process::getPid()
{
    if(!isAdmitted()){
        throw invalid_argument("Process is not admitted");
    }
    return pid;
}
int Process::getArrivalTime()
{
    if(!isAdmitted()){
        throw invalid_argument("Process not Admitted yet.");
    }
    return arrivalTime;
}
int Process::getProcessingTime()
{
    if(!isAdmitted()){
        throw invalid_argument("Process not Admitted yet.");
    }
    return processingTime;
}
int Process::getPriority(){
    if(!isAdmitted()){
        throw invalid_argument("Process not Admitted yet.");
    }
    return priority;
}
int Process::getFinishTime()
{
    if(!isFinished()){
        throw invalid_argument("Process not finished yet.");
    }
    return finishTime;
}
int Process::getResponseTime()
{
    if(!isAdmitted()){
        throw invalid_argument("Process not ready yet.");
    }
    return responseTime;
}
int Process::getRemainingTime()
{
    if(!isAdmitted()){
        throw invalid_argument("Process not ready yet.");
    }
    return remainingTime;
}

// returns actual endTime (if process finished before endTime)
int Process::run(int beginTime, int endTime)
{
    if(!isReady()){
        throw invalid_argument("Process not ready yet.");
    }
    // run to finish
    if (endTime == -1)
    {
        endTime = beginTime + processingTime;
    }
    if (beginTime < 0 || endTime < 0)
    {
        throw invalid_argument("time must be >= 0");
    }
    else if (endTime <= beginTime)
    {
        throw invalid_argument("endTime must be > beginTime");
    }
    
    // first run
    if (remainingTime == processingTime)
    {
        responseTime = beginTime - arrivalTime;
    }
    
    int runningTime = endTime - beginTime;
    // if process finished
    if (runningTime >= remainingTime)
    {
        finishTime = endTime - (runningTime - remainingTime);
        remainingTime = 0;
        return finishTime; // excess running time (not used)
    }
    remainingTime -= runningTime;
    return endTime;
}

// calculations
int Process::getTurnaroundTime()
{
    if(!isFinished()){
        throw invalid_argument("Process not finished yet.");
    }
    if (getFinishTime() != -1)
        return getFinishTime() - arrivalTime;
    return 0;
}
int Process::getDelayTime()
{
    if(!isFinished()){
        throw invalid_argument("Process not finished yet.");
    }
    return getTurnaroundTime() - processingTime;
}

// status checks
bool Process::isNullProcess(){
    return nullProcess;
}
bool Process::isAdmitted(){
    return name.length() > 0 && arrivalTime != -1 && processingTime != -1;
}
bool Process::isReady(){
        return isAdmitted() && remainingTime > 0;
}
bool Process::isFinished(){
    return isAdmitted() && remainingTime == 0;
}

string Process::getText()
{
    if(!isFinished()){
        throw invalid_argument("Process not finished yet.");
    }
    return name + ":(response=" + to_string(getResponseTime()) + ", turnaround=" + to_string(getTurnaroundTime()) + ", delay=" + to_string(getDelayTime()) + ")";
}

bool Process::compareArrivalTime(Process p1, Process p2){
    return p1.getArrivalTime() < p2.getArrivalTime();
}
bool Process::comparePriority(Process p1, Process p2){
    return p1.getPriority() < p2.getPriority();
}
bool Process::comparePid(Process p1, Process p2){
    return p1.pid < p2.pid;
}