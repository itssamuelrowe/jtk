// Friday, March 22, 2019

#ifndef JTK_SUPPORT_CONFIGURATION_ENTRY_H
#define JTK_SUPPORT_CONFIGURATION_ENTRY_H

#include <jtk/Configuration.h>
#include <jtk/support/ConfigurationEntryType.h>

/*******************************************************************************
 * ConfigurationEntry                                                          *
 *******************************************************************************/

struct jtk_ConfigurationEntry_t {
    jtk_JSONType_t m_valueType;
    void* m_value;
    bool m_overriden;
};

typedef struct jtk_ConfigurationEntry_t jtk_ConfigurationEntry_t;

#endif /* JTK_SUPPORT_CONFIGURATION_ENTRY_H */