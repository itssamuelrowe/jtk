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

// Thursday, June 28, 2018

#include <jtk/unit/TestResult.h>

/*******************************************************************************
 * TestResult                                                                 *
 *******************************************************************************/

jtk_TestResult_t* jtk_TestResult_new() {
    jtk_TestResult_t* result = jtk_Memory_allocate(jtk_TestResult_t, 1);
    result->m_list = jtk_ArrayList_new();

    return result;
}

void jtk_TestResult_delete(jtk_TestResult_t* result) {
    jtk_Assert_assertObject(manager, "The specified test result is null.");

    jtk_ArrayList_delete(result->m_list);
    jtk_Memory_deallocate(result);
}