// Tuesday, August 28, 2018

#ifndef JTK_MASS_ERROR_H
#define JTK_MASS_ERROR_H

/*******************************************************************************
 * Error                                                                       *
 *******************************************************************************/

/**
 * @class Error
 * @ingroup jtk_mass
 * @author Samuel Rowe <samuelrowe1999@gmail.com>
 * @since JTK 1.1
 */
struct jtk_Error_t {
    jtk_StringBuffer_t* m_message;
    int32_t m_code;
};

/**
 * @memberof Error
 */
typedef struct jtk_Error_t jtk_Error_t;

#endif /* JTK_MASS_ERROR_H */