#ifndef BANKERS_HPP
#define BANKERS_HPP

#include <vector>

class Bankers {

public:
    
    Bankers(int n_processes, int n_resources);

    void setAllocation(int i, int j, int value);
    void setMax(int i, int j, int value);
    void setAvailable(int j, int value);

    void computeNeed();

    bool isSafe(std::vector<int>& safeSequence);

    bool requestResources(int processID, std::vector<int> request);

    void releaseResources(int processID, std::vector<int> release);

private:
    int n;
    int m; 

    std::vector<std::vector<int>> Allocation;  
    std::vector<std::vector<int>> Max;        
    std::vector<std::vector<int>> Need;       
    std::vector<int> Available;             

};

#endif