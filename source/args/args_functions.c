#include "../../master_header.h"
#include "../../headers/args.h"
#include "../../headers/data.h"
#include "../../headers/file.h"
#include "../../headers/error.h"

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
    printf("<files> -f \"\'searched_word\'\"/<word_list>\n");
    printf("-fAll\nFinds all occurencies of word or list of words\n");
    printf("<files> -fAll \"\'searched_word\'\"/<word_list>\n");
    printf("-fc\nChecks if text contains word or list of words, returns number of found words\n");
    printf("-f, -fAll, -fc takes only 1 file or strings, other files or strings are ignored!\n");
    printf("<files> -fc \"\'searched_word\'\"/<word_list>\n");
    printf("-fs\nChecks if text contains string\n");
    printf("<files> -fs \"\'string\'\"/<string>\n");
    printf("-fsAll\nFinds all occurencies of string\n");
    printf("<files> -fsAll \"\'string\'\"/<string>\n");
    printf("-fsl\nChecks if text contains strings from list of strings\n");
    printf("<files> -fsl <string_list>\n");
    printf("-fslc\nChecks if text contains strings from list of strings, returns number of found strings\n");
    printf("<files> -fslc <string_list>\n");
    printf("-fslA\nFinds all occurencies of strings from list of strings\n");
    printf("<files> -fslA <string_list>\n");
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
    parameter_data->get_data = &get_f_parameter_data;
    parameter_data->get_data(parameter_data);

    if (DEBUG)
        print_f_found_data(input_data, parameter_data);

    for (int i = 0; i < input_data->data_count; ++i)
    {
        int found_strings = 0;
        printf("Searching: %s:\n", input_data->data_paths[i]);
        for (int j = 0; j < parameter_data->data_count; ++j)
        {
            char *index = input_data->data[i];
            bool is_word = false;
            while ((index = strstr(index, parameter_data->data[j])) != NULL)
            {
                bool word_start = index == input_data->data[i] || *(index - 1) == ' ' || *(index - 1) == '\n' || *(index - 1) == '\t' ? true : false;
                bool word_end = *(index + strlen(parameter_data->data[j])) == '\0' ||
                                        *(index + strlen(parameter_data->data[j])) == ' ' ||
                                        *(index + strlen(parameter_data->data[j])) == '\n' ||
                                        *(index + strlen(parameter_data->data[j])) == '\r' ||
                                        *(index + strlen(parameter_data->data[j])) == '\t'
                                    ? true
                                    : false;
                if (word_start && word_end)
                {
                    is_word = true;
                    break;
                }
                index += strlen(parameter_data->data[j]);
            }

            if (is_word)
            {
                printf("%s\n", parameter_data->data[j]);
                ++found_strings;
            }
        }
        if (!found_strings)
            printf("No strings found!\n");
    }
}

void find_words_count(struct data *input_data, struct data *parameter_data)
{
    parameter_data->get_data = &get_f_parameter_data;
    parameter_data->get_data(parameter_data);
    printf("Data loaded, finding started!\n");

    if (DEBUG)
        print_f_found_data(input_data, parameter_data);

    for (int i = 0; i < input_data->data_count; ++i)
    {
        int found_strings = 0;
        printf("Searching: %s:\n", input_data->data_paths[i]);
        for (int j = 0; j < parameter_data->data_count; ++j)
        {
            char *index = input_data->data[i];
            bool is_word = false;
            while ((index = strstr(index, parameter_data->data[j])) != NULL)
            {
                bool word_start = index == input_data->data[i] || *(index - 1) == ' ' || *(index - 1) == '\n' || *(index - 1) == '\t' ? true : false;
                bool word_end = *(index + strlen(parameter_data->data[j])) == '\0' ||
                                        *(index + strlen(parameter_data->data[j])) == ' ' ||
                                        *(index + strlen(parameter_data->data[j])) == '\n' ||
                                        *(index + strlen(parameter_data->data[j])) == '\r' ||
                                        *(index + strlen(parameter_data->data[j])) == '\t'
                                    ? true
                                    : false;
                if (word_start && word_end)
                {
                    is_word = true;
                    break;
                }
                index += strlen(parameter_data->data[j]);
            }

            if (is_word)
                ++found_strings;
        }
        printf("%d\n", found_strings);
    }
}

