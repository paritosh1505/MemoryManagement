#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdint.h>
typedef struct 
{
    uint8_t *ptrval;
    size_t sizeval;
}Block;
void fisher_shuffle(int blockSize,int *arrval){
   for(int i=0;i<blockSize;i++)
    arrval[i]=i;
    for(int j =blockSize-1;j>0;j--){
        int index = rand()%(j+1);
        int val = arrval[index];
        arrval[index]=arrval[j];
        arrval[j] = val;
    }
}

void free_ptr(Block *block){
free(block->ptrval);
block->ptrval=NULL;
block->sizeval=0;
}
int main(){
    srand((unsigned)time(NULL));  
    int blockSize=10;
    int arrVal[blockSize];

    Block block[blockSize];
    memset(block,0,sizeof(block));
    for(int i=0;i<blockSize;i++){
        int randSize = rand()%256;
        block[i].ptrval = malloc(randSize);
        block[i].sizeval=randSize;
        if (block[i].ptrval==NULL){
            printf("Value is out of memory hence closing it");
            free_ptr(&block[i]);
            return 0;
        }
        memset(block[i].ptrval,i,block[i].sizeval);
    }
    fisher_shuffle(blockSize,arrVal);
    
    //free the block ranadomly

    for(int i =0;i<blockSize/2;i++){
    free_ptr(&block[arrVal[i]]);
    }

    for(int i=0;i<blockSize/2;i++){
        int randSize = rand()%256;
        block[arrVal[i]].ptrval = malloc(randSize);
        block[arrVal[i]].sizeval=randSize;
        memset(block[arrVal[i]].ptrval,arrVal[i],block[arrVal[i]].sizeval);
    }
    for(int i=0;i<blockSize;i++){
        free_ptr(&block[i]);
    }
    
}

