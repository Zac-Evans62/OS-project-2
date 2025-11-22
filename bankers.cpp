#include "bankers.hpp"
#include <iostream>
using namespace std;

Bankers::Bankers(int n_processes, int n_resources)
    : n(n_processes), m(n_resources)
{
    Allocation.assign(n, vector<int>(m, 0));
    Max.assign(n, vector<int>(m, 0));
    Need.assign(n, vector<int>(m, 0));
    Available.assign(m, 0);
}

void Bankers::setAllocation(int i, int j, int value) {
    Allocation[i][j] = value;
}
void Bankers::setMax(int i, int j, int value) {
    Max[i][j] = value;
}

void Bankers::setAvailable(int j, int value) {
    Available[j] = value;
}

void Bankers::computeNeed() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            Need[i][j] = Max[i][j] - Allocation[i][j];
        }
    }
}

bool Bankers::isSafe(vector<int>& safeSequence) {
    vector<int> Work = Available;
    vector<bool> Finish(n, false);
    safeSequence.clear();

    int count = 0;
    while (count < n) {
        bool found = false;

        for (int p = 0; p < n; p++) {
            if (!Finish[p]) {
                bool canRun = true;

                for (int r = 0; r < m; r++) {
                    if (Need[p][r] > Work[r]) {
                        canRun = false;
                        break;
                    }
                }

                if (canRun) {
                    for (int r = 0; r < m; r++) {
                        Work[r] += Allocation[p][r];
                    }
                    Finish[p] = true;
                    safeSequence.push_back(p);
                    found = true;
                    count++;
                }
            }
        }

        if (!found) {
            return false;
        }
    }

    return true;
}

bool Bankers::requestResources(int processID, vector<int> request) {

    for (int r = 0; r < m; r++) {
        if (request[r] > Need[processID][r]) {
            cout << "Error: Process exceeds maximum claim.\n";
            return false;
        }
    }

    for (int r = 0; r < m; r++) {
        if (request[r] > Available[r]) {
            cout << "Error: Resources not available.\n";
            return false;
        }
    }

    for (int r = 0; r < m; r++) {
        Available[r] -= request[r];
        Allocation[processID][r] += request[r];
        Need[processID][r] -= request[r];
    }

    vector<int> safeSeq;
    if (isSafe(safeSeq)) {
        cout << "Request granted. System remains safe.\n";
        return true;
    }

    for (int r = 0; r < m; r++) {
        Available[r] += request[r];
        Allocation[processID][r] -= request[r];
        Need[processID][r] += request[r];
    }

    cout << "Request denied. Unsafe state.\n";
    return false;
}
