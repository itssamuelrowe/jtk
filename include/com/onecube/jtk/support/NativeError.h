// Sunday, May 05, 2019

#ifndef COM_ONECUBE_JTK_SUPPORT_NATIVE_ERROR_H
#define COM_ONECUBE_JTK_SUPPORT_NATIVE_ERROR_H

#include <jtk/Configuration.h>
#include <jtk/core/Error.h>

/*******************************************************************************
 * NativeError                                                                 *
 *******************************************************************************/

// Translate

jtk_Error_t jtk_NativeError_translate(int32_t code);
jtk_Error_t jtk_NativeError_translateEx(int32_t code, jtk_Error_t* error);

#endif /* COM_ONECUBE_JTK_SUPPORT_NATIVE_ERROR_H */