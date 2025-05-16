#include <stdio.h>

int getPhysicalAddress(int seg_count, int limit[], int base[], int segmentNumber, int offset) {
    if (segmentNumber >= seg_count || segmentNumber < 0) {
        printf("Invalid segment number!\n");
        return -1;
    }

    if (offset >= limit[segmentNumber]) {
        printf("Segmentation fault: Offset exceeds segment limit!\n");
        return -1;
    }

    int physicalAddress = base[segmentNumber] + offset;
    return physicalAddress;
}

int main() {
    int seg_count;

    printf("Enter total number of segments: ");
    scanf("%d", &seg_count);

    int limit[seg_count], base[seg_count];

    printf("Enter limit and base of each segment:\n");
    for (int i = 0; i < seg_count; i++) {
        printf("Segment No: %d\n", i);
        printf("Limit: ");
        scanf("%d", &limit[i]);
        printf("Base: ");
        scanf("%d", &base[i]);
        printf("\n");
    }

    int segmentNumber, offset;
    printf("Enter segment number (0 to %d): ", seg_count - 1);
    scanf("%d", &segmentNumber);

    printf("Enter offset (reference byte): ");
    scanf("%d", &offset);

    int physicalAddress = getPhysicalAddress(seg_count, limit, base, segmentNumber, offset);
    if (physicalAddress != -1) {
        printf("Physical Address: %d\n", physicalAddress);
    }

    return 0;
}

