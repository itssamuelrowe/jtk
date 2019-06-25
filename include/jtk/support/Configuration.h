// Friday, March 22, 2019

#ifndef JTK_SUPPORT_CONFIGURATION_H
#define JTK_SUPPORT_CONFIGURATION_H

/*******************************************************************************
 * Configuration                                                               *
 *******************************************************************************/

struct jtk_Configuration_t {
};

typedef struct jtk_Configuration_t jtk_Configuration_t;

void jtk_Configuration_defineString(jtk_Configuration_t* configuration,
    jtk_String_t* key, jtk_String_t* value);

#endif /* JTK_SUPPORT_CONFIGURATION_H */