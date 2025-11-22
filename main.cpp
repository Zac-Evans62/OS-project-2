#include <iostream>
#include <fstream>
#include <vector>
#include "bankers.hpp"

using namespace std;

int main() {
    ifstream file("data.txt");
    if (!file.is_open()) {
        cerr << "Error: Could not open input file.\n";
        return 1;
    }

    int m = 3;
    int n = 5;

    vector<int> total(m);
    for (int i = 0; i < m; i++) file >> total[i];

    vector<vector<int>> allocation(n, vector<int>(m));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            file >> allocation[i][j];

    vector<vector<int>> maxNeed(n, vector<int>(m));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            file >> maxNeed[i][j];

    vector<int> available(m);
    for (int i = 0; i < m; i++) file >> available[i];

    file.close();

    Bankers b(n, m);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            b.setAllocation(i, j, allocation[i][j]);
            b.setMax(i, j, maxNeed[i][j]);
        }

    for (int i = 0; i < m; i++)
        b.setAvailable(i, available[i]);

    b.computeNeed();

    vector<int> safeSequence;
    bool safe = b.isSafe(safeSequence);

    if (safe) {
        cout << "System is in a SAFE state.\nSafe sequence: ";
        for (int i = 0; i < safeSequence.size(); i++) {
            cout << "P" << safeSequence[i];
            if (i != safeSequence.size() - 1) cout << " -> ";
        }
        cout << endl;
    } else {
        cout << "System is NOT in a safe state.\n";
    }

    return 0;
}