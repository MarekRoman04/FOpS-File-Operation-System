/*
DATA HANDLING HEADER
-Defines functions getting and processing data
*/

#ifndef DATA_H

#define DATA_H

void get_input_data(struct data *);

void get_f_parameter_data(struct data *);

void get_fs_parameter_data(struct data *);

void get_fsl_parameter_data(struct data *);

void get_string_data(struct data *);

long *get_string_data_lengths(char **, int);

#endif