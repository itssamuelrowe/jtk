/*
 * Copyright 2017-2020 Samuel Rowe
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

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