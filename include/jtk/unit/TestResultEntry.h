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

// Wednesday, June 27, 2018

#ifndef JTK_UNIT_TEST_RESULT_ENTRY_H
#define JTK_UNIT_TEST_RESULT_ENTRY_H

#include <jtk/Configuration.h>
#include <jtk/core/SourceLocation.h>

/*******************************************************************************
 * TestResultEntry                                                             *
 *******************************************************************************/

struct jtk_TestResultEntry_t {
    jtk_SourceLocation_t* m_sourceLocation;
    uint8_t* m_message;
};

typedef struct jtk_TestResultEntry_t jtk_TestResultEntry_t;

#endif /* JTK_UNIT_TEST_RESULT_ENTRY_H */