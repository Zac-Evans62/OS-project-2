##Compilation: 
g++ main.cpp bankers.cpp -o banker
##Run: 
./banker
To run the unsafe input file replace the txt file in line 9 of main.cpp with data_unsafe.txt

##Progran Explanation:
The program starts by reading an input file in order to obtain the following.
the total number of instances for each resource type.
the allocation matrix - shows resources currecntly held by each process.
the maximum demand matrix - specifies the maximum amount of resources each process might request.
the available vector - indicates how many instances of each resource are free.

Using these inputs the program constructs the structures needed for the bankers algorythm being allocation, max need, available, and safe sequence.

The program then computes a need matrix that shows the remaining resources eaxch process may request to finish execution.
This matrix determines whether a process can safely execute based on if it's remaining need can be sattisfied by the current available resources.

The core of the program works using the bankers algorythm which works as follows.
1. work = available - a vector reprisenting current available resources finish[i] = false - used with all processes and checks if they are finished. Initilized to false at the start of the program.
2. Then the program looks for a process i where finish[i] = false and need[i] >= work. That means that the process can safely execute.
3. after allocation the resources allocated to i are added back to work and finish[i] is set to true. process i is then added to the safe sequence
4. the process repeats until all processes are finished or there is no safe route available.
5. If all finish[i] = true then the system is in a safe state and safe sequence contains the proper execution order.

##output examples:
safe state -System is in a SAFE state. Safe sequence: P0 -> P1 -> P2 -> P3 -> P4
unsafe state - System is NOT in a safe state.

##Question:
for the system given it is in a safe state and the proper safe sequence is [p3, p1, p0, p2, p4]
