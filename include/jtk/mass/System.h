// Tuesday, August 28, 2018

#ifndef JTK_MASS_SYSTEM_H
#define JTK_MASS_SYSTEM_H

/*******************************************************************************
 * System                                                                      *
 *******************************************************************************/

/* Error */

void jtk_System_setError(jtk_Error_t error);
bool jtk_System_hasError();
jtk_Error_t jtk_System_getError();

#endif /* JTK_MASS_SYSTEM_H */