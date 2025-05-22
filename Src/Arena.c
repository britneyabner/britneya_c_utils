#include <stddef.h>
#include <stdlib.h>
#include "../Inc/Arena.h"

struct Arena_Region {
    struct Arena_Region *Next;
    size_t Size;
    void *Start;
    void *End;
};

struct Arena {
    void *Start;
    void *End;
    size_t Block_Size;
    size_t Total_Size;
    size_t Current_Size;
    struct Arena_Region *Head;
    struct Arena_Region *Tail;
    size_t Region_Count;
};

Arena_t Arena_Create(size_t Block_Size) {
    Arena_t arena = (Arena_t)malloc(sizeof(struct Arena));
    if(arena == NULL) {
        return NULL;
    }

    arena->Start = malloc(Block_Size);
    if(arena->Start == NULL) {
        free(arena);

        return NULL;
    }

    arena->Block_Size = Block_Size;
    arena->End = arena->Start + Block_Size;
    arena->Total_Size = Block_Size;
    arena->Current_Size = 0;

    arena->Head = NULL;
    arena->Tail = NULL;
    arena->Region_Count = 0;

    return arena;
}

void Arena_Destroy(Arena_t arena) {

}

void *Arena_Alloc(Arena_t arena, size_t size) {
    size_t remaining_size = arena->Total_Size - arena->Current_Size;
    if(remaining_size < size) {
        arena->End = malloc(arena->Block_Size);
        if(arena->End == NULL) {
            return NULL;
        }

        arena->Total_Size += arena->Block_Size;
        arena->End += arena->Block_Size;

        // Just allocate the rest of the remaining block as padding for now
        // I'll deal with the issue of multiple blocks later
        (void)Arena_Alloc(arena, remaining_size);
    }

    struct Arena_Region *new_region =
        (struct Arena_Region *)malloc(sizeof(struct Arena_Region));
    if(new_region == NULL) {
        return NULL;
    }

    if(arena->Region_Count == 0) {
        new_region->Start = arena->Start;
        arena->Head = new_region;
    }
    else {
        new_region->Start = arena->Tail->End;
        arena->Tail->Next = new_region;
    }

    new_region->Next = NULL;
    new_region->End = new_region->Start + size;
    new_region->Size = size;

    arena->Tail = new_region;
    arena->Current_Size += size;
    arena->Region_Count++;

    return new_region->Start;
}

void Arena_Free(Arena_t arena, void *ptr) {
}
