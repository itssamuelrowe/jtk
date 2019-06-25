/*
 * Copyright 2018-2019 OneCube
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