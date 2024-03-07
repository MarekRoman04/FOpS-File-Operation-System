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
        print_found_files(&input_files);

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
    data->data_lengths = NULL;
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

void get_f_parameter_data(struct data *data)
{
    struct files parameter_files;
    parameter_files.get_files = &get_parameter_files;
    parameter_files.get_files(&parameter_files);
    if (parameter_files.file_count > 1)
        printf("-f takes only 1 parameter file, ignoring other files!\n");

    data->data_count = 0;
    if (parameter_files.file_count)
        get_f_parameter_file_data(data, parameter_files.fp_arr[0]);

    if (!data->data_count)
    {
        data->get_data = &get_string_data;
        data->get_data(data);
    }
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
        print_string_data(&string_data);

    if (!data->data_count && !string_data.data_count)
        error_missing_parameter();
    merge_data_struct(data, &string_data);
}

void get_fsl_parameter_data(struct data *data){
    struct files parameter_files;
    parameter_files.get_files = &get_parameter_files;
    parameter_files.get_files(&parameter_files);
    
    if (parameter_files.file_count > 1)
        printf("-fsl takes only 1 parameter file, ignoring other files!\n");
    if (!parameter_files.file_count)
        error_missing_parameter();
    
    get_fsl_parameter_file_data(data, parameter_files.fp_arr[0]);
}