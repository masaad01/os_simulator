#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

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


    sort(inputProcesses.begin(), inputProcesses.end(), Process::compareArrivalTime);
    
    time = inputProcesses[0].getArrivalTime();

    while(!inputProcesses.empty() || os.hasReadyProcess()){
        if(!inputProcesses.empty()){
            forkNewProcess();
        }
        else{
            time += 0;
        }
        if(!os.hasReadyProcess()){
            time++;
            continue;
        }
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
        int arrivalTime = ps.getArrivalTime();
        if(arrivalTime > 500)
            arrivalTime /= 100;
        string shift = drawRectangle(arrivalTime * unit, 3, ' ');
        string psRect = drawProcessRunning(ps, unit, true);
        string res = joinMultiLineString(shift, psRect);
        if(res.length() > 10000)
            cout << res.length() << endl << shift.length() << endl << psRect.length() << endl;
        fout << res;
    }
    fout << endl;

    string runningPS = drawRectangle(1, 3, '|');
    string timeline = "0";
    int time = 0;
    int prevTimeSeperator = 0;
    for(auto &ps : processesTimeline){
        vector<string> psRect;
        int runTime = ps.getProcessingTime() - ps.getRemainingTime();
        int runTimePadding = runTime * unit;

        // original timeline (before ps)
        psRect.push_back(runningPS);

        // shift to position (space padding)
        if(time < ps.getArrivalTime()){
            psRect.push_back(drawRectangle((ps.getArrivalTime() - time) * unit, 3, ' '));
            timeline += string((ps.getArrivalTime() - time) * unit, ' ');
            time = ps.getArrivalTime();
        }
        
        // draw start timeline seperator
        if(time != prevTimeSeperator){
            psRect.push_back(drawRectangle(1, 3, '|'));
            timeline += to_string(time);
            runTimePadding -= to_string(time).length() - 1;
        }

        // draw process running
        psRect.push_back(drawProcessRunning(ps, unit));
        time += runTime;
        runTimePadding -= to_string(time).length() - 1;
        timeline += string(runTimePadding, ' ');

        // draw end timeline seperator
        psRect.push_back(drawRectangle(1, 3, '|'));
        timeline += to_string(time);
        prevTimeSeperator = time;

        runningPS = joinMultiLineString(psRect);

        if(runningPS.length() > 2000){
            fout << runningPS;
            fout << timeline << endl;
            runningPS = "";
            timeline = "";
        }
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
    
    string name = ps.getName();
    double namePadding = (rt * size - name.length()) / 2.0;
    

    if(namePadding < 1){
        name = name[0] + string(rt * size - 2, '.') + name[name.length() - 1];
        namePadding = 0;
        addInfo = false;
    }
    else if(addInfo){
        double l = (at.length() + pt.length())/2.0;
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
    res += ps.getName();
    res += string(ceil(namePadding), ' ');
    res += addInfo? pt : "#";
    res += "\n";

    res += string(rt * size, '#');

    return res;
}

void Simulator::drawProcessTable(ofstream &fout){
    Table table;
    table.addColumnHeader("Name");
    table.addColumnHeader("Arrival");
    table.addColumnHeader("Processing");
    table.addColumnHeader("Remaining");
    table.addColumnHeader("Response");
    table.addColumnHeader("Turnaround");
    table.addColumnHeader("Delay");
    table.addColumnHeader("Start");
    table.addColumnHeader("Finish");

    long long totalResponse = 0;
    long long totalTurnaround = 0;
    long long totalDelay = 0;

    

    for(auto &ps : os.getProcessHistory()){
        vector<string> row;
        totalResponse += ps.getResponseTime();
        totalTurnaround += ps.getTurnaroundTime();
        totalDelay += ps.getDelayTime();
        row.push_back(ps.getName());
        row.push_back(to_string(ps.getArrivalTime()));
        row.push_back(to_string(ps.getProcessingTime()));
        row.push_back(to_string(ps.getRemainingTime()));
        row.push_back(to_string(ps.getResponseTime()));
        row.push_back(to_string(ps.getTurnaroundTime()));
        row.push_back(to_string(ps.getDelayTime()));
        row.push_back(to_string(ps.getArrivalTime() + ps.getResponseTime()));
        row.push_back(to_string(ps.getFinishTime()));
        table.addRow(row);
    }
    {
        vector<string> row;
        row.push_back("Total");
        row.push_back("");
        row.push_back("");
        row.push_back("");
        row.push_back(to_string(totalResponse));
        row.push_back(to_string(totalTurnaround));
        row.push_back(to_string(totalDelay));
        row.push_back("");
        row.push_back("");
        table.addRow(row);
    }
    {
        vector<string> row;
        row.push_back("Average");
        row.push_back("");
        row.push_back("");
        row.push_back("");
        string tmp = to_string((double)totalResponse / os.getProcessHistory().size());
        tmp = tmp.substr(0, tmp.find('.') + 3);
        row.push_back(tmp);
        tmp = to_string((double)totalTurnaround / os.getProcessHistory().size());
        tmp = tmp.substr(0, tmp.find('.') + 3);
        row.push_back(tmp);
        tmp = to_string((double)totalDelay / os.getProcessHistory().size());
        tmp = tmp.substr(0, tmp.find('.') + 3);
        row.push_back(tmp);
        row.push_back("");
        row.push_back("");
        table.addRow(row);
    }
    
    fout << table.printTable("|") << endl;
}
