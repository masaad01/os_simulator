#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

#include "simulator.h"

using namespace std;


string joinMultiLineString(vector<string> arr){
    string res = "";
    vector<vector<string>> blocks;
    for(auto &str : arr){
        vector<string> lines;
        int pos = 0;
        while(pos < str.length()){
            int nextPos = str.find('\n', pos);
            if(nextPos == string::npos){
                nextPos = str.length();
            }
            lines.push_back(str.substr(pos, nextPos - pos));
            pos = nextPos + 1;
        }
        blocks.push_back(lines);
    }
    int maxLine = 0;
    for(auto &block : blocks){
        maxLine = max(maxLine, (int)block.size());
    }
    for(int i = 0; i < maxLine; i++){
        for(auto &block : blocks){
            if(i < block.size()){
                res += block[i];
            }
        }
        res += "\n";
    }
    return res;
}

string joinMultiLineString(string a, string b){
    vector<string> arr;
    arr.push_back(a);
    arr.push_back(b);
    return joinMultiLineString(arr);
}

string drawRectangle(int width, int height, char symbol = '#'){
    string res = "";
    for(int i = 0; i < height; i++){
        res += string(width, symbol) + "\n";
    }
    return res;
}


Simulator::Simulator(){
    os = OperatingSystem(time);
}
void Simulator::addProcess(Process ps){
    inputProcesses.push_back(ps);
}
void Simulator::forkNewProcess(){
    for(int i = 0; i < inputProcesses.size(); i++){
        if(inputProcesses[i].getArrivalTime() <= time){
            os.fork(inputProcesses[i]);
            inputProcesses.erase(inputProcesses.begin() + i);
            i--;
        }
    }
}
void Simulator::run(){


    Process::sortByArrivaltime(inputProcesses);
    
    os.setTimer(inputProcesses[0].getArrivalTime());
    time = inputProcesses[0].getArrivalTime();

    while(!inputProcesses.empty() || os.hasReadyProcess()){
        forkNewProcess();
        pair<int, Process> res = os.run();
        time = res.first;
        Process ps = res.second;
        processesTimeline.push_back(ps);
    }
}
vector<Process> Simulator::getProcessesTimeline(){
    return processesTimeline;
}

void Simulator::drawTimeLine(ofstream &fout){
    int unit = 5;

    for(auto &ps : os.getProcessHistory()){
        string shift = drawRectangle(ps.getArrivalTime() * unit, 3, ' ');
        string psRect = drawProcessRunning(ps, unit, true);
        fout << joinMultiLineString(shift, psRect);
    }
    fout << endl;

    vector<string> startMark;
    startMark.push_back(drawRectangle(1, 3, ' '));
    startMark.push_back(drawRectangle(1, 3, '|'));
    startMark.push_back(drawRectangle(1, 3, ' '));

    string runningPS = joinMultiLineString(startMark);
    string timeline = " 0 ";
    int time = 0;
    for(auto &ps : processesTimeline){
        vector<string> psRect;
        psRect.push_back(runningPS);
        if(time < ps.getArrivalTime()){
            psRect.push_back(drawRectangle((ps.getArrivalTime() - time) * unit, 3, ' '));
            timeline += string((ps.getArrivalTime() - time) * unit, ' ');
            time = ps.getArrivalTime();
        }

        psRect.push_back(drawProcessRunning(ps, unit));
        psRect.push_back(drawRectangle(1, 3, ' '));
        psRect.push_back(drawRectangle(1, 3, '|'));
        psRect.push_back(drawRectangle(1, 3, ' '));

        runningPS = joinMultiLineString(psRect);


        int runTime = ps.getProcessingTime() - ps.getRemainingTime();

        time += runTime;

        string timeStr = "";
        timeStr += (time < 100)? " ": "";
        timeStr += to_string(time);
        timeStr += (time < 10)? " ": "";

        timeline += string(runTime * unit, ' ') + timeStr;
        
    }
    fout << runningPS;
    fout << timeline;
}

string Simulator::drawProcessRunning(Process ps, int size, bool addInfo){
    string res = "";

    int rt = ps.getProcessingTime() - ps.getRemainingTime();
    string at = "a:" + to_string(ps.getArrivalTime());
    string pt = "p:" + to_string(ps.getProcessingTime());

    res += string(rt * size, '#');
    res += "\n";
    
    string name = ps.getPid();
    double namePadding = (rt * size - name.length()) / 2.0;
    

    if(namePadding < 0){
        name = name.substr(0, rt * size);
        namePadding = 0;
        addInfo = false;
    }
    else if(addInfo){
        int l = (at.length() + pt.length())/2.0;
        if(l >= namePadding){
            namePadding -= 1;
            addInfo = false;
        }
        else{
            namePadding -= l;
        }
    }
    else
        namePadding -= 1;

    res += addInfo? at : "#";
    res += string(floor(namePadding), ' ');
    res += ps.getPid();
    res += string(ceil(namePadding), ' ');
    res += addInfo? pt : "#";
    res += "\n";

    res += string(rt * size, '#');

    return res;
}

void Simulator::drawProcessTable(ofstream &fout){
    Table table;
    table.addColumnHeader("PID");
    table.addColumnHeader("Arrival");
    table.addColumnHeader("Processing");
    table.addColumnHeader("Remaining");
    table.addColumnHeader("Response");
    table.addColumnHeader("Turnaround");
    table.addColumnHeader("Delay");

    for(auto &ps : os.getProcessHistory()){
        vector<string> row;
        row.push_back(ps.getPid());
        row.push_back(to_string(ps.getArrivalTime()));
        row.push_back(to_string(ps.getProcessingTime()));
        row.push_back(to_string(ps.getRemainingTime()));
        row.push_back(to_string(ps.getResponseTime()));
        row.push_back(to_string(ps.getTurnaroundTime()));
        row.push_back(to_string(ps.getDelayTime()));
        table.addRow(row);
    }
    fout << table.printTable("|") << endl;
}
