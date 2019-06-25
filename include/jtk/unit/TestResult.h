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

// Monday, May 21, 2018

#ifndef JTK_UNIT_TEST_RESULT_H
#define JTK_UNIT_TEST_RESULT_H

#include <jtk/Configuration.h>
#include <jtk/unit/TestResultEntry.h>

/*******************************************************************************
 * TestResult                                                                  *
 *******************************************************************************/

struct jtk_TestResult_t {
    jtk_ArrayList_t* m_list;
};

typedef struct jtk_TestResult_t jtk_TestResult_t;

jtk_TestResult_t* jtk_TestResult_new();
void jtk_TestResult_delete(jtk_TestResult_t* result);
void jtk_TestResult_addFailure(jtk_TestResult_t* result, jtk_TestResultEntry_t* failure);
void jtk_TestResult_addError(jtk_TestResult_t* result, jtk_TestResultEntry_t* error);
void jtk_TestResult_addUnknownError(jtk_TestResult_t* result, jtk_TestResultEntry_t* unknownError);

#endif /* JTK_UNIT_TEST_RESULT_H */