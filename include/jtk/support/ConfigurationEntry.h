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