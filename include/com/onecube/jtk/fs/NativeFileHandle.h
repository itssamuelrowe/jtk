// Monday, May 06, 2019

#ifndef COM_ONECUBE_JTK_FS_NATIVE_FILE_HANDLE_H
#define COM_ONECUBE_JTK_FS_NATIVE_FILE_HANDLE_H

#include <jtk/Configuration.h>
#include <jtk/core/Error.h>

/*******************************************************************************
 * NativeFileHandle                                                            *
 *******************************************************************************/

// Open

int64_t jtk_NativeFileHandle_open(const uint8_t* path, jtk_Error_t* error);

// Read

int32_t jtk_NativeFileHandle_readBytes(int64_t handle, uint8_t* buffer,
    int32_t size, int32_t startIndex, int32_t stopIndex, jtk_Error_t* error);

#endif /* COM_ONECUBE_JTK_FS_NATIVE_FILE_HANDLE_H */