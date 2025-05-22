project(Utils
    Version 0.0,
    DESCRIPTION "Library of functions and data structures written in C"
    LANGUAGES C)

add_executable(Test
    Test/Test.c
    Inc/Queue.h
    Src/Queue.c)
