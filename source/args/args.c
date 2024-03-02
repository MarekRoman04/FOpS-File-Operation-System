#include "../../master_header.h"
#include "../../headers/args.h"
#include "../../headers/error.h"
#include "../../headers/alloc.h"
#include "../../headers/data.h"

struct args input_args;
struct args parameter_args;
char operation[5];

void get_args(struct args *args, int start_index, int end_index, char *argv[])
{
    args->args_len = end_index - start_index;
    args->args = (char **)malloc(args->args_len * sizeof(char *));
    if (args->args == NULL)
        alloc_error("get_args");

    for (int i = 0; i < end_index - start_index; i++)
    {
        args->args[i] = (char *)malloc(strlen(argv[i + start_index]));
        if (args->args[i] == NULL)
            alloc_2d_error(i, "get_args");
        strcpy(args->args[i], argv[i + start_index]);
    }
}

void process_args(int argc, char *argv[])
{
    int operation_index;
    bool got_operation = false;

    for (int i = 0; i < argc; ++i)
    {
        if (argv[i][0] == '-')
        {
            if (!got_operation)
            {
                input_args.get_args = &get_args;
                input_args.get_args(&input_args, 1, i, argv);
            }
            else
                error_multiple_operations();
            got_operation = true;
            operation_index = i;
            if (strlen(argv[operation_index]) > 6)
                error_invalid_operation();
            strcpy(operation, argv[operation_index]);
        }
    }

    if (!got_operation)
        error_missing_operation();

    if (input_args.args_len == 0)
        error_missing_input();

    if (operation_index == argc - 1)
        error_missing_parameter();

    parameter_args.get_args = &get_args;
    parameter_args.get_args(&parameter_args, operation_index + 1, argc, argv);

    if (DEBUG)
        print_args(&input_args, &parameter_args, operation);
}

void start_operation()
{
    struct data input_data;
    input_data.get_data = &get_input_data;
    input_data.get_data(&input_data);

    free_args(&input_args);

    struct data parameter_data;

    if (!strcmp(operation, "-f"))
        find_words(&input_data, &parameter_data);
    else if (!strcmp(operation, "-fAll"))
        find_all_words(&input_data, &parameter_data);
    else if (!strcmp(operation, "-fc"))
        find_words_count(&input_data, &parameter_data);    
    else if (!strcmp(operation, "-fs"))
        find_string(&input_data, &parameter_data);
    else if (!strcmp(operation, "-fsAll"))
        find_all_strings(&input_data, &parameter_data);
    else
        error_invalid_operation();
}