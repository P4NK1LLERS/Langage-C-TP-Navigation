cmake_minimum_required(VERSION 3.26)
project(TP_Navigation C)

set(CMAKE_C_STANDARD 11)

add_executable(TP_Navigation main.c
        history.c
        history.h)
