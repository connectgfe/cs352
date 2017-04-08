
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 

#include "cs352.h"

#define MAKE_MALLOC_FAIL_FILE "MAKE_MALLOC_FAIL"
#define NOT_SET (-99)

static int fail_this_time(void);

void* cs352_malloc(size_t num_bytes)
{
    if (fail_this_time())
    {
        return NULL;
    }
    else
    {
        return malloc(num_bytes);
    }
}

void* cs352_calloc(size_t count, size_t size)
{
    if (fail_this_time())
    {
        return NULL;
    }
    else
    {
        return calloc(count, size);
    }
}

void* cs352_strdup(const char* str)
{
    if (fail_this_time())
    {
        return NULL;
    }
    else
    {
        return strdup(str);
    }
}

static int fail_this_time(void)
{
    static int first_time = 1;    /* TRUE */
    static int call_count = 0; 
    static int periodicity = NOT_SET;

    if (first_time)
    {
        static FILE *make_file_fp = NULL; 

        first_time = 0;

        make_file_fp = fopen(MAKE_MALLOC_FAIL_FILE, "r"); 

        if (make_file_fp != NULL)
        {
            char* line = NULL;
            size_t line_sz = 0;
            int count_lines = 0;

            while (getline(&line, &line_sz, make_file_fp) != EOF)
            {
                if (count_lines == 0) 
                {
                    int sscanf_res = sscanf(line, "%d", &periodicity); 

                    if (sscanf_res != 1)
                    {
                        fprintf(stderr, "Unable to read a single integer from %s.\n", MAKE_MALLOC_FAIL_FILE); 
                        exit (1); 
                    }
                    else if (periodicity <= 0)
                    {
                        fprintf(stderr, "The contents of %s need to be exactly one positive integer.\n", MAKE_MALLOC_FAIL_FILE); 
                        exit (1); 
                    }
                }
                count_lines++;
            }

            if (count_lines != 1)
            {
                fprintf(stderr, "File %s should have exactly one line.\n", MAKE_MALLOC_FAIL_FILE);
                exit(1);
            }
            free(line);
            fclose(make_file_fp);
        }

    }

    if (periodicity == NOT_SET)
    {
        return 0;
    }
    else 
    {
        call_count++;

        /*
        printf("call_count: %d, mod: %d, bool: %d\n", call_count, call_count % periodicity, (call_count % periodicity) == 0);
        */

        return ((call_count % periodicity) == 0); 
    }

}






