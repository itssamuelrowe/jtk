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

// Tuesday, May 22, 2018

#ifndef JTK_UNIT_TEST_MANAGER_H
#define JTK_UNIT_TEST_MANAGER_H

#include <jtk/Configuration.h>
#include <jtk/collection/list/ArrayList.h>
#include <jtk/unit/TestCase.h>
#include <jtk/unit/TestSuite.h>
#include <jtk/unit/TestListener.h>

/*******************************************************************************
 * TestManager                                                                 *
 *******************************************************************************/

/**
 * @class TestManager
 * @ingroup jtk_unit
 * @author Samuel Rowe <samuelrowe1999@gmail.com>
 * @since JTK 1.0
 */
struct jtk_TestManager_t {
    jtk_ArrayList_t* m_listeners;
};

/**
 * @memberof TestManager
 */
typedef struct jtk_TestManager_t jtk_TestManager_t;

/**
 * @memberof TestManager
 */
jtk_TestManager_t* jtk_TestManager_new();

/**
 * @memberof TestManager
 */
void jtk_TestManager_delete(jtk_TestManager_t* manager);

/**
 * @memberof TestManager
 */
void jtk_TestManager_addTestListener(jtk_TestManager_t* result, jtk_TestListener_t* listener);

/**
 * @memberof TestManager
 */
void jtk_TestManager_removeTestListener(jtk_TestManager_t* result, jtk_TestListener_t* listener);

/**
 * @memberof TestManager
 */
void jtk_TestManager_notifyOnStartListeners(jtk_TestManager_t* manager);

/**
 * @memberof TestManager
 */
void jtk_TestManager_notifyOnStopListeners(jtk_TestManager_t* manager);

/**
 * @memberof TestManager
 */
void jtk_TestManager_notifyOnEnterSuiteListeners(jtk_TestManager_t* manager, jtk_TestSuite_t* suite);

/**
 * @memberof TestManager
 */
void jtk_TestManager_notifyOnExitSuiteListeners(jtk_TestManager_t* manager, jtk_TestSuite_t* suite);

/**
 * @memberof TestManager
 */
void jtk_TestManager_notifyOnEnterCaseListeners(jtk_TestManager_t* manager, jtk_TestCase_t* suite);

/**
 * @memberof TestManager
 */
void jtk_TestManager_notifyOnExitCaseListeners(jtk_TestManager_t* manager, jtk_TestCase_t* suite);

/**
 * @memberof TestManager
 */
void jtk_TestManager_notifyOnEnterCaseListeners(jtk_TestManager_t* manager, jtk_TestCase_t* testCase);

/**
 * @memberof TestManager
 */
void jtk_TestManager_notifyOnExitCaseListeners(jtk_TestManager_t* manager, jtk_TestCase_t* testCase);

/**
 * @memberof TestManager
 */
void jtk_TestManager_notifyOnCaseSuccessListeners(jtk_TestManager_t* manager, jtk_TestCase_t* testCase);

/**
 * @memberof TestManager
 */
void jtk_TestManager_notifyOnCaseFailureListeners(jtk_TestManager_t* manager, jtk_TestCase_t* testCase);

/**
 * @memberof TestManager
 */
void jtk_TestManager_notifyOnCaseErrorListeners(jtk_TestManager_t* manager, jtk_TestCase_t* testCase);

/**
 * @memberof TestManager
 */
void jtk_TestManager_notifyOnCaseUnknownErrorListeners(jtk_TestManager_t* manager, jtk_TestCase_t* testCase);

/*
jtk_TestPath_t* jtk_TestManager_resolve(jtk_TestManager_t* manager, const uint8_t* path);
jtk_ArrayList_t* jtk_TestManager_resolveAll(jtk_TestManager_t* manager, const uint8_t* path);
void jtk_TestManager_runPath(jtk_TestManager_t* manager, jtk_TestPath_t* path, jtk_TestResult_t* result);
*/

/**
 * @memberof TestManager
 */
void jtk_TestManager_runSuite(jtk_TestManager_t* manager, jtk_TestSuite_t* suite);

/**
 * @memberof TestManager
 */
void jtk_TestManager_runCase(jtk_TestManager_t* manager, jtk_TestCase_t* testCase);

#endif /* JTK_UNIT_TEST_MANAGER_H */