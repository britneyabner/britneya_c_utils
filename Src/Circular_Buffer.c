#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include "../Inc/Circular_Buffer.h"

struct Circular_Buffer {
    uint8_t *Buffer_Start;
    uint8_t *Buffer_End;
    size_t Max_Length;
    size_t Current_Length;
    uint8_t *Head;
    uint8_t *Tail;
};

Circular_Buffer_t Circular_Buffer_Create(size_t Max_Length) {
    Circular_Buffer_t cbuffer =
        (Circular_Buffer_t)malloc(sizeof(struct Circular_Buffer));
    if(cbuffer == NULL) {
        return NULL;
    }

    cbuffer->Buffer_Start = (uint8_t *)malloc(Max_Length);
    if(cbuffer->Buffer_Start == NULL) {
        free(cbuffer);

        return NULL;
    }

    cbuffer->Buffer_End = cbuffer->Buffer_Start + Max_Length;
    cbuffer->Max_Length = Max_Length;
    cbuffer->Current_Length = 0;
    cbuffer->Head = cbuffer->Buffer_Start;
    cbuffer->Tail = cbuffer->Buffer_Start;

    return cbuffer;
}

Circular_Buffer_Result_t Circular_Buffer_Push(Circular_Buffer_t cbuffer,
                                              uint8_t byte) {
    if(cbuffer->Current_Length == cbuffer->Max_Length) {
        // Buffer is full, can't push
        return eCIRCULAR_BUFFER_RESULT_ERROR;
    }

    memcpy(cbuffer->Head, &byte, 1);

    cbuffer->Head++;
    if(cbuffer->Head == cbuffer->Buffer_End) {
        // Reached the end of the buffer, go back to the start
        cbuffer->Head = cbuffer->Buffer_Start;
    }

    cbuffer->Current_Length++;

    return eCIRCULAR_BUFFER_RESULT_OK;
}

Circular_Buffer_Result_t Circular_Buffer_Pop(Circular_Buffer_t cbuffer,
                                             uint8_t *output_byte) {
    if(cbuffer->Current_Length == 0) {
        // Buffer is empty, nothing to pop
        return eCIRCULAR_BUFFER_RESULT_ERROR;
    }

    memcpy(output_byte, cbuffer->Tail, 1);

    cbuffer->Tail = cbuffer->Tail + 1;
    if(cbuffer->Tail == cbuffer->Buffer_End) {
        // Reached the end of the buffer, go back to the start
        cbuffer->Tail = cbuffer->Buffer_Start;
    }

    cbuffer->Current_Length--;

    return eCIRCULAR_BUFFER_RESULT_OK;
}

size_t Circular_Buffer_Get_Length(Circular_Buffer_t cbuffer) {
    return cbuffer->Current_Length;
}

bool Circular_Buffer_Is_Empty(Circular_Buffer_t cbuffer) {
    return cbuffer->Current_Length == 0;
}

bool Circular_Buffer_Is_Full(Circular_Buffer_t cbuffer) {
    return cbuffer->Current_Length == cbuffer->Max_Length;
}

