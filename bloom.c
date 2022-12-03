#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <stdio.h>
#include "bloom.h"


struct bloom_t{
        hash_function hashFunc;
        int * tabFilter;
        int numHash;                 
        int bitsSize;
        uint64_t * hashes;

};

/*
      Dériver k hachages de ce condensé d'entrée en utilisant une permutation entière
*/

static uint64_t permute64(uint64_t x, uint64_t key){
    x += key;
    x ^= x >> 30;
    x *= 0xbf58476d1ce4e5b9U;
    x ^= x >> 27;
    x *= 0x94d049bb133111ebU;
    x ^= x >> 31;
    return x;
}

BloomFilter create(int bitSize, int numHash, hash_function hash)
{
    BloomFilter  filter = (BloomFilter) malloc(sizeof(BloomFilter));
    if (filter == NULL) {
         return 0;
    }
    filter->bitsSize = bitSize;
    filter->numHash = numHash;
    filter->hashFunc = hash;
    filter->tabFilter = malloc(filter->bitsSize*sizeof(int));
    filter->hashes = malloc(filter->numHash*sizeof(uint64_t));

    //Initialize all elements of bloom to zero
   for (int i = 0; i < filter->bitsSize; i++)
   {
      filter->tabFilter[i] = 0;
   }
       
   return filter;
}


void insert(const char *value, BloomFilter  * filter)
{
      uint64_t valuehash = (*filter)->hashFunc(value);

      //reduce expresssion lenght
  
      for (int i = 0; i < (*filter)->numHash ; i++) 
      {
            //call permutte64 to genr
            (*filter)->hashes[i] = permute64(valuehash, i);
            (*filter)->tabFilter[((*filter)->hashes[i])%(*filter)->bitsSize] = 1;
      }
      
}

bool search(const char *value, BloomFilter  filter)
{

      uint64_t fh =  filter->hashFunc(value);
      for (int i = 0; i < filter->numHash ; i++) 
      {
            filter->hashes[i] = permute64(fh, i);
            if (  filter->tabFilter[filter->hashes[i]%filter->bitsSize] != 1)
            {
               return 0;
            }
      }
      return 1;
}


void release(BloomFilter filter)
{
        free(filter);        
        free(filter->hashFunc);
        free(filter->tabFilter);
        free(filter->hashes);
}
