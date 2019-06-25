// Monday, March 25, 2019

#ifndef JTK_CORE_VARIABLE_ARGUMENTS_H
#define JTK_CORE_VARIABLE_ARGUMENTS_H

#include <stdarg.h>
#include <jtk/Configuration.h>

/*******************************************************************************
 * VariableArguments                                                           *
 *******************************************************************************/

#define jtk_VariableArguments_start va_start
#define jtk_VariableArguments_end va_end

typedef va_list jtk_VariableArguments_t;

#endif /* JTK_CORE_VARIABLE_ARGUMENTS_H */