void find_all_words(struct data *input_data, struct data *parameter_data)
{
    parameter_data->get_data = &get_f_parameter_data;
    parameter_data->get_data(parameter_data);

    if (DEBUG)
        print_f_found_data(input_data, parameter_data);

    for (int i = 0; i < input_data->data_count; ++i)
    {
        int found_strings = 0;
        int total_founds = 0;
        printf("Searching: %s:\n", input_data->data_paths[i]);
        for (int j = 0; j < parameter_data->data_count; ++j)
        {
            int found_occurences = 0;
            char *index = input_data->data[i];
            bool is_word = false;
            while ((index = strstr(index, parameter_data->data[j])) != NULL)
            {
                bool word_start = index == input_data->data[i] || *(index - 1) == ' ' || *(index - 1) == '\n' || *(index - 1) == '\t' ? true : false;
                bool word_end = *(index + strlen(parameter_data->data[j])) == '\0' ||
                                        *(index + strlen(parameter_data->data[j])) == ' ' ||
                                        *(index + strlen(parameter_data->data[j])) == '\n' ||
                                        *(index + strlen(parameter_data->data[j])) == '\r' ||
                                        *(index + strlen(parameter_data->data[j])) == '\t'
                                    ? true
                                    : false;
                if (word_start && word_end)
                    ++found_occurences;
                index += strlen(parameter_data->data[j]);
            }

            if (found_occurences)
            {
                printf("%s %d x\n", parameter_data->data[j], found_occurences);
                total_founds += found_occurences;
                ++found_strings;
            }
        }
        if (!found_strings)
            printf("No strings found!\n");
        else
            printf("Found %d words %d times\n", found_strings, total_founds);
    }
}

void find_string(struct data *input_data, struct data *parameter_data)
{
    parameter_data->get_data = &get_fs_parameter_data;
    parameter_data->get_data(parameter_data);

    if (DEBUG)
        print_found_data(input_data, parameter_data);

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
        print_found_data(input_data, parameter_data);

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
            printf("%s %d x\n", parameter_data->data_paths[j], found_occurences);
            ++found_strings;
        }
    }
}

void find_string_list(struct data *input_data, struct data *parameter_data)
{
    parameter_data->get_data = &get_fsl_parameter_data;
    parameter_data->get_data(parameter_data);

    if (DEBUG)
        print_f_found_data(input_data, parameter_data);

    for (int i = 0; i < input_data->data_count; ++i)
    {
        int found_strings = 0;
        printf("Searching: %s:\n", input_data->data_paths[i]);
        for (int j = 0; j < parameter_data->data_count; ++j)
        {
            if (strstr(input_data->data[i], parameter_data->data[j]))
            {
                printf("%s\n", parameter_data->data[j]);
                ++found_strings;
            }
        }
        if (!found_strings)
            printf("No strings found!\n");
    }
}

void find_string_list_count(struct data *input_data, struct data *parameter_data)
{
    parameter_data->get_data = &get_fsl_parameter_data;
    parameter_data->get_data(parameter_data);

    if (DEBUG)
        print_f_found_data(input_data, parameter_data);

    for (int i = 0; i < input_data->data_count; ++i)
    {
        int found_strings = 0;
        printf("Searching: %s:\n", input_data->data_paths[i]);
        for (int j = 0; j < parameter_data->data_count; ++j)
        {
            if (strstr(input_data->data[i], parameter_data->data[j]))
                ++found_strings;
        }

        printf("%d\n", found_strings);
    }
}

void find_all_string_list(struct data *input_data, struct data *parameter_data)
{
    parameter_data->get_data = &get_fsl_parameter_data;
    parameter_data->get_data(parameter_data);

    if (DEBUG)
        print_f_found_data(input_data, parameter_data);

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
            printf("%d x ", found_occurences);
            printf("%s\n", parameter_data->data[j]);
            ++found_strings;
        }
    }
}