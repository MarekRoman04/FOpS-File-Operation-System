#include "./master_header.h"
#include "./headers/args.h"

const char *PROGRAM_VERSION = "1.0.0";
const char *PROGRAM_NAME = "FOpS (File-Operation-System)";

int main(int argc, char *argv[])
{
    switch (argc)
    {
    case 1:
        program_usage();
        break;
    case 2:
        if (!strcmp(argv[1], "--version"))
            program_version();
        else if (!strcmp(argv[1], "--help"))
            program_help();
        else
            program_unknown();
        break;
    default:
        process_args(argc, argv);
        start_operation();
    }

    exit(EXIT_SUCCESS);
}