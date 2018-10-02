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
 * @author Samuel Rowe
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