#include "../../master_header.h"
#include "../../headers/error.h"

void alloc_error(char *function)
{
    printf("Memory allocation in %s failed!", function);
    exit(EXIT_FAILURE);
}

void alloc_2d_error(int e, char *function)
{
    printf("Memory allocation of %d element in %s failed!", e, function);
    exit(EXIT_FAILURE);
}

void error()
{
    printf("Something went wrong!");
    exit(EXIT_FAILURE);
}

void error_multiple_operations()
{
    printf("Error multiple operations given, expects only 1 operation!\n");
    exit(EXIT_FAILURE);
}

void error_missing_operation()
{
    printf("Error no operation given!\n");
    exit(EXIT_FAILURE);
}

void error_missing_input()
{
    printf("Error no input files given!\n");
    exit(EXIT_FAILURE);
}

void error_missing_parameter()
{
    printf("Error no parameter given!\n");
    exit(EXIT_FAILURE);
}

void error_invalid_operation()
{
    printf("Error invalid operation given!\n");
    exit(EXIT_FAILURE);
}

void error_missing_input_files()
{
    printf("Error no input files found!");
    exit(EXIT_FAILURE);
}