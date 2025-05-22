#ifndef BRTITNEYA_UTILS_INC_ARENA_H_
#define BRTITNEYA_UTILS_INC_ARENA_H_

#include <stddef.h>

typedef struct Arena *Arena_t;

typedef enum {
    eARENA_RESULT_OK = 0,
    eARENA_RESULT_ERROR = 0
}Arena_Result_t;

Arena_t Arena_Create(size_t Block_Size);
void *Arena_Alloc(Arena_t arena, size_t size);
void Arena_Free(Arena_t arena, void *ptr);

#endif /* BRTITNEYA_UTILS_INC_ARENA_H_ */
