#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include "bloom.h"

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

// taken from http://stackoverflow.com/questions/664014/
// /what-integer-hash-function-are-good-that-accepts-an-integer-hash-key
unsigned int hashUnsigned(unsigned int x) {
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x);
    return x;
}

void set_bit(bloom_filter_t *B, index_t i){
  // number >> shift ---> floor(number / 2^shift)
  index_t integer,integerIndex,maskNum,maskedInt;
  integer = *(B->table + (i / (index_t) 64));
  integerIndex = i % 64;
  maskNum = (index_t) pow(2.,(long) (integerIndex - 1));
  maskedInt = (integer | maskNum);
  *(B->table + (i / (index_t) 64)) = maskedInt;
  return;
}

index_t get_bit(bloom_filter_t *B, index_t i){
  // number >> shift ---> floor(number / 2^shift)
  // the 0th bit is the first in sequence
  // the 64th bit is the first bit of the second int
  index_t integer,integerIndex,maskNum,maskedInt;
  integer = *(B->table + (i / (index_t) 64));
  integerIndex = i % 64;
  maskNum = (index_t) pow(2.,(long) (integerIndex - 1));
  maskedInt = (integer & maskNum) >> (integerIndex - 1);
  return maskedInt;
}

index_t hash1(bloom_filter_t *B, key_t k){
  // auxilary call to first hash function
  index_t value;
  value = k;// B->size * B->count * *B->table;
  return ((index_t) hashUnsigned((unsigned int) value + 1)) % B->size;
}

index_t hash2(bloom_filter_t *B, key_t k){
  // auxilary call to second hash function
  index_t value;
  value = k; //B->size * B->count * *B->table;
  return ((index_t) hash32shift((int) value + 1)) % B->size;
}

void bloom_init(bloom_filter_t *B, index_t size_in_bits){
  // constructor for bloom_filter_t object instance
  int i,numInts;

  // initialize values
  B->size = size_in_bits;
  B->count = 0;
  numInts = (int) (size_in_bits / (index_t) 64) + 1;

  // malloc storage and set all bits to zero
  B->table = malloc(numInts*sizeof(index_t));
  for ( i=0 ; i<numInts ; i++ ){
    *(B->table+i) = 0;
  }
  return;
}

void bloom_destroy(bloom_filter_t *B){
  // free the table, leaving it as an uninitialized table.
  free(B->table);
  B->size = 0;
  B->count = 0;
  return;
}


int bloom_check(bloom_filter_t *B, key_t k){
  index_t i,hash,value;
  value = 1;
  for ( i=0 ; i<N_HASHES ; i++ ){
    hash = (hash1(B,k) + i * hash2(B,k)) % B->size;
    // check that all bits are all set
    value = value & get_bit(B,hash);
  }
  if (value == 1){
    return 1;
  }
  else {
    return 0;
  }
}

void bloom_add(bloom_filter_t *B, key_t k){
  // compute bits to add
  index_t i,hash;
  for ( i=0 ; i<N_HASHES ; i++ ){
    hash = (hash1(B,k) + i * hash2(B,k)) % B->size;
    // add the bits
    if (!get_bit(B,hash)){
      set_bit(B,hash);
      B->count = B->count + 1;
    }
  }
  return;
}

int* random_int_array(int N){
  int Nmax = 1000000;
  int* array = malloc(N*sizeof(int));
  int i;
  for ( i=0 ; i<N ; i++ ){
    *(array+i) = rand() % Nmax;
    // printf("%d\n",*(array+i));
  }
  return array;
}

int experiment(int* array1, int* array2){
  bloom_filter_t* filter = malloc(sizeof(bloom_filter_t));
  bloom_init(filter,1000);

  // add all elements of first array in
  int i;
  int n = 0;
  for ( i=0; i<100; i++ ){
    bloom_add(filter, (index_t) *(array1+i));
  }
  printf("%d\n",(int) filter->count);
  for ( i=0; i<100; i++ ){
    n = n + bloom_check(filter, (index_t) *(array2+i));
  }
  printf("%d\n",n);
  free(filter);
  return 1;
}
