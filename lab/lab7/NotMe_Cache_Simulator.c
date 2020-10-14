#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

#define CACHE_UNIT 1024

// to test in wsl: ./a.out 16 16 < NotMe_Sample.txt
//For readability of the location in a SA cache set
#define N_WAYS 2    //we simulate a simple 2-way SA cache
#define LEFT 0  
#define RIGHT 1


struct CacheBlock
{
    unsigned int tag; 
    bool valid;
    //We only simulate the hit / miss, so the actual data itself is not kept
};

struct TwoWaySet
{
    //Using 2 CacheBlock in a 2-way SA set
    struct CacheBlock location[2];

    //A flag to indicate who is the victim for replacement
    bool notLeft;
};

void InitializeCacheBlock( struct CacheBlock* cBlkPtr)
{
    cBlkPtr->tag = 0;
    cBlkPtr->valid = false;
}

void InitializeCache(struct TwoWaySet newCache[], int size)
{
    int i;

    for (i = 0; i < size; i++){
        InitializeCacheBlock(&(newCache[i].location[LEFT]));
        InitializeCacheBlock(&(newCache[i].location[RIGHT]));
        //left is the default victim at the start
        newCache[i].notLeft = false;
    }
}

bool accessCache(struct TwoWaySet cache[], int nSet, int blockSize, unsigned int address) // nSet is number of sets, blockSize if cache block size
//Access the cache with memory address "address"
//Return: True if cache hit, False otherwise
//Side Effect: This function modifies the corresponding cache block information in cache[] array
{
    unsigned int setNumber, blockNumber, setIdx, tag, offset, targetLocation;
    struct TwoWaySet* targetBlockPtr; //a common way to simplify syntax, see later
    bool result;

    //Compute the relevant information
   
    //offset = address % blockSize;
    offset = address & (blockSize-1);
    blockNumber = address / blockSize;
   
    //setIdx = blockNumber % nSet;
    unsigned int bSizeLog2 = log2(blockSize);
    setIdx = (address >> bSizeLog2) & (nSet-1); //setIdx is cache index

    //tag = blockNumber / nCacheBlock;
    unsigned int otherLog2 = log2(nSet*blockSize);
    tag = (address >> otherLog2);

    printf("Address[%#010x] = [Tag:0x%x|SetIdx:0x%x|Offset:0x%x] => ", address, tag, setIdx, offset);

    //Check Cache
    targetBlockPtr = &cache[setIdx];
    if (targetBlockPtr->location[LEFT].valid == 1 && targetBlockPtr->location[LEFT].tag == tag ) {
        //hit!
        result = true;
        //TODO
        //Update the notLeft flag, use the following partial code to help with syntax
        // hit, access left, notLeft = true
        targetBlockPtr->notLeft = true;
        printf("Hit [LEFT] !\n");
    } else if ((targetBlockPtr->location[RIGHT].valid == 1 && targetBlockPtr->location[RIGHT].tag == tag)) {
        result = true;
        //TODO
        //Update the notLeft flag, use the following partial code to help with syntax
        //targetBlockPtr->notLeft = ?????????;
        // hit, access right, notLeft = false
        targetBlockPtr->notLeft = false;
        printf("Hit [RIGHT] !\n");
    } else {
        //Miss - Update the cache accordingly by "bringing" the block into the cache

        if (targetBlockPtr->notLeft) {
            targetLocation = RIGHT; // load to right, set notLeft as false
        } else {
            targetLocation = LEFT; // load to left, set notLeft as true
        }
        targetBlockPtr->location[targetLocation].valid = true;
        targetBlockPtr->location[targetLocation].tag = tag;
        //TODO
        //Update the notLeft flag, use the following partial code to help with syntax
        targetBlockPtr->notLeft = !targetBlockPtr->notLeft;
        result = false;
        printf("Miss [Replaced %d]\n", targetLocation);
    }

    return result;
}

int main(int argc, char const *argv[])
{
    /* code */

    unsigned int address, blockTag;
    int cacheSize, blockSize, nSet, nAccess, nHit, cacheId;
  
    if (argc < 3){
        printf("Usage: %s Total_Size(in Kbytes) BlockSize(bytes)\n", argv[0]);
        return 1;
    }

    //setup parameters
    cacheSize = atoi(argv[1]) * CACHE_UNIT;
    blockSize = atoi(argv[2]);
    nSet = cacheSize / blockSize / N_WAYS; // number of sets
    
    struct TwoWaySet SACache[nSet];


    InitializeCache(SACache, nSet);
    printf("2-Way SA Cache [%d Byte(s) total capacity | %d Byte(s) block size | %d Set(s)]\n", cacheSize, blockSize, nSet);

    //Start simulating cache access
    nAccess = 0;
    nHit = 0;
    while(scanf("%x", &address) == 1) { 
        nAccess++;
        nHit += accessCache(SACache, nSet, blockSize, address);
    }

    //Print statistics
    printf("Total Access = %d\n", nAccess);
    printf("Cache Hit = %d, %.4f%%\n", nHit, 100.0*nHit/nAccess);


    return 0;
}
