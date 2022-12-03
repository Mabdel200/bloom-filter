#include <stdio.h>
#include <stdlib.h>
#include "bloom.h"

#define FNV_OFFSET 14695981039346656037UL
#define FNV_PRIME 1099511628211UL

static uint64_t  hash(const char* data){
   uint64_t hash = FNV_OFFSET;
   for (const char* p = data; *p; p++) {
       hash ^= (uint64_t)(unsigned char)(*p);
       hash *= FNV_PRIME;
   }
   return hash;
}

int main(void){
   BloomFilter filter = create(1024, 5, hash); 
   
   insert("HALLAM",&filter); 
   insert("VINCENT",&filter); 
   insert("DOUZE",&filter); 
   insert("BONJOUR",&filter); 
   insert("SALUT",&filter); 
   insert("IMPORTE",&filter);
   insert("ABDEL",&filter);
   printf("Filtre contient DOUWE: %d\n", search("DOUWE", filter)); 
   printf("Filtre contient HALLAM: %d\n", search("HALLAM", filter)); 
   printf("Filtre contient VINCENT: %d\n", search("VINCENT", filter)); 
   printf("Filtre contient DOUZE: %d\n", search("DOUZE", filter)); 
   printf("Filtre contient BONJOUR: %d\n", search("BONJOUR", filter)); 
   printf("Filtre contient SALUT: %d\n", search("SALUT", filter)); 
   printf("Filtre contient IMPORTE: %d\n", search("IMPORTE", filter)); 
   printf("Filtre contient IMPORTER: %d\n", search("IMPORTER", filter)); 
   printf("Filtre contient RAPPORTE: %d\n", search("RAPPORTE", filter)); 
   printf("Filtre contient ABBO: %d\n", search("ABBO", filter)); 
   printf("Filtre contient ABDEL: %d\n", search("ABDEL", filter)); 
   release(filter);

   return 0;
}
