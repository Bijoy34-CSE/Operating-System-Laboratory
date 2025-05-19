#include <iostream>
#include <queue>
#include <unordered_set>
#include <vector>
#include <iomanip>
using namespace std;

// Function to implement strict FIFO Page Replacement
void fifoPageReplacement(int pages[], int n, int capacity) {
    unordered_set<int> s;        // To store the pages in memory
    queue<int> indexes;          // To maintain the order of pages (FIFO)
    vector<vector<int>> frameTable(capacity, vector<int>(n, -1));
    vector<bool> pageFaults(n, false);  // To track page faults
    int totalPageFaults = 0;

    for (int i = 0; i < n; i++) {
        // If the page is already in memory, just maintain the current state
        if (s.find(pages[i]) != s.end()) {
            for (int k = 0; k < capacity; k++) {
                if (!indexes.empty()) {
                    frameTable[k][i] = indexes.front();
                    indexes.push(indexes.front());
                    indexes.pop();
                }
            }
            continue; // Page is already there; skip to next
        }

        // If the page is not in memory, a Page Fault occurs
        if (s.size() < capacity) {
            s.insert(pages[i]);
            indexes.push(pages[i]);
        } else {
            // FIFO logic: Remove the oldest page and insert the new one
            int val = indexes.front();
            indexes.pop();
            s.erase(val);

            s.insert(pages[i]);
            indexes.push(pages[i]);
        }
        pageFaults[i] = true;
        totalPageFaults++;

        // Update the frame table with the current state of the queue
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

    fifoPageReplacement(pages, n, capacity);

    return 0;
}

