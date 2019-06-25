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

// Friday, June 29, 2018

#ifndef JTK_UNIT_CONSOLE_PROGRESS_LISTENER_H
#define JTK_UNIT_CONSOLE_PROGRESS_LISTENER_H

#include <jtk/Configuration.h>
#include <jtk/unit/TestListener.h>

/*******************************************************************************
 * ConsoleProgressListener                                                     *
 *******************************************************************************/

/**
 * @class ConsoleProgressListener
 * @ingroup jtk_unit
 * @author Samuel Rowe <samuelrowe1999@gmail.com>
 * @since JTK 1.0
 */
struct jtk_ConsoleProgressListener_t {
    jtk_TestListener_t* m_listener;
    int32_t m_numberOfCases;
    int32_t m_numberOfSuites;
    int32_t m_numberOfSuccesses;
    int32_t m_numberOfFailures;
    int32_t m_numberOfErrors;
    int32_t m_numberOfUnknownErrors;
};

/**
 * @memberof ConsoleProgressListener
 */
typedef struct jtk_ConsoleProgressListener_t jtk_ConsoleProgressListener_t;

/**
 * @memberof ConsoleProgressListener
 */
jtk_ConsoleProgressListener_t* jtk_ConsoleProgressListener_new();

/**
 * @memberof ConsoleProgressListener
 */
void jtk_ConsoleProgressListener_delete(jtk_ConsoleProgressListener_t* listener);

/**
 * @memberof ConsoleProgressListener
 */
jtk_TestListener_t* jtk_ConsoleProgressListener_getTestListener(jtk_ConsoleProgressListener_t* consoleProgressListener);

/**
 * @memberof ConsoleProgressListener
 */
void jtk_ConsoleProgressListener_onStart(jtk_TestListener_t* listener);

/**
 * @memberof ConsoleProgressListener
 */
void jtk_ConsoleProgressListener_onStop(jtk_TestListener_t* listener);

/**
 * @memberof ConsoleProgressListener
 */
void jtk_ConsoleProgressListener_onEnterSuite(jtk_TestListener_t* listener, jtk_TestSuite_t* suite);

/**
 * @memberof ConsoleProgressListener
 */
void jtk_ConsoleProgressListener_onExitSuite(jtk_TestListener_t* listener, jtk_TestSuite_t* suite);

/**
 * @memberof ConsoleProgressListener
 */
void jtk_ConsoleProgressListener_onEnterCase(jtk_TestListener_t* listener, jtk_TestCase_t* testCase);

/**
 * @memberof ConsoleProgressListener
 */
void jtk_ConsoleProgressListener_onExitCase(jtk_TestListener_t* listener, jtk_TestCase_t* testCase);

/**
 * @memberof ConsoleProgressListener
 */
void jtk_ConsoleProgressListener_onCaseSuccess(jtk_TestListener_t* listener, jtk_TestCase_t* testCase);

/**
 * @memberof ConsoleProgressListener
 */
void jtk_ConsoleProgressListener_onCaseFailure(jtk_TestListener_t* listener, jtk_TestCase_t* testCase);

/**
 * @memberof ConsoleProgressListener
 */
void jtk_ConsoleProgressListener_onCaseError(jtk_TestListener_t* listener, jtk_TestCase_t* testCase);

/**
 * @memberof ConsoleProgressListener
 */
void jtk_ConsoleProgressListener_onCaseUnknownError(jtk_TestListener_t* listener, jtk_TestCase_t* testCase);

#endif /* JTK_UNIT_CONSOLE_PROGRESS_LISTENER_H */