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