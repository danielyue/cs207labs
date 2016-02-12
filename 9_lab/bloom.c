#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "bloom.h"
/* this is the struct definition given in the library

typedef uint64_t index_t;
typedef uint64_t key_t;
typedef struct {
  index_t size; // in bits
  index_t count; // in bits
  index_t *table;
} bloom_filter_t;
#define N_HASHES 3

*/

// taken from https://gist.github.com/badboy/6267743
int hash32shift(int key)
{
  key = ~key+(key << 15); // key = (key << 15) - key - 1;
  key = key^(key >> 12);
  key = key+(key << 2);
  key = key^(key >> 4);
  key = key*2057; // key = (key + (key << 3)) + (key << 11);
  key = key^(key >> 16);
  return key;
}

// taken from http://stackoverflow.com/questions/664014/what-integer-hash-function-are-good-that-accepts-an-integer-hash-key
unsigned int hashUnsigned(unsigned int x) {
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x);
    return x;
}

/*
void set_bit(bloom_filter_t *B, index_t i){
  // TODO
  return;
}

index_t get_bit(bloom_filter_t *B, index_t i){
  // TODO
  return;
}
*/

index_t hash1(bloom_filter_t *B, key_t k){
  // TODO
  index_t value;
  value = k;// B->size * B->count * *B->table;
  return ((index_t) hashUnsigned((unsigned int) value)) % B->size;
}

index_t hash2(bloom_filter_t *B, key_t k){
  // TODO
  index_t value;
  value = k; //B->size * B->count * *B->table;
  return ((index_t) hash32shift((int) value)) % B->size;
}
/*
void bloom_init(bloom_filter_t *B, index_t size_in_bits){
  // TODO
  return;
}

void bloom_destroy(bloom_filter_t *B){
  // TODO
  return;
}
int bloom_check(bloom_filter_t *B, key_t k){
  // TODO
  return;
}

void bloom_add(bloom_filter_t *B, key_t k){
  // TODO
  return;
}
*/
