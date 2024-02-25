#include "../../master_header.h"
#include "../../headers/data.h"
#include "../../headers/file.h"
#include "../../headers/alloc.h"
#include "../../headers/error.h"

extern struct args input_args;
extern struct args parameter_args;

static char **copy_file_path(char **path, int file_count)
{
    char **path_copy = (char **)malloc(sizeof(char *) * file_count);
    if (path_copy == NULL)
        alloc_error("copy_file_path");
    for (int i = 0; i < file_count; ++i)
    {
        path_copy[i] = (char *)malloc(strlen(path[i]));
        if (path_copy[i] == NULL)
            alloc_2d_error(i, "copy_file_path");
        strcpy(path_copy[i], path[i]);
    }
    return path_copy;
}

void get_input_data(struct data *data)
{
    struct files input_files;
    input_files.get_files = &get_input_files;
    input_files.get_files(&input_files);

    if (DEBUG)
    {
        printf("Found files: %d\n", input_files.file_count);
        for (int i = 0; i < input_files.file_count; ++i)
            printf("%s ", input_files.file_paths[i]);
        printf("\n");
    }
    data->data_count = input_files.file_count;
    data->data_lengths = get_file_lengths(input_files.fp_arr, input_files.file_count);
    data->data = get_file_data(input_files.fp_arr, data->data_count, data->data_lengths);
    data->data_paths = copy_file_path(input_files.file_paths, input_files.file_count);
    free_files(&input_files);
}

void get_string_data(struct data *data)
{
    int found_strings = 0;

    data->data = (char **)malloc(sizeof(char *) * parameter_args.args_len);
    if (data->data == NULL)
        alloc_error("get_string_data data");

    data->data_paths = (char **)malloc(sizeof(char *) * parameter_args.args_len);
    if (data->data_paths == NULL)
        alloc_error("get_string_data data_paths");

    for (int i = 0; i < parameter_args.args_len; ++i)
    {
        if (parameter_args.args[i][0] == '\'')
        {
            data->data[found_strings] = (char *)malloc(strlen(parameter_args.args[i]) - 2);
            if (data->data[found_strings] == NULL)
                alloc_2d_error(found_strings, "get_string_data data");
            strncpy(data->data[found_strings], parameter_args.args[i] + 1, strlen(parameter_args.args[i]) - 1);
            data->data[found_strings][strlen(parameter_args.args[i]) - 2] = '\0';
            data->data_paths[found_strings] = (char *)malloc(strlen(parameter_args.args[i]));
            if (data->data_paths == NULL)
                alloc_2d_error(found_strings, "get_string_data data_paths");
            strcpy(data->data_paths[found_strings], parameter_args.args[i]);

            ++found_strings;
        }
    }
    data->data_count = found_strings;
    data->data = (char **)realloc(data->data, sizeof(char *) * found_strings);
    data->data_paths = (char **)realloc(data->data_paths, sizeof(char *) * found_strings);
}

long *get_string_data_lengths(char **data, int data_count)
{
    long *data_lengths = (long *)malloc(sizeof(long) * data_count);
    if (data_lengths == NULL)
        alloc_error("get_string_data_length");

    for (int i = 0; i < data_count; ++i)
        data_lengths[i] = strlen(data[i]);

    return data_lengths;
}

void get_fs_parameter_data(struct data *data)
{
    struct files parameter_files;
    parameter_files.get_files = &get_parameter_files;
    parameter_files.get_files(&parameter_files);

    data->data_count = parameter_files.file_count;
    data->data_lengths = get_file_lengths(parameter_files.fp_arr, parameter_files.file_count);
    data->data = get_file_data(parameter_files.fp_arr, data->data_count, data->data_lengths);
    data->data_paths = copy_file_path(parameter_files.file_paths, parameter_files.file_count);

    free_files(&parameter_files);

    struct data string_data;
    string_data.get_data = &get_string_data;
    string_data.get_data(&string_data);
    string_data.data_lengths = get_string_data_lengths(string_data.data, string_data.data_count);

    if (DEBUG)
    {
        printf("String data: %d\n", string_data.data_count);
        printf("Data lengths: ");
        for (int i = 0; i < string_data.data_count; ++i)
            printf("%ld ", string_data.data_lengths[i]);
        printf("\nData: \n");
        for (int i = 0; i < string_data.data_count; ++i)
            printf("%s", string_data.data[i]);
        printf("\n");
    }
    
    if (!data->data_count && !string_data.data_count)
        error_missing_parameter();
    merge_data_struct(data, &string_data);

    free_data(&string_data);
}