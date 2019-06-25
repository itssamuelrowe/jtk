// Saturday, May 25, 2019

#ifndef JTK_CORE_DEFAULT_ERROR_HANDLER_H
#define JTK_CORE_DEFAULT_ERROR_HANDLER_H

#include <jtk/Configuration.h>
#include <jtk/core/Error.h>

/*******************************************************************************
 * DefaultErrorHandler                                                         *
 *******************************************************************************/

/**
 * @since JTK 1.1
 */
void jtk_DefaultErrorHandler_handleError(jtk_Error_t error, int32_t flags);

#endif /* JTK_CORE_DEFAULT_ERROR_HANDLER_H */