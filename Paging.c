#include <stdio.h>
#include <stdlib.h>

int main() {
    int pageSize, pageTableSize;

    // Take page size and page table size from the user
    printf("Enter page size: ");
    scanf("%d", &pageSize);

    printf("Enter number of pages (page table size): ");
    scanf("%d", &pageTableSize);

    int pageTable[pageTableSize];

    // Take page table entries from user
    printf("Enter page table entries (frame numbers):\n");
    for (int i = 0; i < pageTableSize; i++) {
        printf("Page %d -> Frame: ", i);
        scanf("%d", &pageTable[i]);
    }

    int logicalAddress;
    printf("Enter logical address: ");
    scanf("%d", &logicalAddress);

    int pageNumber = logicalAddress / pageSize;
    int offset = logicalAddress % pageSize;

    if (pageNumber >= pageTableSize) {
        printf("Invalid logical address! Page number out of bounds.\n");
        return 1;
    }

    int frameNumber = pageTable[pageNumber];
    int physicalAddress = frameNumber * pageSize + offset;

    printf("Physical address: %d\n", physicalAddress);

    return 0;
}
