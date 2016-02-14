#include "bloom.h"

int main(void){
  // declare local variables
  bloom_filter_t *filter;

  // create a bloom filter
  filter = malloc(sizeof(bloom_filter_t));

  //-* showing that hash functions work
  // fill test constants 0, 1, 2, 3, 13, and 97
  key_t key;
  int TESTNUM = 6;
  key_t testNums[TESTNUM];
  testNums[0] = 0;
  testNums[1] = 1;
  testNums[2] = 2;
  testNums[3] = 3;
  testNums[4] = 13;
  testNums[5] = 97;

  // initialize the filter
  bloom_init(filter,100);

  // Example testing system
  int i;
  for (i=0;i<TESTNUM;i++){
    key = testNums[i];
    printf("%d\n\n",(int) hash1(filter,key));
  }
  //*/

  /* testing the init and destory filter methods
  bloom_init(filter, 45);
  printf("filter size = %d\n",(int) filter->size);
  bloom_destroy(filter);
  printf("filter size = %d\n",(int) filter->size);
  //*/

  /*testing for filter
    // smoke test
  bloom_init(filter,1000);
  int i;
  for ( i=1 ; i<71 ; i++ ){
    bloom_add(filter, (key_t) i);
  }
  printf("%d\n",(int) filter->count);
  //*/
  /*  // randomized testing
  int* array1 = random_int_array(100);
  int* array2 = random_int_array(100);

  // check that the arrays have different starting values
  // printf("%d\n",*array1);
  // printf("%d\n",*array2);

  int a = experiment(array1, array2);

  free(array1);
  free(array2);
  //*/

  free(filter);
  return 1;
}
