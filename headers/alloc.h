/*
MEMORY ALLOCATION HEADER
-Defines function allocating/deallocating memory
*/

#ifndef ALLOC_H

#define ALLOC_H

void free_2d_array(void **, int);

void free_args(struct args *);

void free_files(struct files *);

void free_data(struct data *);

void merge_data_struct(struct data *, struct data *);

#endif