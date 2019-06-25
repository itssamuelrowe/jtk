#include <stdio.h>
#include <stdlib.h>

#include <jtk/core/System.h>
#include <jtk/core/Error.h>
#include <jtk/io/InputStream.h>
#include <jtk/io/BufferedInputStream.h>
#include <jtk/fs/FileInputStream.h>
#include <jtk/fs/Path.h>

int32_t mainf(int32_t size, char** arguments) {
    if (size < 2) {
        fprintf(stderr, "Usage: %s path+\n", arguments[0]);
        exit(1);
    }

    jtk_System_initialize();

    int32_t i;
    for (i = 1; i < size; i++) {
        const uint8_t* path = (uint8_t*)arguments[i];
        jtk_FileInputStream_t* input = jtk_FileInputStream_newFromString(path);
        jtk_BufferedInputStream_t* bufferedInputStream =
            jtk_BufferedInputStream_newEx(input->m_inputStream, 1024 * 4);
        jtk_InputStream_t* stream = bufferedInputStream->m_inputStream;
        int32_t c;
        int32_t read = 0;
        int32_t j = 0;
        do {
            uint8_t buffer[1024];
            read = jtk_InputStream_readBytesEx(stream, buffer, 1024, 0, 1024);
            for (j = 0; j < read; j++) {
//                printf("%c", buffer[j]);
            }
            /*
            if (j++ == 4) {
                j = 0;
                jtk_BufferedInputStream_buffer(bufferedInputStream);
            }
            */
        }
        while (read > 0);

        printf("\n\nCache hits: %d\tCache misses: %d\n", bufferedInputStream->m_cacheHits,
            bufferedInputStream->m_cacheMisses);

        jtk_InputStream_destroy(stream);
    }

    jtk_System_shutdown();

    return 0;
}

int32_t main(int32_t size, char** arguments) {
    if (size < 2) {
        fprintf(stderr, "Usage: %s path+\n", arguments[0]);
        exit(1);
    }

    jtk_System_initialize();

    int32_t i;
    for (i = 1; i < size; i++) {
        const uint8_t* argument = (uint8_t*)arguments[i];
        jtk_Path_t* path = jtk_Path_newFromString(argument);
        jtk_PathHandle_t* handle = jtk_PathHandle_newFromPath(path);
        
        if (jtk_PathHandle_isDirectory(handle)) {
            printf("%s is a directory.\n", argument);
        }
        else if (jtk_PathHandle_isRegularFile(handle)) {
            printf("%s is a regular file.\n", argument);
        }
        
        jtk_PathHandle_delete(handle);
        jtk_Path_delete(path);
    }

    jtk_System_shutdown();

    return 0;
}