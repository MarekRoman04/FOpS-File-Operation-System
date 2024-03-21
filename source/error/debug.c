#include "../../master_header.h"

void print_found_data(struct data *input_data, struct data *parameter_data)
{
    printf("Input data found: %d\n", input_data->data_count);
    printf("Length of data:\n");
    for (int i = 0; i < input_data->data_count; ++i)
        printf("%s: %d\n", input_data->data_paths[i], input_data->data_lengths[i]);
    printf("\n");
    // printf("Data:\n");
    // for (int i = 0; i < input_data->data_count; ++i)
    //     printf("%s\n", input_data->data[i]);
    // printf("\n");

    printf("Parameter data found: %d\n", parameter_data->data_count);
    printf("Length of data:\n");
    for (int i = 0; i < parameter_data->data_count; ++i)
        printf("%s: %d\n", parameter_data->data_paths[i], parameter_data->data_lengths[i]);
    printf("\n");
    // printf("Data:\n");
    // for (int i = 0; i < parameter_data->data_count; ++i)
    //     printf("%s\n", parameter_data->data[i]);
    // printf("\n");
}

void print_f_found_data(struct data *input_data, struct data *parameter_data)
{
    printf("Input data found: %d\n", input_data->data_count);
    printf("Length of data:\n");
    for (int i = 0; i < input_data->data_count; ++i)
        printf("%s: %d\n", input_data->data_paths[i], input_data->data_lengths[i]);
    printf("\n");
    // printf("Data:\n");
    // for (int i = 0; i < input_data->data_count; ++i)
    //     printf("%s\n", input_data->data[i]);
    // printf("\n");

    printf("Parameter data found: %d\n", parameter_data->data_count);
    // printf("Data:\n");
    // for (int i = 0; i < parameter_data->data_count; ++i)
    //     printf("%s\n", parameter_data->data[i]);
    // printf("\n");
}

void print_string_data(struct data *data)
{
    printf("String data: %d\n", data->data_count);
    printf("Data lengths: ");
    for (int i = 0; i < data->data_count; ++i)
        printf("%ld ", data->data_lengths[i]);
    printf("\nData: \n");
    for (int i = 0; i < data->data_count; ++i)
        printf("%s ", data->data[i]);
    printf("\n");
}

void print_args(struct args *input_args, struct args *parameter_args, char operation[5])
{
    printf("Input args: %d\n", input_args->args_len);
    printf("Args: ");
    for (int i = 0; i < input_args->args_len; ++i)
        printf("%s ", input_args->args[i]);
    printf("\n");

    printf("Operation: %s", operation);
    printf("\n");

    printf("Parameter args: %d\n", parameter_args->args_len);
    printf("Args: ");
    for (int i = 0; i < parameter_args->args_len; ++i)
        printf("%s ", parameter_args->args[i]);
    printf("\n\n");
}

void print_found_files(struct files *files)
{
    printf("Found files: %d\n", files->file_count);
    for (int i = 0; i < files->file_count; ++i)
        printf("%s ", files->file_paths[i]);
    printf("\n\n");
}

void print_input_data(struct data *data)
{
    printf("Input data found: %d\n", data->data_count);
    printf("Length of data:\n");
    for (int i = 0; i < data->data_count; ++i)
        printf("%s: %d\n", data->data_paths[i], data->data_lengths[i]);
    printf("\n");
    // printf("Data:\n");
    // for (int i = 0; i < data->data_count; ++i)
    //     printf("%s\n", data->data[i]);
    // printf("\n");
}