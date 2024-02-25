/*
ERROR FUNCTION HEADER
-Defines error handling functions
*/

#ifndef ERROR_H

#define ERROR_H

void alloc_error(char *);
void alloc_2d_error(int, char *);

void error();

void error_multiple_operations();
void error_missing_operation();
void error_missing_input();
void error_missing_parameter();
void error_invalid_operation();
void error_missing_input_files();

#endif