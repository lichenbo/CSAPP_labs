/*
Coursera HW/SW Interface
Lab 4 - Mystery Caches

Mystery Cache Geometries (for you to keep notes):
mystery0:
    block size = 64
    cache size = 4096
    associativity = 32
mystery1:
    block size = 8
    cache size = 8192
    associativity = 8
mystery2:
    block size = 32
    cache size = 32768
    associativity = 2
mystery3:
    block size = 16
    cache size = 4096
    associativity = 1
*/

#include <stdlib.h>
#include <stdio.h>
#include "mystery-cache.h"

/*
 * NOTE: When using access_cache() you do not need to provide a "real"
 * memory addresses. You can use any convenient integer value as a
 * memory address, you should not be able to cause a segmentation
 * fault by providing a memory address out of your programs address
 * space as the argument to access_cache.
 */

/*
   Returns the size (in B) of each block in the cache.
*/
int get_block_size(void) {
  access_cache(0x0);
  int iter = 1;
  while(access_cache(iter) == TRUE) {
    iter++;
  }
  flush_cache();
  return iter;
}

/*
   Returns the size (in B) of the cache.
*/
int get_cache_size(int size) {
  flush_cache();
  addr_t addr;
  for (addr = 0; ; addr += size) {
    addr_t addr_temp;
    access_cache(addr);
    for (addr_temp = 0; addr_temp <= addr; addr_temp+=size) {
      bool_t access_result = access_cache(addr_temp);
      if (access_result == FALSE) {
        return addr;
      }
    }
  }
}

/*
   Returns the associativity of the cache.
*/
int get_cache_assoc(int size) {
  addr_t addr,addr_temp;
  for(addr = 0;1; addr+=size){
    access_cache(addr);
    for(addr_temp = 0;addr_temp <= addr;addr_temp+=size){
      if(access_cache(addr_temp)==FALSE){
        return addr/size;
      }
    }
  }
  
  return -1;
}

//// DO NOT CHANGE ANYTHING BELOW THIS POINT
int main(void) {
  int size;
  int assoc;
  int block_size;

  /* The cache needs to be initialized, but the parameters will be
     ignored by the mystery caches, as they are hard coded.  You can
     test your geometry paramter discovery routines by calling
     cache_init() w/ your own size and block size values. */
  cache_init(0,0);

  block_size=get_block_size();
  size=get_cache_size(block_size);
  assoc=get_cache_assoc(size);

  printf("Cache block size: %d bytes\n", block_size);
  printf("Cache size: %d bytes\n", size);
  printf("Cache associativity: %d\n", assoc);

  return EXIT_SUCCESS;
}
