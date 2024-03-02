#include "../../master_header.h"
#include "../../headers/alloc.h"
#include "../../headers/error.h"

void free_2d_array(void **arr, int e)
{
    for (int i = 0; i < e; i++)
        free(arr[i]); 
    free(arr);
}

void free_args(struct args *args)
{
    free_2d_array((void **)args->args, args->args_len);
}

void free_files(struct files *files)
{
    free(files->fp_arr);
    free_2d_array((void **)files->file_paths, files->file_count);
}

void free_data(struct data *data)
{
    free_2d_array((void **)data->data, data->data_count);
    free_2d_array((void **)data->data_paths, data->data_count);
    free(data->data_lengths);
}

void merge_data_struct(struct data *dest, struct data *source)
{
    int dest_length = dest->data_count;
    dest->data_count += source->data_count;
    dest->data = (char **)realloc(dest->data, sizeof(char *) * dest->data_count);
    if (dest->data == NULL)
        alloc_error("merge_data_struct realloc_data");
    dest->data_paths = (char **)(realloc(dest->data_paths, sizeof(char *) * dest->data_count));
    if (dest->data_paths == NULL)
        alloc_error("merge_data_struct realloc_data_paths");
    dest->data_lengths = (long *)realloc(dest->data_lengths, sizeof(long) * dest->data_count);
    if (dest->data_lengths == NULL)
        alloc_error("merge_data_struct realloc_data_lengths");

    for (int i = 0; i < source->data_count; ++i)
    {
        dest->data[i + dest_length] = (char *)malloc(strlen(source->data[i]));
        if (dest->data[i] == NULL)
            alloc_2d_error(i + dest_length, "merge_data_struct data");
        strcpy(dest->data[i + dest_length], source->data[i]);

        dest->data_paths[i + dest_length] = (char *)malloc(strlen(source->data_paths[i]));
        if (dest->data_paths[i + dest_length] == NULL)
            alloc_2d_error(i + dest_length, "merge_data_struct data_paths");
        strcpy(dest->data_paths[i + dest_length], source->data_paths[i]);

        dest->data_lengths[i + dest_length] = source->data_lengths[i];
    }
}