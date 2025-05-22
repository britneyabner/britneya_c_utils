#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "../Inc/Queue.h"

struct Queue_Node {
    void *Data;
    size_t Data_Size;
    struct Queue_Node *Next;
};

struct Queue {
    struct Queue_Node *Head;
    struct Queue_Node *Tail;
};
