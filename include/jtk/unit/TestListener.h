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

#ifndef JTK_UNIT_TEST_LISTENER_H
#define JTK_UNIT_TEST_LISTENER_H

#include <jtk/Configuration.h>

/*******************************************************************************
 * TestListener                                                                *
 *******************************************************************************/

/* Forward References */

typedef struct jtk_TestCase_t jtk_TestCase_t;
typedef struct jtk_TestSuite_t jtk_TestSuite_t;

/**
 * @memberof TestListener
 */
typedef struct jtk_TestListener_t jtk_TestListener_t;

/**
 * @memberof TestListener
 */
typedef void (*jtk_TestListenerOnStart_t)(jtk_TestListener_t* listener);

/**
 * @memberof TestListener
 */
typedef void (*jtk_TestListenerOnStop_t)(jtk_TestListener_t* listener);

/**
 * @memberof TestListener
 */
typedef void (*jtk_TestListenerOnEnterSuite_t)(jtk_TestListener_t* listener, jtk_TestSuite_t* suite);

/**
 * @memberof TestListener
 */
typedef void (*jtk_TestListenerOnExitSuite_t)(jtk_TestListener_t* listener, jtk_TestSuite_t* suite);

/**
 * @memberof TestListener
 */
typedef void (*jtk_TestListenerOnEnterCase_t)(jtk_TestListener_t* listener, jtk_TestCase_t* testCase);

/**
 * @memberof TestListener
 */
typedef void (*jtk_TestListenerOnExitCase_t)(jtk_TestListener_t* listener, jtk_TestCase_t* testCase);

/**
 * @memberof TestListener
 */
typedef void (*jtk_TestListenerOnCaseSuccess_t)(jtk_TestListener_t* listener, jtk_TestCase_t* testCase);

/**
 * @memberof TestListener
 */
typedef void (*jtk_TestListenerOnCaseFailure_t)(jtk_TestListener_t* listener, jtk_TestCase_t* testCase);

/**
 * @memberof TestListener
 */
typedef void (*jtk_TestListenerOnCaseError_t)(jtk_TestListener_t* listener, jtk_TestCase_t* testCase);

/**
 * @memberof TestListener
 */
typedef void (*jtk_TestListenerOnCaseUnknownError_t)(jtk_TestListener_t* listener, jtk_TestCase_t* testCase);

/**
 * @class TestListener
 * @ingroup jtk_unit
 * @author Samuel Rowe <samuelrowe1999@gmail.com>
 * @since JTK 1.0
 */
struct jtk_TestListener_t {
    jtk_TestListenerOnStart_t m_onStart;
    jtk_TestListenerOnStop_t m_onStop;
    
    jtk_TestListenerOnEnterSuite_t m_onEnterSuite;
    jtk_TestListenerOnExitSuite_t m_onExitSuite;

    jtk_TestListenerOnEnterCase_t m_onEnterCase;
    jtk_TestListenerOnExitCase_t m_onExitCase;

    jtk_TestListenerOnCaseSuccess_t m_onCaseSuccess;
    jtk_TestListenerOnCaseFailure_t m_onCaseFailure;
    jtk_TestListenerOnCaseError_t m_onCaseError;
    jtk_TestListenerOnCaseUnknownError_t m_onCaseUnknownError;
    
    void* m_bundle;
};

/**
 * @memberof TestListener
 */
jtk_TestListener_t* jtk_TestListener_new();

/**
 * @memberof TestListener
 */
jtk_TestListener_t* jtk_TestListener_newWithBundle(void* bundle);

/**
 * @memberof TestListener
 */
void jtk_TestListener_delete(jtk_TestListener_t* listener);

/**
 * @memberof TestListener
 */
void jtk_TestListener_onStart(jtk_TestListener_t* listener);

/**
 * @memberof TestListener
 */
void jtk_TestListener_onStop(jtk_TestListener_t* listener);

/**
 * @memberof TestListener
 */
void jtk_TestListener_onEnterSuite(jtk_TestListener_t* listener, jtk_TestSuite_t* suite);

/**
 * @memberof TestListener
 */
void jtk_TestListener_onExitSuite(jtk_TestListener_t* listener, jtk_TestSuite_t* suite);

/**
 * @memberof TestListener
 */
void jtk_TestListener_onEnterCase(jtk_TestListener_t* listener, jtk_TestCase_t* testCase);

/**
 * @memberof TestListener
 */
void jtk_TestListener_onExitCase(jtk_TestListener_t* listener, jtk_TestCase_t* testCase);

/**
 * @memberof TestListener
 */
void jtk_TestListener_onCaseSuccess(jtk_TestListener_t* listener, jtk_TestCase_t* testCase);

/**
 * @memberof TestListener
 */
void jtk_TestListener_onCaseFailure(jtk_TestListener_t* listener, jtk_TestCase_t* testCase);

/**
 * @memberof TestListener
 */
void jtk_TestListener_onCaseError(jtk_TestListener_t* listener, jtk_TestCase_t* testCase);

/**
 * @memberof TestListener
 */
void jtk_TestListener_onCaseUnknownError(jtk_TestListener_t* listener, jtk_TestCase_t* testCase);

#endif /* JTK_UNIT_TEST_LISTENER_H */