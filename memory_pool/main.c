#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "memory_pool.h"

int main(){
    MemoryPool* pool = mem_pool_create(POOL_CHUNK_SIZE);
    char* buffer = mem_pool_alloc(pool);
    char* buffer2 = mem_pool_alloc(pool);
    if (!buffer || !buffer){

    }

    strcpy(buffer,"abcdefgh\n");
    strcpy(buffer2,"abcdefghij\n");

    printf("%s",buffer);
    printf("%s",buffer2);

    mem_pool_free(pool, buffer);
    mem_pool_free(pool, buffer2);

    return 0;
}

//gcc -o test memory_pool.c main.c