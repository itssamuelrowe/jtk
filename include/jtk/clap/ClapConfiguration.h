// Saturday, April 06, 2019

#ifndef JTK_CLAP_CLAP_CONFIGURATION_H
#define JTK_CLAP_CLAP_CONFIGURATION_H

#include <jtk/Configuration.h>
#include <jtk/clap/Parameter.h>
#include <jtk/collection/map/HashMap.h>

/*******************************************************************************
 * ClapConfiguration                                                           *
 *******************************************************************************/

/**
 * @class ClapConfiguration
 * @ingrop jtk_clap
 * @author Samuel Rowe
 * @since JTK 1.1
 */
struct jtk_ClapConfiguration_t {
    jtk_HashMap_t* m_parameters;
};

/**
 * @memberof ClapConfiguration
 */
typedef struct jtk_ClapConfiguration_t jtk_ClapConfiguration_t;

// Constructor

/**
 * @memberof ClapConfiguration
 */
jtk_ClapConfiguration_t* jtk_ClapConfiguration_new();

// Destructor

/**
 * @memberof ClapConfiguration
 */
void jtk_ClapConfiguration_delete(jtk_ClapConfiguration_t* configuration);

#endif /* JTK_CLAP_CLAP_CONFIGURATION_H */