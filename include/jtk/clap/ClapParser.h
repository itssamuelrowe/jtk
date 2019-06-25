// Saturday, April 06, 2019

#ifndef JTK_CLAP_CLAP_PARSER_H
#define JTK_CLAP_CLAP_PARSER_H

#include <jtk/Configuration.h>
#include <jtk/clap/ClapConfiguration.h>
#include <jtk/clap/Parameter.h>
#include <jtk/collection/array/Array.h>

/*******************************************************************************
 * ClapParser                                                                  *
 *******************************************************************************/

/**
 * @author Samuel Rowe
 * @since JTK 1.1
 */
struct jtk_ClapParser_t {
    jtk_ClapConfiguration_t* m_configuration;
};

/**
 * @memberof ClapParser
 */
typedef struct jtk_ClapParser_t jtk_ClapParser_t;

// Constructor

/**
 * @memberof ClapParser
 */
jtk_ClapParser_t* jtk_ClapParser_newWithConfiguration(jtk_ClapConfiguration_t* configuration);

// Destructor

/**
 * @memberof ClapParser
 */
void jtk_ClapParser_delete(jtk_ClapParser_t* parser);

// Parse

void jtk_ClapParser_parse(jtk_ClapParser_t* parser, jtk_Array_t* arguments);

#endif /* JTK_CLAP_CLAP_PARSER_H */