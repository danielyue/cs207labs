/*
typedef uint64_t index_t;
typedef uint64_t key_t;
typedef struct {
  index_t size; // in bits
  index_t count; // in bits
  index_t *table;
} bloom_filter_t;
*/
#include "bloom.h"

int main(void){
  bloom_filter_t *filter;

  filter->size = 1000;
  filter->count = 1000;
  index_t htable = 1000;
  filter->table = &htable;
  key_t key;

  key_t i;
  index_t N = 1000;
  for (i=0;i<N;i++){
    key = 2414*i+50234;
    printf("%d\n\n",(int) hash1(filter,key));
  }
  return 1;
}
