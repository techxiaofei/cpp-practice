#include <stdio.h>
#include <stdlib.h>
#include "memory_pool.h"

/*
* TODO,size读的define
*/
MemoryPool* mem_pool_create(int size){
    MemoryPool* mp = (MemoryPool*)malloc(sizeof(MemoryPool));
    if (!mp){
        return NULL;
    }
    mp->block_num = 1;
    mp->last_id = 0;
    for (int i = 0; i < mp->block_num; i++){
        Block* block_prev = mp->next;
        mp->next = (Block*)malloc(sizeof(Block));
        if (!mp->next){
            return NULL;
        }
        mp->next->next = block_prev;
        mp->next->id = mp->last_id++;
        mp->next->chunk_num = POOL_CHUNK_NUM;
        mp->next->chunk_size = POOL_CHUNK_SIZE;
        for (int j = 0; j < mp->next->chunk_num; j++){
            Chunk* chunk_prev = mp->next->free_list;
            mp->next->free_list = (Chunk*)malloc(sizeof(Chunk));
            mp->next->free_list->next = chunk_prev;
        }
    }
   
    return mp;
}

/*
* fix，return chunk->buffer;
*/
void* mem_pool_alloc(MemoryPool* pool){
    Block *block = pool->next;
    Chunk *ret = block->free_list;
    if (ret){
        block->free_list = block->free_list->next;
    }
    printf("mem_pool_alloc %p,%p\n",ret,ret->buf);
    return (char*)ret+sizeof(struct Chunk*);
}

void mem_pool_free(MemoryPool* pool, void* memory){
    Chunk *old = pool->next->free_list;
    Chunk* now = (Chunk*)(memory - sizeof(struct Chunk*));
    printf("mem_pool_free %p\n",now);
    pool->next->free_list = now;
    pool->next->free_list->next = old;
}

void mem_pool_destroy(MemoryPool* pool){

}