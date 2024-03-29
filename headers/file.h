/*
FILE HANDLING HEADER
-Defines functions opening files
*/

#ifndef FILE_H

#define FILE_H

void get_input_files(struct files *);

void get_parameter_files(struct files *);

void get_f_parameter_file_data(struct data * ,FILE *);

void get_fsl_parameter_file_data(struct data *, FILE *);

long *get_file_lengths(FILE **, int);

char **get_file_data(FILE **, int, long *);

void copy_data(struct data *);

void merge_data(struct data *);

#endif