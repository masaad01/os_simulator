#ifndef PROCESS_H
#define PROCESS_H

#include <vector>
#include <string>

using namespace std;

class Process
{
    static int pidCounter;
    
    int pid = -1;
    string name = "";
    int arrivalTime = -1;
    int processingTime = -1;
    int priority = -1;

    int remainingTime = -1;
    int finishTime = -1;
    int responseTime = -1;

    bool nullProcess = true;

    // setters
    void setName(string n);
    void setArrivalTime(int at);
    void setProcessingTime(int pt);
    void setPriority(int p);

public:
    Process();
    Process(string name, int arrivalTime, int processTime, int priority = 0);
    void set(string name, int arrivalTime, int processTime, int priority = 0);
    // property getters
    string getName();
    int getArrivalTime();
    int getProcessingTime();
    int getPriority();
    int getFinishTime();
    int getResponseTime();
    int getRemainingTime();
    // returns actual endTime (if process finished before endTime)
    int run(int beginTime, int endTime = -1);

    // calculations
    int getTurnaroundTime();
    int getDelayTime();

    bool isNullProcess();
    bool isAdmitted();
    bool isReady();
    bool isFinished();

    string getText();

    static bool compareArrivalTime(Process p1, Process p2);
    static bool comparePriority(Process p1, Process p2);
    static bool comparePid(Process p1, Process p2);
};

#endif // PROCESS_H
