#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Function to convert memory size to bytes (KB, MB, or Bytes)
long long convertToBytes(long long size, string unit) {
    if (unit == "KB") {
        return size * 1024;
    } else if (unit == "MB") {
        return size * 1024 * 1024;
    } else {
        return size;
    }
}

// Structure to represent a memory block
struct MemoryBlock {
    long long size;
    bool allocated;
    string process;
    long long start;
    long long end;
};

// Function to display the Gantt Chart (Memory Allocation View)
void displayGanttChart(const vector<MemoryBlock>& memory) {
    cout << "\nGantt Chart (Memory Allocation View):\n";
    for (int i = 0; i < memory.size(); i++) {
        string status = memory[i].allocated ? "Allocated" : "Free";
        cout << "Block " << i + 1 << ": ";
        if (memory[i].allocated) {
            cout << memory[i].process << " [" << memory[i].start << " - " << memory[i].end << "]";
        } else {
            cout << "Free [" << memory[i].start << " - " << memory[i].end << "]";
        }
        cout << " - " << status << endl;
    }
}

// Function to initialize memory with processes and detect gaps
void initializeMemory(long long totalMemorySize, string unit, vector<pair<string, pair<long long, long long>>>& processes, vector<MemoryBlock>& memory) {
    long long totalMemoryBytes = convertToBytes(totalMemorySize, unit);

    sort(processes.begin(), processes.end(), [](auto &a, auto &b) {
        return a.second.second < b.second.second;
    });

    long long previousEnd = -1;

    for (auto& p : processes) {
        string processName = p.first;
        long long processSize = p.second.first;
        long long startingAddress = p.second.second;
        long long processSizeBytes = convertToBytes(processSize, unit);

        if (previousEnd + 1 < startingAddress) {
            memory.push_back({startingAddress - (previousEnd + 1), false, "", previousEnd + 1, startingAddress - 1});
        }

        memory.push_back({processSizeBytes, true, processName, startingAddress, startingAddress + processSizeBytes - 1});
        previousEnd = startingAddress + processSizeBytes - 1;
    }

    if (previousEnd < totalMemoryBytes - 1) {
        memory.push_back({totalMemoryBytes - previousEnd - 1, false, "", previousEnd + 1, totalMemoryBytes - 1});
    }

    displayGanttChart(memory);
}

// Function to add a new process using Best Fit
void addNewProcess(vector<MemoryBlock>& memory, string newProcessName, long long newProcessSize, string unit) {
    long long newProcessSizeBytes = convertToBytes(newProcessSize, unit);
    bool allocated = false;
    int worstIndex = -1;
    long long maxSize = -1;

    // Find the worst fit block
    for (int i = 0; i < memory.size(); i++) {
        if (!memory[i].allocated && memory[i].size >= newProcessSizeBytes) {
            if (memory[i].size > maxSize) {
                maxSize = memory[i].size;
                worstIndex = i;
            }
        }
    }

    if (worstIndex != -1) {
        long long remainingSize = memory[worstIndex].size - newProcessSizeBytes;

        memory[worstIndex].allocated = true;
        memory[worstIndex].process = newProcessName;
        memory[worstIndex].size = newProcessSizeBytes;
        memory[worstIndex].end = memory[worstIndex].start + newProcessSizeBytes - 1;

        if (remainingSize > 0) {
            memory.insert(memory.begin() + worstIndex + 1, {remainingSize, false, "", memory[worstIndex].end + 1, memory[worstIndex].end + remainingSize});
        }

        allocated = true;
    }

    if (allocated) {
        cout << "Process " << newProcessName << " with size " << newProcessSize << " allocated successfully (Worst Fit).";
        displayGanttChart(memory);
    } else {
        cout << "Process " << newProcessName << " could not be allocated. Not enough space.";
    }
}


int main() {
    long long totalMemorySize;
    string memoryUnit;
    cout << "Enter total memory size (in kb, mb, or Bytes): ";
    cin >> totalMemorySize;
    //cout << "Enter memory unit (KB, MB, or Bytes): ";
    cin >> memoryUnit;

    int processCount;
    cout << "Enter the number of processes to initialize: ";
    cin >> processCount;
    vector<pair<string, pair<long long, long long>>> processes;

    for (int i = 0; i < processCount; i++) {
        string processName;
        long long processSize, startingAddress;
        cout << "Enter process name: ";
        cin >> processName;
        cout << "Enter size of " << processName << " in " << memoryUnit << ": ";
        cin >> processSize;
        cout << "Enter starting address for " << processName << ": ";
        cin >> startingAddress;
        processes.push_back({processName, {processSize, startingAddress}});
    }

    vector<MemoryBlock> memory;
    initializeMemory(totalMemorySize, memoryUnit, processes, memory);

    string newProcessName;
    long long newProcessSize;
    cout << "Enter new process name: ";
    cin >> newProcessName;
    cout << "Enter size of " << newProcessName << " in " << memoryUnit << ": ";
    cin >> newProcessSize;

    addNewProcess(memory, newProcessName, newProcessSize, memoryUnit);

    return 0;
}
