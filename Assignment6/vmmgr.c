#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Specifics
#define PAGE_ENTRIES 256
#define PAGE_SIZE 256
#define TLB_ENTRIES 16
#define FRAME_SIZE 256
#define FRAME_NUM 256
#define MEMORY_SIZE 256
#define BUFFER_SIZE 256

// Structs
typedef struct { // Check for endians
    __uint32_t unused: 16; 
    __uint32_t pageno: 8; 
    __uint32_t offset: 8; 
} virtualAddress;

typedef union {
    __uint32_t ul; 
    virtualAddress bf; 
} virtualMemory;

typedef struct {
    int frameNum;
    int pageNum;
} TLB;

typedef struct {
    int frameNum;
} pageTable;

// Files
FILE* addresses;
FILE* bs;

// Variables
virtualMemory vAddr;
TLB TLBarr[TLB_ENTRIES];
pageTable pageArr[PAGE_ENTRIES];
char buffer[BUFFER_SIZE];
char physMemory[MEMORY_SIZE][MEMORY_SIZE];

int TLBhits = 0;
int TLBfaults = 0;
int pageHits = 0;
int pageFaults = 0;

int frameCount = 0;
int TLBsize = 0;
int TLBcount = 0;

// Initialize all table associated values to -1
void setTables() {
    // Set page table
    for (int i = 0; i < PAGE_ENTRIES; ++i) {
        pageArr[i].frameNum = -1;
    }
    // Set TLB table
    for (int i = 0; i < TLB_ENTRIES; ++i) {
        TLBarr[i].frameNum = -1;
        TLBarr[i].pageNum = -1;
    }
}

// Check TLB for page number
int checkTLB(int pageNum) {
    for (int i = 0; i < TLB_ENTRIES; i++) {
        if (TLBarr[i].pageNum == pageNum) {
            TLBhits++;
            return i;
        }
    }
    TLBfaults++;
    return -1;
}

// Check page table for page number
int checkPage(int pageNum) {
    int frameNum = pageArr[pageNum].frameNum;
    if (frameNum != -1) {
        pageHits++;
        return frameNum;
    } else {
        pageFaults++;
        return -1;
    }
}

// Get frame number from backing store
int seekBS(int pageNum, int offset) {
    // Open BACKING_STORE.bin
    bs = fopen("BACKING_STORE.bin", "r");
    if (bs == NULL) {
        printf("File opening error: %s\n", strerror(errno));
        return -1;
    }
    
    // Find frame
    int frameSeek = fseek(bs, pageNum*256, SEEK_SET);
    if (frameSeek != 0) {
        printf("Frame seeking error: %s\n", strerror(errno));
        return -1;
    }

    fread(buffer, sizeof(char), BUFFER_SIZE, bs);
    int frameNum = frameCount;
    
    // Insert to TLB, page table, and physical memory
    if (TLBsize < TLB_ENTRIES) {
        // Room in TLB, insert
        TLBarr[TLBcount].frameNum = frameSeek;
        TLBarr[TLBcount].pageNum = pageNum;
        TLBsize++;
        TLBcount++;
    } else {
        // TLB full, FIFO
        for (int i = 1; i < TLB_ENTRIES; i++) {
            TLBarr[i].frameNum = TLBarr[i-1].frameNum;
            TLBarr[i].pageNum = TLBarr[i-1].pageNum;
        }
        TLBarr[0].frameNum = frameNum;
        TLBarr[0].pageNum = pageNum;
    }
    pageArr[pageNum].frameNum = frameNum;
    memcpy(physMemory[frameNum], buffer, BUFFER_SIZE);
    frameCount++;

    // Close BACKING_STORE.bin
    fclose(bs);
    return frameSeek;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Error: 2 arguments needed.\n");
        return -1;
    }

    setTables();

    // Open address file
    addresses = fopen(argv[1], "r");
    if (addresses == NULL) {
        printf("File opening error: %s\n", strerror(errno));
        return -1;
    }

    // Iterate through file
    while (fgets(buffer, BUFFER_SIZE, addresses)) {
        int pAddrInt = 0;
        vAddr.ul = atoi(buffer);
        printf("Virtual Address: %d   ", vAddr.ul);
        vAddr.bf.pageno = (vAddr.ul & 0xFF00) >> 8;
        vAddr.bf.offset = (vAddr.ul & 0xFF);

        // Check TLB for address
        int frameReturn = checkTLB(vAddr.bf.pageno);
        if (frameReturn == -1) {
            // TLB miss: Check page table for address
            frameReturn = checkPage(vAddr.bf.pageno);
            if (frameReturn == -1) {
                // Page fault: Load from backing store
                frameReturn = seekBS(vAddr.bf.pageno, vAddr.bf.offset);
                if (frameReturn == -1) {
                    printf("Error: Cannot find frame.\n");
                    return -1;
                } else {
                    pAddrInt = (TLBarr[frameReturn].frameNum * FRAME_SIZE) + vAddr.bf.offset;
                }
            } else {
                pAddrInt = (pageArr[vAddr.bf.pageno].frameNum * FRAME_SIZE) + vAddr.bf.offset;
            }
        } else {
            pAddrInt = (TLBarr[frameReturn].frameNum * FRAME_SIZE) + vAddr.bf.offset;
        }

        // Get physical address information
        uint64_t pAddr = (uint64_t)&physMemory[pAddrInt];
        int signedByte = (intptr_t)&physMemory[pAddrInt];

        printf("Physical Addresss: %lu   ", pAddr);
        printf("Signed Byte: %d\n", signedByte);
    }

    double TLBhitRate = (TLBhits / (TLBfaults+TLBhits)) * 100;
    double pageFaultRate = (pageFaults / (pageFaults+pageHits)) * 100;
    
    printf("TLB Hit Rate: %f\n", TLBhitRate);
    printf("Page Fault Rate: %f\n", pageFaultRate);

    // Close address file
    fclose(addresses);
}