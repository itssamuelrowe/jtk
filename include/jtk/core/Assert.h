// Monday, May 21, 2018

#ifndef JTK_CORE_ASSERT_H
#define JTK_CORE_ASSERT_H

#include <jtk/Configuration.h>

/*******************************************************************************
 * Assert                                                                      *
 *******************************************************************************/

/**
 * @class Assert
 * @ingroup jtk_core
 * @author Samuel Rowe <samuelrowe1999@gmail.com>
 * @since JTK 1.0
 */

/**
 * @memberof Assert
 */
#define jtk_Assert_assertObject(object, message) assert((object) != NULL)

/**
 * @memberof Assert
 */
#define jtk_Assert_assertTrue(expression, message) assert(expression)

/**
 * @memberof Assert
 */
#define jtk_Assert_assertFalse(expression, message) assert(!(expression))

#endif /* JTK_CORE_ASSERT_H */