#ifndef __BLOOM_FILTER__

#define __BLOOM_FILTER__

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>


/**
 * Définition d'un type incomplet pour représenter les données du filtre
 */
typedef struct bloom_t *BloomFilter;

/**
 *
 * Définition d'un type générique pour les fonctions de hachage
 *
 */

typedef uint64_t (* hash_function) (const char * value);

/** Une fonction qui permet d'initialiser le bloom filter
 *   en fournissant le nombre de bits à utiliser pour stocker les éléménts du filtre
 *   et le nombre de fonctions de hachage à utiliser 
 */
BloomFilter create(int bitSize, int numHash, hash_function fonc);


/**
 * Elle permet d'insérer une nouvelle valeur dans le bloom filter
 * 
 */
void insert(const char *value, BloomFilter  * filter);

/**
 *
 * Cette fonction renvoie vrai s'il est probable que value soit dans le filter 
 * et faux si définitivement value n'est pas dans le filtre
 *
 */
bool search(const char *value, BloomFilter  filter);

/**
 * Cette fonction permet de libérer les différentes ressources qui sont allouées par le filtre.
 */
void release(BloomFilter filter);

#endif
