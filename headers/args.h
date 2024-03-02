/*
ARGS PROCESSING AND PROGRAM FUNCTIONS HEADER
-Defines functions handling argumnets
-Defines program functions called by arguments
*/

#ifndef ARGS_H

#define ARGS_H

void program_usage();
void program_version();
void program_help();
void program_unknown();

void process_args(int, char *[]);
void get_args(struct args *, int, int, char *[]);

void start_operation();

void find_words(struct data *, struct data *);
void find_words_count(struct data *, struct data *);
void find_all_words(struct data *, struct data *);
void find_string(struct data *, struct data *);
void find_all_strings(struct data *, struct data *);

#endif