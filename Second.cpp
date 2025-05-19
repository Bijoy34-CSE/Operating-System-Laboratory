#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <iomanip>
using namespace std;

// Function to implement Second Chance Page Replacement
void secondChancePageReplacement(int pages[], int n, int capacity) {
    unordered_map<int, bool> referenceBit; // Track reference bits
    queue<int> indexes;                    // FIFO queue of pages
    vector<vector<int>> frameTable(capacity, vector<int>(n, -1));
    vector<bool> pageFaults(n, false);     // Track page faults
    int totalPageFaults = 0;

    for (int i = 0; i < n; i++) {
        // If the page is already in memory (Hit)
        if (referenceBit.find(pages[i]) != referenceBit.end()) {
            referenceBit[pages[i]] = true; // Set the reference bit
            for (int k = 0; k < capacity; k++) {
                if (!indexes.empty()) {
                    frameTable[k][i] = indexes.front();
                    indexes.push(indexes.front());
                    indexes.pop();
                }
            }
            continue;
        }

        // If it's a miss (Page Fault)
        pageFaults[i] = true;
        totalPageFaults++;

        // If space is available, just insert
        if (indexes.size() < capacity) {
            indexes.push(pages[i]);
            referenceBit[pages[i]] = false;
        } else {
            // Second Chance Algorithm
            while (true) {
                int front = indexes.front();
                indexes.pop();
                if (referenceBit[front] == false) {
                    referenceBit.erase(front); // Evict the page
                    break;
                } else {
                    referenceBit[front] = false;
                    indexes.push(front); // Give it a second chance
                }
            }
            indexes.push(pages[i]);
            referenceBit[pages[i]] = false;
        }

        // Update the frame table with the current state
        int k = 0;
        queue<int> tempQueue = indexes;
        while (!tempQueue.empty() && k < capacity) {
            frameTable[k][i] = tempQueue.front();
            tempQueue.pop();
            k++;
        }
    }

    // Output the Page Reference Table
    cout << "Page Reference Table:\n";
    cout << "   ";
    for (int i = 0; i < n; i++) {
        cout << setw(4) << pages[i];
    }
    cout << "\n";
    cout << string(4 * n + 3, '-') << "\n";

    for (int i = 0; i < capacity; i++) {
        cout << "   ";
        for (int j = 0; j < n; j++) {
            if (frameTable[i][j] == -1)
                cout << setw(4) << "-";
            else
                cout << setw(4) << frameTable[i][j];
        }
        cout << "\n";
    }

    cout << string(4 * n + 3, '-') << "\n";
    cout << "   ";
    for (int i = 0; i < n; i++) {
        if (pageFaults[i])
            cout << "  PF";
        else
            cout << "    ";
    }
    cout << "\n";
    cout << "Total Page Faults: " << totalPageFaults << endl;
}

// Main function to test the algorithm
int main() {
    int n, capacity;

    cout << "Enter the number of pages: ";
    cin >> n;

    int pages[n];
    cout << "Enter the page references: ";
    for (int i = 0; i < n; i++) {
        cin >> pages[i];
    }

    cout << "Enter the number of available frames: ";
    cin >> capacity;

    secondChancePageReplacement(pages, n, capacity);

    return 0;
}

