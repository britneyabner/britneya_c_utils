#ifndef BRITNEYA_UTILS_INC_QUEUE_H_
#define BRITNEYA_UTILS_INC_QUEUE_H_

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

typedef struct Queue *Queue_t;

typedef enum {
    eQUEUE_RESULT_OK = 0,
    eQUEUE_RESULT_ERROR = 1
}Queue_Result_t;

Queue_t Queue_Create(void);
Queue_Result_t Queue_Push(Queue_t queue, void *data, size_t data_size);
size_t Queue_Pop(Queue_t queue, void* output);
size_t Queue_Peek(Queue_t queue, void *output);
size_t Queue_Get_Length(Queue_t queue);
bool Queue_Is_Empty(Queue_t queue);

#endif /* BRITNEYA_UTILS_INC_QUEUE_H_ */
