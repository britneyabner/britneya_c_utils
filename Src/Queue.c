#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../Inc/Queue.h"

struct Queue_Node {
    void *Data;
    size_t Data_Size;
    struct Queue_Node *Next;
};

struct Queue {
    struct Queue_Node *Head;
    struct Queue_Node *Tail;
    size_t Length;
};

Queue_t Queue_Create(void) {
    Queue_t queue = (Queue_t)malloc(sizeof(struct Queue));

    if(queue == NULL) {
        return NULL;
    }

    queue->Head = NULL;
    queue->Tail = NULL;
    queue->Length = 0;

    return queue;
}

Queue_Result_t Queue_Push(Queue_t queue, void *data, size_t data_size) {
    struct Queue_Node *node =
        (struct Queue_Node *)malloc(sizeof(struct Queue_Node));
    if(node == NULL) {
        return eQUEUE_RESULT_ERROR;
    }

    node->Data = malloc(data_size);
    if(node->Data == NULL) {
        return eQUEUE_RESULT_ERROR;
    }
    memcpy(node->Data, data, data_size);
    node->Data_Size = data_size;
    node->Next = NULL;

    if(queue->Length == 0) {
        queue->Head = node;
        queue->Tail = node;
    }
    else {
        queue->Tail->Next = node;
        queue->Tail = queue->Tail->Next; 
    }

    queue->Length++;

    return eQUEUE_RESULT_OK;
}

size_t Queue_Pop(Queue_t queue, void* output) {
    if(queue->Length == 0) {
        return 0;
    }

    struct Queue_Node *node = queue->Head;
    memcpy(output, node->Data, node->Data_Size);

    queue->Head = queue->Head->Next;

    size_t data_size = node->Data_Size;
    free(node->Data);
    free(node);

    queue->Length--;

    return data_size;
}

size_t Queue_Peek(Queue_t queue, void *output) {
    if(queue->Length == 0) {
        return 0;
    }

    memcpy(output, queue->Head->Data, queue->Head->Data_Size);

    return queue->Head->Data_Size;
}

size_t Queue_Get_Length(Queue_t queue) {
    return queue->Length;
}

bool Queue_Is_Empty(Queue_t queue) {
    return queue->Length == 0;
}
