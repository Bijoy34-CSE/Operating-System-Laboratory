#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BLOCKS 100
#define MAX_PROCESSES 100
#define MAX_NAME_LEN 50

typedef struct {
    long long size;
    int allocated;
    char process[MAX_NAME_LEN];
    long long start;
    long long end;
} MemoryBlock;

long long convertToBytes(long long size, char* unit) {
    if (strcmp(unit, "KB") == 0) {
        return size * 1024;
    } else if (strcmp(unit, "MB") == 0) {
        return size * 1024 * 1024;
    } else {
        return size;
    }
}

void displayGanttChart(MemoryBlock memory[], int count) {
    printf("\nGantt Chart (Memory Allocation View):\n");
    for (int i = 0; i < count; i++) {
        printf("Block %d: ", i + 1);
        if (memory[i].allocated) {
            printf("%s [%lld - %lld] - Allocated\n", memory[i].process, memory[i].start, memory[i].end);
        } else {
            printf("Free [%lld - %lld] - Free\n", memory[i].start, memory[i].end);
        }
    }
}

void initializeMemory(
    long long totalMemorySize,
    char* unit,
    char processNames[][MAX_NAME_LEN],
    long long processSizes[],
    long long startAddresses[],
    int processCount,
    MemoryBlock memory[],
    int* memCount
) {
    long long totalMemoryBytes = convertToBytes(totalMemorySize, unit);

    // Sort processes by starting address (Simple Bubble Sort for clarity)
    for (int i = 0; i < processCount - 1; i++) {
        for (int j = 0; j < processCount - i - 1; j++) {
            if (startAddresses[j] > startAddresses[j + 1]) {
                // Swap names
                char tempName[MAX_NAME_LEN];
                strcpy(tempName, processNames[j]);
                strcpy(processNames[j], processNames[j + 1]);
                strcpy(processNames[j + 1], tempName);

                // Swap sizes and addresses
                long long tmpSize = processSizes[j];
                processSizes[j] = processSizes[j + 1];
                processSizes[j + 1] = tmpSize;

                long long tmpAddr = startAddresses[j];
                startAddresses[j] = startAddresses[j + 1];
                startAddresses[j + 1] = tmpAddr;
            }
        }
    }

    long long previousEnd = -1;
    int idx = 0;

    for (int i = 0; i < processCount; i++) {
        long long sizeBytes = convertToBytes(processSizes[i], unit);
        long long startAddr = startAddresses[i];
        long long endAddr = startAddr + sizeBytes - 1;

        if (previousEnd + 1 < startAddr) {
            memory[idx++] = (MemoryBlock){startAddr - (previousEnd + 1), 0, "", previousEnd + 1, startAddr - 1};
        }

        MemoryBlock block;
        block.size = sizeBytes;
        block.allocated = 1;
        strcpy(block.process, processNames[i]);
        block.start = startAddr;
        block.end = endAddr;

        memory[idx++] = block;
        previousEnd = endAddr;
    }

    if (previousEnd < totalMemoryBytes - 1) {
        memory[idx++] = (MemoryBlock){totalMemoryBytes - previousEnd - 1, 0, "", previousEnd + 1, totalMemoryBytes - 1};
    }

    *memCount = idx;
    displayGanttChart(memory, idx);
}

void addNewProcess(MemoryBlock memory[], int* memCount, char* newProcessName, long long newProcessSize, char* unit) {
    long long newSizeBytes = convertToBytes(newProcessSize, unit);
    int bestIndex = -1;
    long long minSize = 1e12;

    for (int i = 0; i < *memCount; i++) {
        if (!memory[i].allocated && memory[i].size >= newSizeBytes) {
            if (memory[i].size < minSize) {
                minSize = memory[i].size;
                bestIndex = i;
            }
        }
    }

    if (bestIndex != -1) {
        long long remainingSize = memory[bestIndex].size - newSizeBytes;

        memory[bestIndex].allocated = 1;
        strcpy(memory[bestIndex].process, newProcessName);
        memory[bestIndex].size = newSizeBytes;
        memory[bestIndex].end = memory[bestIndex].start + newSizeBytes - 1;

        if (remainingSize > 0) {
            // Shift elements to make space
            for (int j = *memCount; j > bestIndex + 1; j--) {
                memory[j] = memory[j - 1];
            }

            memory[bestIndex + 1] = (MemoryBlock){
                remainingSize, 0, "", memory[bestIndex].end + 1, memory[bestIndex].end + remainingSize
            };
            (*memCount)++;
        }

        printf("\nProcess %s with size %lld allocated successfully (Best Fit).\n", newProcessName, newProcessSize);
        displayGanttChart(memory, *memCount);
    } else {
        printf("\nProcess %s could not be allocated. Not enough space.\n", newProcessName);
    }
}

int main() {
    long long totalMemorySize;
    char memoryUnit[10];

    printf("Enter total memory size (in KB, MB, or Bytes): ");
    scanf("%lld", &totalMemorySize);
    printf("Enter memory unit (KB, MB, or Bytes): ");
    scanf("%s", memoryUnit);

    int processCount;
    printf("Enter the number of processes to initialize: ");
    scanf("%d", &processCount);

    char processNames[MAX_PROCESSES][MAX_NAME_LEN];
    long long processSizes[MAX_PROCESSES];
    long long startAddresses[MAX_PROCESSES];

    for (int i = 0; i < processCount; i++) {
        printf("Enter process name: ");
        scanf("%s", processNames[i]);
        printf("Enter size of %s in %s: ", processNames[i], memoryUnit);
        scanf("%lld", &processSizes[i]);
        printf("Enter starting address for %s: ", processNames[i]);
        scanf("%lld", &startAddresses[i]);
    }

    MemoryBlock memory[MAX_BLOCKS];
    int memCount = 0;

    initializeMemory(totalMemorySize, memoryUnit, processNames, processSizes, startAddresses, processCount, memory, &memCount);

    char newProcessName[MAX_NAME_LEN];
    long long newProcessSize;

    int c=1;

    while(c){
        printf("Enter new process name: ");
        scanf("%s", newProcessName);
        printf("Enter size of %s in %s: ", newProcessName, memoryUnit);
        scanf("%lld", &newProcessSize);


        addNewProcess(memory, &memCount, newProcessName, newProcessSize, memoryUnit);
        printf("Enter 1 to add new process and 0 to exit: ");
        scanf("%d",&c);
    }


    return 0;
}

