/*
FILE HANDLING HEADER
-Defines functions opening files
*/

#ifndef FILE_H

#define FILE_H

void get_input_files(struct files *);

void get_parameter_files(struct files *);

long *get_file_lengths(FILE **, int);

char **get_file_data(FILE **, int, long *);


#endif