#include <iostream>
#include <queue>
#include <unordered_set>
#include <vector>
#include <iomanip>
using namespace std;

// Function to implement FIFO Page Replacement with Rearrangement on Hit
void fifoPageReplacement(int pages[], int n, int capacity) {
    unordered_set<int> s;
    queue<int> indexes;
    vector<bool> pageFaults(n, false);
    vector<vector<int>> frameTable(capacity, vector<int>(n, -1));
    int pageFault = 0;

    for (int i = 0; i < n; i++) {
        // If the page is already in memory (Page Hit)
        if (s.find(pages[i]) != s.end()) {
            // Rearrange the queue to mark it as recently visited
            queue<int> tempQueue;
            while (!indexes.empty()) {
                int front = indexes.front();
                indexes.pop();
                if (front != pages[i]) {
                    tempQueue.push(front);
                }
            }
            tempQueue.push(pages[i]);
            indexes = tempQueue;

            // Copy current state to the frame table
            int k = 0;
            queue<int> copyQueue = indexes;
            while (!copyQueue.empty() && k < capacity) {
                frameTable[k][i] = copyQueue.front();
                copyQueue.pop();
                k++;
            }
            continue; // No page fault, so skip to the next iteration
        }

        // Page Fault
        if (s.size() < capacity) {
            s.insert(pages[i]);
            indexes.push(pages[i]);
        } else {
            int val = indexes.front();
            indexes.pop();
            s.erase(val);

            s.insert(pages[i]);
            indexes.push(pages[i]);
        }
        pageFault++;
        pageFaults[i] = true;

        // Update the frame table with the current state of the queue
        int k = 0;
        queue<int> copyQueue = indexes;
        while (!copyQueue.empty() && k < capacity) {
            frameTable[k][i] = copyQueue.front();
            copyQueue.pop();
            k++;
        }
    }

    // Output the table
    cout << "Page Reference Table:";
    cout << "-------------------------\n";
    for (int i = 0; i < capacity; i++) {
        for (int j = 0; j < n; j++) {
            if (frameTable[i][j] == -1)
                cout << setw(4) << "-";
            else
                cout << setw(4) << frameTable[i][j];
        }
        cout << "\n";
    }
    cout << "-------------------------\n";
     for (int i = 0; i < n; i++) {
        if (pageFaults[i])
            cout << "  PF";
        else
            cout << "    ";
    }
    cout << '\n';
    cout << "Total Page Faults: " << pageFault << endl;
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

    fifoPageReplacement(pages, n, capacity);

    return 0;
}
