/*
STRUCTS HEADER FILE
-Defines structs used in program
*/

#ifndef STRUCTS_H

#define STRUCTS_H

struct args {
    int args_len;
    char **args;
    void (*get_args)(struct args *, int, int, char *[]);
};

struct files {
    FILE **fp_arr;
    int file_count;
    char **file_paths;
    void (*get_files)(struct files *);
};


struct data {
    char **data_paths;
    int data_count;
    long *data_lengths;
    char **data;
    void (*get_data)(struct data *);
};

#endif