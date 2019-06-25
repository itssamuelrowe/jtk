// Saturday, May 25, 2019

#include <stdio.h>
#include <jtk/core/DefaultErrorHandler.h>

/*******************************************************************************
 * DefaultErrorHandler                                                         *
 *******************************************************************************/

const uint8_t messages[JTK_ERROR_TOTAL + 1][100] = {
    "No error",
    "Unknown error",
    "Invalid path",
    "Unauthorized access",
    "Invalid path handle",
    "Invalid buffer",
    "Too many symbolic links",
    "Very long path",
    "Out of memory",
    "Expected directory",
    "Expected file",
    "Integer overflow",
    "End of stream",
    "Unknown error code" // Special message that indicates an invalid error code.
};

const uint8_t* jtk_DefaultErrorHandler_getMessage(jtk_Error_t error, uint32_t flags) {
    const uint8_t* result = messages[(int32_t)JTK_ERROR_TOTAL];
    int32_t index = (int32_t)error;
    if ((index >= 0) && (index < (int32_t)JTK_ERROR_TOTAL)) {
        result = messages[index];
    }
    return result;
}

void jtk_DefaultErrorHandler_handleError(jtk_Error_t error, int32_t flags) {
    const uint8_t* message = jtk_DefaultErrorHandler_getMessage(error, flags);
    fprintf(stderr, "Error: %s (code=0x%08X, flags=0x%08X)\n", message, error, flags);
    fflush(stderr);
}