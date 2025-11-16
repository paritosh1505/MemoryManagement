#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#define ARENA_SIZE 4096u
#define ALIGNMENT 8u

typedef struct {
  unsigned char *base;
  size_t offset;
  size_t capacity;

} Arena;
typedef struct {
  unsigned char *ptr;
  size_t size;
} Block;

size_t fix_alignment(size_t byteVal,size_t alignment){
  size_t masking = alignment - 1u;
  return (byteVal + masking) & ~masking;

}

void Arena_init(Arena *a, void *mem, size_t cap) {
  if(!a || mem==0||cap==0){
    fprintf(stderr, "Empty Arena initialized.Exit...");
    exit(1);
  
  }
  a->base = mem;
  a->capacity = cap;
  a->offset = 0;
}
size_t resize_block(Block **block,size_t indexval,size_t block_cap){
  if(indexval>=block_cap){
    block_cap=2*block_cap;
    void *newBlock = realloc(*block, block_cap * sizeof(Block));
    if(!newBlock){
      perror("realloc fail");
      exit(1);
    }
    *block=newBlock;
    
  }
  return block_cap;
}
void *Arena_alloc(Arena *a, size_t size) {
    size_t alignedByte = fix_alignment(size, ALIGNMENT);
    if (a->offset>a->capacity||a->capacity-a->offset<alignedByte)return NULL;
    void *p=a->base+a->offset;
    a->offset=a->offset+alignedByte;
    return p;
}
void Arena_reset(Arena *a) { 
  a->offset = 0; 
}
void Arena_destroy(Arena *a){
  free(a->base);
}
int main() {
  srand((unsigned)time(NULL));
  Arena arena;
  size_t blockSize = 1;
  Block *block = malloc(blockSize * sizeof(Block));
  if(!block) exit(1);
  size_t indexval=0;
  void *allocation = malloc(ARENA_SIZE);
  if(!allocation) exit(1);
  Arena_init(&arena, allocation, ARENA_SIZE);
  
  while(true){
    size_t byteAsk = 1 +(rand()%256);
    void *blckpt = Arena_alloc(&arena, byteAsk);
    if(blckpt==NULL){
      break;
    }
    blockSize=resize_block(&block,indexval,blockSize);

    block[indexval].ptr=blckpt;
    block[indexval].size=byteAsk;
   
    memset(block[indexval].ptr, (unsigned char)indexval, block[indexval].size);

    
    printf("Address of pointer is %p\n",block[indexval].ptr);
    printf("Size of pointer is %zu\n",arena.offset);
    indexval++;
  }
  Arena_reset(&arena);
  printf("**************************After Calling Arean reset***********************\n");
  blockSize=1;
  for(size_t i=0;i<indexval;i++){
    
    void *arena_re = Arena_alloc(&arena, block[i].size);
    if(!arena_re)break;
    if(block[i].ptr!=arena_re){printf("****Address Mismatch****");exit(1);}
    else{printf("Address match\n");}
    memset(arena_re, (unsigned char)i, block[i].size);
    unsigned char* bp = (unsigned char*)arena_re;
    for(size_t p=0;p<block[i].size;p++){
      if(bp[p]!=(unsigned char)i){
        printf("byte value and pattern value %d %zu\n ",bp[i],i);

        perror("Byte not match");
        exit(1);
      }
    }
    
  }
  free(block);
  Arena_destroy(&arena);

}
