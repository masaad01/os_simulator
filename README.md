# os_simulator

input a group of processes and show order of execution using LIFO scheduler algorithm (algorithm may be changed)
    
## Usage:
Compile file using command (g++ main.cpp ./classes/*.cpp -o main.exe) then run file.

You may input processes manually in (in.txt) in the format(see next section),
or choose to generate random processes.


## Input file format (in.txt):
{number of processes}
{name 1} {arrival time 1} {processing time 1}
{name 2} {arrival time 2} {processing time 2}
.
.
.
{name N} {arrival time N} {processing time N}

## output files:
1) out.txt:
{order of execution}
{name}:(response time, turnaround time, delay time)

2) table.txt:
a table of all stats of processes

3) timeline.txt:
this has 2 sections:
* Visual representations of the arrival/processing time of each process seperatly
* A time line representing the order of execution for all processes (as dectated by the scheduling algorithm)
