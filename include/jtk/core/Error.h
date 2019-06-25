// Monday, May 06, 2019

#ifndef JTK_CORE_ERROR_H
#define JTK_CORE_ERROR_H

/*******************************************************************************
 * Error                                                                       *
 *******************************************************************************/
 
/**
 * @class Error
 * @ingroup jtk_core
 * @author Samuel Rowe
 * @since JTK 1.1
 */
enum jtk_Error_t {
    JTK_ERROR_NONE,
    JTK_ERROR_UNKNOWN,
    JTK_ERROR_INVALID_PATH,
    JTK_ERROR_UNAUTHORIZED_ACCESS,
    JTK_ERROR_INVALID_PATH_HANDLE,
    JTK_ERROR_INVALID_BUFFER,
    JTK_ERROR_TOO_MANY_SYMBOLIC_LINKS,
    JTK_ERROR_VERY_LONG_PATH,
    JTK_ERROR_OUT_OF_MEMORY,
    JTK_ERROR_EXPECTED_DIRECTORY,
    JTK_ERROR_EXPECTED_FILE,
    JTK_ERROR_INTEGER_OVERFLOW,
    JTK_ERROR_END_OF_STREAM,
    JTK_ERROR_TOTAL
};

/**
 * @memberof Error
 */
typedef enum jtk_Error_t jtk_Error_t;

#endif /* JTK_CORE_ERROR_H */