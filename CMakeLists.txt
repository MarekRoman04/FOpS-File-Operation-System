cmake_minimum_required(VERSION 3.20)
project(File-Operation-System C)

set(SOURCES
    main.c
    source/alloc/alloc.c
    source/args/args.c
    source/args/args_functions.c
    source/data/data.c
    source/data/file.c
    source/error/error.c
    source/error/debug.c
    )

set(HEADER_FILES
    master_header.h
    headers/alloc.h
    headers/args.h
    headers/data.h
    headers/error.h
    headers/file.h
    headers/structs.h
    )

include_directories(headers)

add_executable(fops ${SOURCES} ${HEADER_FILES})