
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include "../Inc/Queue.h"
#include "../Inc/Circular_Buffer.h"

void Test_Queue(void);
void Test_Circular_Buffer(void);

int main() {
    Test_Queue();
    Test_Circular_Buffer();

    return 0;
}

void Test_Queue(void) {
}

void Test_Circular_Buffer(void) {
    Circular_Buffer_t cbuffer = Circular_Buffer_Create(100);
    assert(cbuffer != NULL);

    for(int i = 0; i < 100; i++) {
        size_t current_length = Circular_Buffer_Get_Length(cbuffer);
        assert(current_length == i);
        Circular_Buffer_Result_t push_result =
            Circular_Buffer_Push(cbuffer, (uint8_t)i);
        assert(push_result == eCIRCULAR_BUFFER_RESULT_OK);
        current_length = Circular_Buffer_Get_Length(cbuffer);
        assert(current_length == i + 1);
    }

    assert(Circular_Buffer_Push(cbuffer, 0) == eCIRCULAR_BUFFER_RESULT_ERROR);


    uint8_t output_byte;
    for(int i = 0; i < 100; i++) {
        size_t current_length = Circular_Buffer_Get_Length(cbuffer);
        assert(current_length == 100 - i);
        Circular_Buffer_Pop(cbuffer, &output_byte);
        assert(output_byte == i);
        current_length = Circular_Buffer_Get_Length(cbuffer);
        assert(current_length == 100 - i - 1);
    }

    assert(
        Circular_Buffer_Pop(cbuffer, &output_byte) ==
        eCIRCULAR_BUFFER_RESULT_ERROR);
}
