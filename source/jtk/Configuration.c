// Friday, May 18, 2018

#include <stdlib.h>
#include <jtk/Configuration.h>

/*******************************************************************************
 * Memory                                                                      *
 *******************************************************************************/

void* jtk_Memory_allocate0(int32_t size) {
    void* object = malloc(size);
    return object;
}

void jtk_Memory_deallocate0(void* object) {
    free(object);
}