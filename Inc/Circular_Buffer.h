#ifndef BRITNEYA_UTILS_CIRCULAR_BUFFER_H_
#define BRITNEYA_UTILS_CIRCULAR_BUFFER_H_

#include <stdint.h>
#include <stddef.h>

typedef struct Circular_Buffer *Circular_Buffer_t;

typedef enum {
    eCIRCULAR_BUFFER_RESULT_OK = 0,
    eCIRCULAR_BUFFER_RESULT_ERROR = 1
}Circular_Buffer_Result_t;

Circular_Buffer_t Circular_Buffer_Create(size_t Max_Length);
Circular_Buffer_Result_t Circular_Buffer_Push(Circular_Buffer_t cbuffer,
                                              uint8_t byte);
Circular_Buffer_Result_t Circular_Buffer_Pop(Circular_Buffer_t cbuffer,
                                             uint8_t *output_byte);
size_t Circular_Buffer_Get_Length(Circular_Buffer_t cbuffer);
 
 

#endif /* BRITNEYA_UTILS_CIRCULAR_BUFFER_H_ */
