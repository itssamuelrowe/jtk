// Monday, May 27, 2019

#ifndef JTK_IO_INPUT_STREAM_HELPER_H
#define JTK_IO_INPUT_STREAM_HELPER_H

#include <jtk/Configuration.h>
#include <jtk/io/InputStream.h>

/*******************************************************************************
 * InputStreamHelper                                                           *
 *******************************************************************************/

bool jtk_InputStreamHelper_readFully(jtk_InputStream_t* stream, uint8_t* buffer,
    int32_t size);

bool jtk_InputStreamHelper_readFullyEx(jtk_InputStream_t* stream, uint8_t* buffer,
    int32_t size, int32_t index, int32_t limit);

#endif /* JTK_IO_INPUT_STREAM_HELPER_H */