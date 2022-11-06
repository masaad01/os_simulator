#include <iostream>
#include <fstream>
#include <string>

#include "./classes/simulator.h"

using namespace std;


void randomProcessGenerator(ofstream &fout, int processCount, int maxArrivalTime, int maxProcessingTime){
    srand(time(NULL));
    fout << processCount << endl;
    for(int i = 0; i < processCount; i++){
        int arrivalTime = (rand() % maxArrivalTime) + 1;
        int processingTime = (rand() % maxProcessingTime) + 1;
        fout << char('A' + i) << " " << arrivalTime << " " << processingTime;
        if(i != processCount - 1)
            fout << endl;
    }

}

int main()
{
    int numOfProcesses = 0;
    Simulator simulator = Simulator();
    
    ofstream fout;
    
    {
        cout << "Do you want to generate random processes? (y/n): ";
        char c;
        cin >> c;
        if(c == 'y'){
            int processCount = 0;
            cout << "Enter number of processes: ";
            cin >> processCount;
            cout << "Enter max arrival time: ";
            int maxArrivalTime;
            cin >> maxArrivalTime;
            cout << "Enter max processing time: ";
            int maxProcessingTime;
            cin >> maxProcessingTime;
            fout.open("in.txt");
            randomProcessGenerator(fout, processCount, maxArrivalTime, maxProcessingTime);
            fout.close();
        }
    }

    // getting input
    ifstream fin;
    fin.open("in.txt");

    fin >> numOfProcesses;

    while (!fin.eof())
    {
        string pid = "";
        int aTime = 0, pTime = 0;
        fin >> pid >> aTime >> pTime;


        if(pid.length() > 0 && aTime >= 0 && pTime > 0){
            Process ps = Process(pid, aTime, pTime);
            simulator.addProcess(ps);
        }

    }

    fin.close();

    // running simulator
    simulator.run();

    // writing output
    string briefOutput = "";
    string output = "";

    for( auto &it : simulator.getProcessesTimeline()){
        briefOutput += it.getPid();
        output += it.getText() + "\n";
    }


    // ofstream fout;

    fout.open("out.txt");
    fout << briefOutput << endl;
    fout << output;
    fout.close();

    
    fout.open("timeline.txt");
    simulator.drawTimeLine(fout);
    fout.close();


    fout.open("table.txt");
    simulator.drawProcessTable(fout);
    fout.close();


    return 0;
}


