#ifndef __MEM_POOL_H__
#define __MEM_POOL_H__

#define POOL_CHUNK_SIZE 64
#define POOL_CHUNK_NUM 128

//最小的unit
typedef struct _chunk{
    //struct _chunk *prev;  //TODO
    struct _chunk *next;
    char buf[POOL_CHUNK_SIZE];
}Chunk;

//一个block包括多个Chunk
typedef struct _block{
    unsigned int id;
    int chunk_num;
    int chunk_size;
    Chunk *free_list;
    //Chunk *alloc_list;  //TODO
    struct _block *next;
}Block;

typedef struct _memory_pool{
    unsigned int last_id;
    int block_num;
    struct _block *next;
}MemoryPool;

MemoryPool* mem_pool_create(int size);
void* mem_pool_alloc(MemoryPool* pool);
void mem_pool_free(MemoryPool* pool, void* memory);
void mem_pool_destroy(MemoryPool* pool);

#endif