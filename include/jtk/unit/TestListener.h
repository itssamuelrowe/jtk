/*
 *                              Jez Toolkit (JTK)
 *     Copyright (C) 2018 OneCube Software Solutions. All rights reserved.
 *
 * This file is part of Jez Toolkit Free Edition, version 1.0.
 *
 * See the file "LICENSE" included in the distribution for the terms and conditions,
 * or visit http://www.onecube.in/jtk/free-license.
 *
 * IMPORTANT NOTE: You may NOT copy the content of this file, either partially
 * or fully, into your source code.
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
 * @author Samuel Rowe
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