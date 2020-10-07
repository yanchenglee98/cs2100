#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

#define CACHE_UNIT 1024

struct CacheBlock
{
    unsigned int tag; 
    bool valid;
    //We only simulate the hit / miss, so the actual data itself is not kept
};

void InitilaizeCache(struct CacheBlock newCache[], int size)
{
    int i;

    for (i = 0; i < size; i++){
        newCache[i].tag = 0;
        newCache[i].valid = false;
    }
}

bool accessCache(struct CacheBlock cache[], int nCacheBlock, int blockSize, unsigned int address)
//Access the cache with memory address "address"
//Return: True if cache hit, False otherwise
//Side Effect: This function modifies the corresponding cache block information in cache[] array
{
    unsigned int cacheIdx, tag, offset;
    bool result;

    //Compute the relevant information
	//TODO: a. Figure out the relevant fields
    //         You can add additional variable(s) if it helps
    offset = address % blockSize;
    cacheIdx = (address / blockSize) % nCacheBlock;             //Index of Cache Block
    tag = address / (blockSize * nCacheBlock);                  //Tag for the memory address

    printf("Address[%#010x] = [Tag:0x%x|Idx:0x%x|Offset:0x%x] => ", address, tag, cacheIdx, offset);

    //Check Cache
    if (cache[cacheIdx].valid && cache[cacheIdx].tag == tag) {  //TODO: b. figure out the condition
        //hit!
        result = true;
        printf("Hit!\n");
    } else {
        //Miss
        
		//TODO: c. Update the cache
		cache[cacheIdx].valid = 1;
        cache[cacheIdx].tag = tag;
		
        result = false;
        printf("Miss\n");
    }

    return result;
}

// to test use: ./DMCache_Simulator.exe 16 16
// in wsl: ./DMCache_Simulator.exe 16 16 < SPECINT-401-1K-Access.dat
int main(int argc, char const *argv[])
{
    /* code */

    unsigned int address, blockTag;
    int cacheSize, blockSize, nCacheBlock, nAccess, nHit, cacheId;
  
    if (argc < 3){
        printf("Usage: %s Total_Size(in Kbytes) BlockSize(bytes)\n", argv[0]);
        return 1;
    }

    //setup parameters
    cacheSize = atoi(argv[1]) * CACHE_UNIT;
    blockSize = atoi(argv[2]);
    nCacheBlock = cacheSize / blockSize;
    
    struct CacheBlock DMCache[nCacheBlock];

    printf("Direct Mapped Cache [%d Byte(s) total capacity | %d Byte(s) block size]\n", cacheSize, blockSize);

    //Start simulating cache access
    nAccess = 0;
    nHit = 0;
    while(scanf("%x", &address) == 1) { 
        nAccess++;
        nHit += accessCache(DMCache, nCacheBlock, blockSize, address);
    }

    //Print statistics
    printf("Total Access = %d\n", nAccess);
    printf("Cache Hit = %d, %.4f%%\n", nHit, 100.0*nHit/nAccess);


    return 0;
}
