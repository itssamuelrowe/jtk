#include <jtk/io/InputStream.h>
#include <jtk/fs/FileInputStream.h>
#include <stdio.h>
#include <jtk/core/Error.h>
#include <stdlib.h>
#include <jtk/fs/Path.h>

int32_t main(int32_t size, char** arguments) {
    if (size < 2) {
        fprintf(stderr, "Usage: %s path+\n", arguments[0]);
        exit(1);
    }
    
    int32_t i;
    for (i = 1; i < size; i++) {
        const uint8_t* path = (uint8_t*)arguments[i];
        jtk_FileInputStream_t* stream = jtk_FileInputStream_newFromString(path);
        int32_t c;
        do {
            c = jtk_FileInputStream_read(stream);
            printf("%c", c);
        }
        while (c >= 0);
        jtk_FileInputStream_delete(stream);
    }
    
    return 0;
}

void jtk_System_setError(jtk_Error_t error) {
    printf("Error: %d\n", error);
}