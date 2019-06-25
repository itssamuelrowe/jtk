// Friday, May 18, 2018

#ifndef JTK_CONFIGURATION_H
#define JTK_CONFIGURATION_H

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>

#ifndef NULL
    #define NULL 0
#endif

#define jtk_Memory_allocate(type, units) (type*)jtk_Memory_allocate0(sizeof (type) * (units))
#define jtk_Memory_deallocate(object) jtk_Memory_deallocate0(object)

#define jtk_Assert_assertObject(object, message) assert((object) != NULL)
#define jtk_Assert_assertTrue(expression, message) assert(expression)
#define jtk_Assert_assertFalse(expression, message) assert(!(expression))

void* jtk_Memory_allocate0(int32_t size);
void jtk_Memory_deallocate0(void* object);

#endif /* JTK_CONFIGURATION_H */