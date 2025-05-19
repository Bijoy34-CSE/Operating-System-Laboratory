#include <iostream>
#include <vector>
using namespace std;

bool detectDeadlockMultiInstance(
    vector<vector<int>> alloc,
    vector<vector<int>> request,
    vector<int> available) {

    int n = alloc.size(), r = available.size();
    vector<bool> finish(n, false);

    bool done;
    do {
        done = false;
        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                bool canFinish = true;
                for (int j = 0; j < r; j++) {
                    if (request[i][j] > available[j]) {
                        canFinish = false;
                        break;
                    }
                }
                if (canFinish) {
                    for (int j = 0; j < r; j++)
                        available[j] += alloc[i][j];
                    finish[i] = true;
                    done = true;
                }
            }
        }
    } while (done);

    for (int i = 0; i < n; ++i)
        if (!finish[i]) return true; // Deadlock exists

    return false; // No deadlock
}

int main() {
    int n, r;
    cout << "\nEnter number of processes and resources: ";
    cin >> n >> r;

    vector<vector<int>> alloc(n, vector<int>(r)), request(n, vector<int>(r));
    vector<int> available(r);

    cout << "Enter Allocation Matrix:\n";
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < r; ++j)
            cin >> alloc[i][j];
    }

    cout << "Enter Request Matrix:\n";
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < r; ++j)
            cin >> request[i][j];

    cout << "Enter Available Resources:\n";
    for (int i = 0; i < r; ++i)
        cin >> available[i];

    if (detectDeadlockMultiInstance(alloc, request, available))
        cout << "Deadlock detected.\n";
    else
        cout << "No deadlock detected.\n";

    return 0;
}

