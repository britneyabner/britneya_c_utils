
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include "../Inc/Queue.h"
#include "../Inc/Circular_Buffer.h"
#include "../Inc/Arena.h"

void Test_Queue(void);
void Test_Circular_Buffer(void);
void Test_Arena(void);

int main() {
    Test_Queue();
    Test_Circular_Buffer();
    Test_Arena();

    return 0;
}

void Test_Queue(void) {
    Queue_t queue = Queue_Create();
    assert(queue != NULL);
    assert(Queue_Is_Empty(queue));

    char input[32];
    for(int i = 0; i < 100; i++) {
        size_t queue_length = Queue_Get_Length(queue);
        assert(queue_length == i);
        size_t input_length = (size_t)sprintf(input, "input: %d\r\n", i);
        Queue_Result_t push_result =
            Queue_Push(queue, (void *)input, input_length + 1);
        assert(push_result == eQUEUE_RESULT_OK);
        queue_length = Queue_Get_Length(queue);
        assert(queue_length == i + 1);
    }

    char output[32];
    char test_str[32];
    for(int i = 0; i < 100; i++) {
        size_t queue_length = Queue_Get_Length(queue);
        assert(queue_length == 100 - i);
        size_t test_str_length = (size_t)sprintf(test_str, "input: %d\r\n", i);
        size_t output_length = Queue_Pop(queue, (void *)output);
        assert(output_length == test_str_length + 1);
        assert(strcmp(output, test_str) == 0);
        queue_length = Queue_Get_Length(queue);
        assert(queue_length == 100 - i - 1);
    }

    assert(Queue_Is_Empty(queue));
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

    for(int i = 0; i < 100; i++) {
        size_t current_length = Circular_Buffer_Get_Length(cbuffer);
        assert(current_length == i);
        Circular_Buffer_Result_t push_result =
            Circular_Buffer_Push(cbuffer, (uint8_t)i);
        assert(push_result == eCIRCULAR_BUFFER_RESULT_OK);
        current_length = Circular_Buffer_Get_Length(cbuffer);
        assert(current_length == i + 1);
    }
}

void Test_Arena(void) {
    Arena_t arena = Arena_Create(1024);
    char *buffer_one = (char *)Arena_Alloc(arena, 64);
    strcpy(buffer_one, "one");
    assert(strcmp(buffer_one, "one") == 0);
    char *buffer_two = (char *)Arena_Alloc(arena, 950);
    strcpy(buffer_two, "two");
    assert(strcmp(buffer_two, "two") == 0);
    char *buffer_three = (char *)Arena_Alloc(arena, 128);
    strcpy(buffer_three, "three");
    assert(strcmp(buffer_three, "three") == 0);
    assert(strcmp(buffer_one, "one") == 0);
    assert(strcmp(buffer_two, "two") == 0);
}
