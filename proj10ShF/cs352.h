
#ifndef _CS352_H_INCLUDED_
#define _CS352_H_INCLUDED_

/* Somthing for size_t. */
#include <stdlib.h>

void* cs352_malloc(size_t num_bytes);
void* cs352_calloc(size_t count, size_t size);
void* cs352_strdup(const char* str); 

#endif 

