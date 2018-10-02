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

// Saturday, June 30, 2018

#ifndef JTK_UNIT_SIMPLE_PROGRESS_LISTENER_H
#define JTK_UNIT_SIMPLE_PROGRESS_LISTENER_H

#include <jtk/Configuration.h>
#include <jtk/unit/TestListener.h>

/*******************************************************************************
 * SimpleProgressListener                                                      *
 *******************************************************************************/

/**
 * @class SimpleProgressListener
 * @ingroup jtk_unit
 * @author Samuel Rowe
 * @since JTK 1.0
 */
struct jtk_SimpleProgressListener_t {
    jtk_TestListener_t* m_listener;
    int32_t m_numberOfCases;
    int32_t m_numberOfSuites;
    int32_t m_numberOfSuccesses;
    int32_t m_numberOfFailures;
    int32_t m_numberOfErrors;
    int32_t m_numberOfUnknownErrors;
};

/**
 * @memberof SimpleProgressListener
 */
typedef struct jtk_SimpleProgressListener_t jtk_SimpleProgressListener_t;

/**
 * @memberof SimpleProgressListener
 */
jtk_SimpleProgressListener_t* jtk_SimpleProgressListener_new();

/**
 * @memberof SimpleProgressListener
 */
void jtk_SimpleProgressListener_delete(jtk_SimpleProgressListener_t* listener);

/**
 * @memberof SimpleProgressListener
 */
jtk_TestListener_t* jtk_SimpleProgressListener_getTestListener(jtk_SimpleProgressListener_t* consoleProgressListener);

/**
 * @memberof SimpleProgressListener
 */
void jtk_SimpleProgressListener_onStart(jtk_TestListener_t* listener);

/**
 * @memberof SimpleProgressListener
 */
void jtk_SimpleProgressListener_onStop(jtk_TestListener_t* listener);

/**
 * @memberof SimpleProgressListener
 */
void jtk_SimpleProgressListener_onEnterSuite(jtk_TestListener_t* listener, jtk_TestSuite_t* suite);

/**
 * @memberof SimpleProgressListener
 */
void jtk_SimpleProgressListener_onExitSuite(jtk_TestListener_t* listener, jtk_TestSuite_t* suite);

/**
 * @memberof SimpleProgressListener
 */
void jtk_SimpleProgressListener_onEnterCase(jtk_TestListener_t* listener, jtk_TestCase_t* testCase);

/**
 * @memberof SimpleProgressListener
 */
void jtk_SimpleProgressListener_onExitCase(jtk_TestListener_t* listener, jtk_TestCase_t* testCase);

/**
 * @memberof SimpleProgressListener
 */
void jtk_SimpleProgressListener_onCaseSuccess(jtk_TestListener_t* listener, jtk_TestCase_t* testCase);

/**
 * @memberof SimpleProgressListener
 */
void jtk_SimpleProgressListener_onCaseFailure(jtk_TestListener_t* listener, jtk_TestCase_t* testCase);

/**
 * @memberof SimpleProgressListener
 */
void jtk_SimpleProgressListener_onCaseError(jtk_TestListener_t* listener, jtk_TestCase_t* testCase);

/**
 * @memberof SimpleProgressListener
 */
void jtk_SimpleProgressListener_onCaseUnknownError(jtk_TestListener_t* listener, jtk_TestCase_t* testCase);

#endif /* JTK_UNIT_SIMPLE_PROGRESS_LISTENER_H */