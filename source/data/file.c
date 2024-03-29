#include "../../master_header.h"
#include "../../headers/error.h"
#include "../../headers/file.h"

extern struct args input_args;
extern struct args parameter_args;

void get_input_files(struct files *files)
{
    int found_files = 0;

    files->fp_arr = (FILE **)malloc(sizeof(FILE *) * input_args.args_len);
    if (files->fp_arr == NULL)
        alloc_error("get_input_files fp_arr");

    files->file_paths = (char **)malloc(sizeof(char *) * input_args.args_len);
    if (files->file_paths == NULL)
        alloc_error("get_input_files file_paths");

    for (int i = 0; i < input_args.args_len; ++i)
    {
        FILE *fp = fopen(input_args.args[i], "rb");
        if (fp == NULL)
        {
            printf("Error file: %s not found!\n", input_args.args[i]);
            continue;
        }

        files->fp_arr[found_files] = fp;

        files->file_paths[found_files] = (char *)malloc(strlen(input_args.args[i]));
        if (files->file_paths[found_files] == NULL)
            alloc_2d_error(found_files, "get_input_args file_paths");
        strcpy(files->file_paths[found_files], input_args.args[i]);

        ++found_files;
    }

    files->file_count = found_files;

    if (!files->file_count)
        error_missing_input_files();

    files->fp_arr = (FILE **)realloc(files->fp_arr, sizeof(FILE *) * found_files);
    if (files->fp_arr == NULL)
        alloc_error("get_input_files realloc_file_arr");
    files->file_paths = (char **)realloc(files->file_paths, sizeof(char *) * found_files);
    if (files->file_paths == NULL)
        alloc_error("get_input_files realloc_file_paths");
}

long *get_file_lengths(FILE **files, int file_count)
{
    long *file_length = (long *)malloc(sizeof(long) * file_count);
    if (file_length == NULL)
        alloc_error("get_file_length");

    for (int i = 0; i < file_count; ++i)
    {
        fseek(files[i], 0, SEEK_END);
        file_length[i] = ftell(files[i]);

        if (fseek(files[i], 0, SEEK_SET) < 0)
            error();
    }
    return file_length;
}

char **get_file_data(FILE **files, int file_count, long *file_length)
{
    char **file_data = (char **)malloc(sizeof(char *) * file_count);
    if (file_data == NULL)
        alloc_error("get_file_data");

    for (int i = 0; i < file_count; ++i)
    {
        file_data[i] = (char *)malloc(file_length[i]);
        if (file_data[i] == NULL)
            alloc_2d_error(i, "get_file_data");
        fread(file_data[i], file_length[i], 1, files[i]);
        file_data[i][file_length[i]] = '\0';
        fclose(files[i]);
    }
    return file_data;
}

void get_f_parameter_file_data(struct data *data, FILE *file)
{
    int word_count = 0;
    char word[100];

    while (fscanf(file, "%99s", word) != EOF)
        ++word_count;
    fseek(file, 0, SEEK_SET);

    data->data = (char **)malloc(sizeof(char *) * word_count);
    if (data->data == NULL)
        alloc_error("get_f_parameter_file_data realloc_file_data");

    for (int i = 0; fscanf(file, "%99s", word) != EOF; ++i)
    {

        data->data[i] = (char *)malloc(strlen(word));
        if (data->data[i] == NULL)
            alloc_2d_error(i, "get_f_parameter_file_data");
        strcpy(data->data[i], word);
    }

    data->data_count = word_count;
}

void get_fsl_parameter_file_data(struct data *data, FILE *fp)
{
    char line[1000];
    size_t line_count = 0;

    while (fgets(line, sizeof(line), fp))
        ++line_count;
    fseek(fp, 0, SEEK_SET);

    data->data_count = line_count;

    data->data = (char **)malloc(sizeof(char *) * line_count);
    if (data->data == NULL)
        alloc_error("get_fsl_parameter_data data");

    for (int i = 0; i < line_count; ++i)
    {
        fgets(line, sizeof(line), fp);
        size_t line_length = strlen(line) + 1;
        if (line[line_length - 1] == '\n')
        {
            if (line[line_length - 2] == '\r')
            {
                data->data[i] = (char *)malloc(line_length - 2);
                if (data->data[i] == NULL)
                    alloc_2d_error(i, "get_fsl_parameter_data data_data");
                strncpy(data->data[i], line, line_length - 3);
                data->data[i][line_length - 2] = '\0';
            }
            else
            {
                data->data[i] = (char *)malloc(line_length - 1);
                if (data->data[i] == NULL)
                    alloc_2d_error(i, "get_fsl_parameter_data data_data");
                strncpy(data->data[i], line, line_length - 1);
                data->data[i][line_length - 2] = '\0';
            }
        }
        else
        {
            data->data[i] = (char *)malloc(line_length);
            if (data->data[i] == NULL)
                alloc_2d_error(i, "get_fsl_parameter_data data_data");
            strcpy(data->data[i], line);
        }
    }
    fclose(fp);
}

void get_parameter_files(struct files *files)
{
    int found_files = 0;
    files->fp_arr = (FILE **)malloc(sizeof(FILE *) * parameter_args.args_len);
    if (files->fp_arr == NULL)
        alloc_error("get_parameter_files fp_arr");

    files->file_paths = (char **)malloc(sizeof(char *) * parameter_args.args_len);
    if (files->file_paths == NULL)
        alloc_error("get_parameter_args file_paths");

    for (int i = 0; i < parameter_args.args_len; ++i)
    {

        if (parameter_args.args[i][0] == '\'')
            continue;

        FILE *fp = fopen(parameter_args.args[i], "rb");
        if (fp == NULL)
        {
            printf("Error file: %s not found!\n", parameter_args.args[i]);
            continue;
        }

        files->fp_arr[found_files] = fp;

        files->file_paths[found_files] = (char *)malloc(strlen(parameter_args.args[i]));
        if (files->file_paths[found_files] == NULL)
            alloc_2d_error(found_files, "get_input_args file_paths");
        strcpy(files->file_paths[found_files], parameter_args.args[i]);

        ++found_files;
    }

    if (found_files)
    {
        files->fp_arr = (FILE **)realloc(files->fp_arr, sizeof(FILE *) * found_files);
        if (files->fp_arr == NULL)
            alloc_error("get_parameter_files realloc_fp_arr");
        files->file_paths = (char **)realloc(files->file_paths, sizeof(char *) * found_files);
        if (files->file_paths == NULL)
            alloc_error("get_parameter_files realloc_file_paths");
    }
    files->file_count = found_files;
}

void copy_data(struct data *data)
{
    for (int i = 0; i < parameter_args.args_len; ++i)
    {
        FILE *fp = fopen(parameter_args.args[i], "ab");
        if (fp == NULL)
            printf("Error opening/creating %s file.\n", parameter_args.args[i]);

        for (int j = 0; j < data->data_count; ++j)
        {
            fputc('\n', fp);
            fwrite(data->data[j], sizeof(char), data->data_lengths[j], fp);
        }

        fclose(fp);
    }
}

void merge_data(struct data *data)
{
    if (parameter_args.args_len > 1)
        printf("-m writes to only 1 file, other entered file paths being ignored!\n");

    FILE *fp = fopen(parameter_args.args[0], "wb");
    if (fp == NULL)
    {
        printf("Error creating file!");
        exit(EXIT_FAILURE);
    }

    for (int j = 0; j < data->data_count; ++j)
    {
        fwrite(data->data[j], sizeof(char), data->data_lengths[j], fp);
        fputc('\n', fp);
    }
    fclose(fp);
}