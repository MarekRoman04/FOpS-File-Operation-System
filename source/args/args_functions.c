#include "../../master_header.h"
#include "../../headers/args.h"
#include "../../headers/data.h"
#include "../../headers/file.h"

extern char *PROGRAM_NAME;
extern char *PROGRAM_VERSION;

void program_usage()
{
    printf("%s %s\n", PROGRAM_NAME, PROGRAM_VERSION);
    printf("No arguments given!\nType --help for more info!");
    exit(EXIT_SUCCESS);
}

void program_version()
{
    printf("%s\n", PROGRAM_VERSION);
    exit(EXIT_SUCCESS);
}

void program_help()
{
    printf("%s %s\n", PROGRAM_NAME, PROGRAM_VERSION);
    printf("Command list: \n");
    printf("--version\nPrints program version\n");
    printf("-f\nChecks if text contains word or list of words\n");
    printf("<files> -f \"searched_word\"/<word_list>\n");
    printf("-fAll\nFinds all occurencies of word or list of words\n");
    printf("<files> -fAll \"searched_word\"/<word_list>\n");
    printf("-fs\nChecks if text contains string\n");
    printf("<files> -f \"\'string\'\"/<string>\n");
    printf("-fsAll\nFinds all occurencies of string\n");
    printf("<files> -fsAll \"\'string\'\"/<string>\n");
    exit(EXIT_SUCCESS);
}

void program_unknown()
{
    printf("%s %s\n", PROGRAM_NAME, PROGRAM_VERSION);
    printf("Unknown command!\nType --help for more info!\n");
    exit(EXIT_SUCCESS);
}

void find_words(struct data *input_data, struct data *parameter_data)
{
    if (DEBUG)
    {
        printf("Data found: %d\n", input_data->data_count);
        printf("Length of data:\n");
        for (int i = 0; i < input_data->data_count; ++i)
            printf("%s: %d\n", input_data->data_paths[i], input_data->data_lengths[i]);
        printf("\n");

        printf("Data:\n");
        for (int i = 0; i < input_data->data_count; ++i)
            printf("%s\n", input_data->data[i]);
        printf("\n");
    }
}

void find_string(struct data *input_data, struct data *parameter_data)
{
    parameter_data->get_data = &get_fs_parameter_data;
    parameter_data->get_data(parameter_data);

    if (DEBUG)
    {
        printf("Data found: %d\n", input_data->data_count);
        printf("Length of data: ");
        for (int i = 0; i < input_data->data_count; ++i)
            printf("%s: %d\n", input_data->data_paths[i], input_data->data_lengths[i]);
        printf("\n");
        // printf("Data:\n");
        // for (int i = 0; i < input_data->data_count; ++i)
        //     printf("%s\n", input_data->data[i]);
        // printf("\n");

        printf("Data found: %d\n", parameter_data->data_count);
        printf("Length of data: ");
        for (int i = 0; i < parameter_data->data_count; ++i)
            printf("%s: %d\n", parameter_data->data_paths[i], parameter_data->data_lengths[i]);
        printf("\n");
        // printf("Data:\n");
        // for (int i = 0; i < parameter_data->data_count; ++i)
        //     printf("%s\n", parameter_data->data[i]);
        // printf("\n");
    }

    for (int i = 0; i < input_data->data_count; ++i)
    {
        int found_strings = 0;
        printf("Searching: %s:\n", input_data->data_paths[i]);
        for (int j = 0; j < parameter_data->data_count; ++j)
        {
            if (strstr(input_data->data[i], parameter_data->data[j]))
            {
                printf("%s\n", parameter_data->data_paths[j]);
                ++found_strings;
            }
        }
        if (!found_strings)
            printf("No strings found!\n");
    }
}

void find_all_strings(struct data *input_data, struct data *parameter_data)
{
    parameter_data->get_data = &get_fs_parameter_data;
    parameter_data->get_data(parameter_data);

    if (DEBUG)
    {
        printf("Data found: %d\n", input_data->data_count);
        printf("Length of data: ");
        for (int i = 0; i < input_data->data_count; ++i)
            printf("%s: %d\n", input_data->data_paths[i], input_data->data_lengths[i]);
        printf("\n");
        // printf("Data:\n");
        // for (int i = 0; i < input_data->data_count; ++i)
        //     printf("%s\n", input_data->data[i]);
        // printf("\n");

        printf("Data found: %d\n", parameter_data->data_count);
        printf("Length of data: ");
        for (int i = 0; i < parameter_data->data_count; ++i)
            printf("%s: %d\n", parameter_data->data_paths[i], parameter_data->data_lengths[i]);
        printf("\n");
        // printf("Data:\n");
        // for (int i = 0; i < parameter_data->data_count; ++i)
        //     printf("%s\n", parameter_data->data[i]);
        // printf("\n");
    }

    for (int i = 0; i < input_data->data_count; ++i)
    {
        int found_strings = 0;
        printf("Searching: %s:\n", input_data->data_paths[i]);
        for (int j = 0; j < parameter_data->data_count; ++j)
        {
            char *index = input_data->data[i];
            int data_string_len = strlen(parameter_data->data[j]);
            int found_occurences = 0;
            while ((index = strstr(index, parameter_data->data[j])) != NULL)
            {
                index += data_string_len;
                ++found_occurences;
            }
            printf("%s %dx\n", parameter_data->data_paths[j], found_occurences);
            ++found_strings;
        }
    }
}
