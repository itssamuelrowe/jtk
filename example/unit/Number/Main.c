/*
 *                              Jez Toolkit (JTK)
 *     Copyright (C) 2018 OneCube Software Solutions. All rights reserved.
 *
 * This file is part of Jez Toolkit Example Suite, version 1.0. The contents of
 * this file, either partially or fully, may be used, distributed and modified
 * without any limitation.
 */

// Wednesday, June 27, 2018

#include <jtk/unit/TestCase.h>
#include <jtk/unit/TestSuite.h>
#include <jtk/unit/TestManager.h>
#include <jtk/unit/ConsoleProgressListener.h>
#include <jtk/unit/SimpleProgressListener.h>
#include <jtk/collection/array/Array.h>

#include "Number.h"

/*******************************************************************************
 * Number Test                                                                 *
 *******************************************************************************/

void example_NumberTest_testIsOdd(jtk_TestCase_t* testCase) {
    jtk_TestCase_assertTrue(testCase, example_Number_isOdd(5));
    jtk_TestCase_assertFalse(testCase, example_Number_isOdd(4));
}

void example_NumberTest_testIsEven(jtk_TestCase_t* testCase) {
    jtk_TestCase_assertTrueEx(testCase, example_Number_isEven(5), "This failure was intentionally caused.");
    jtk_TestCase_assertFalse(testCase, example_Number_isEven(5));
}

/*******************************************************************************
 * Main                                                                        *
 *******************************************************************************/

int32_t main() {
    /* A test suite contains zero or more test cases and even other test suites.
     * All test cases are grouped together and given a name. The name helps us
     * identify the test suite when printing the result.
     */
    jtk_TestSuite_t* suite = jtk_TestSuite_new("number");

    /* A test case represents an individual test which does not affect other
     * test cases, ideally. It has a fixture which represents an isolated
     * environment.
     *
     * Every fixture receives two notifications from the test manager.
     * 1. "set-up"
     *    In this event, the fixture should allocate resources which
     *    are required by the test case.
     * 2. "tear-down"
     *    In this event, the fixture should deallocate resources which
     *    were allocated in the "setUp" event.
     *
     * It should be noted that a fixture is not necessary. Here, we pass
     * NULL to indicate the absence of a fixture.
     */
    jtk_TestCase_t* testIsOdd = jtk_TestCase_new("testIsOdd", NULL, example_NumberTest_testIsOdd);
    jtk_TestCase_t* testIsEven = jtk_TestCase_new("testIsEven", NULL, example_NumberTest_testIsEven);

    /* Add the all the test cases. */
    jtk_TestSuite_addCase(suite, testIsOdd);
    jtk_TestSuite_addCase(suite, testIsEven);

    /* A console progress listener prints appropriate messages on the console
     * as the tests are executed.
     */
    jtk_ConsoleProgressListener_t* consoleProgressListener = jtk_ConsoleProgressListener_new();
    // jtk_SimpleProgressListener_t* simpleProgressListener = jtk_SimpleProgressListener_new();
    /* Custom test listeners can be created. But the test manager understands
     * only the TestListener interface. Therfore, all listeners should be
     * converted into a test listener. The obtained listener is then passed to
     * the test manager.
     */
    jtk_TestListener_t* listener = jtk_ConsoleProgressListener_getTestListener(consoleProgressListener);
    // jtk_TestListener_t* listener = jtk_SimpleProgressListener_getTestListener(simpleProgressListener);

    /* A test manager runs all the test cases in the root test suite, directly
     * or indirectly, through recurive algorithms.
     */
    jtk_TestManager_t* manager = jtk_TestManager_new();

    /* Add the equivalent test listener of the console progress listener we
     * instantiated previously.
     */
    jtk_TestManager_addTestListener(manager, listener);

    /* Run the tests cases contained in the specified test suite. The results
     * of the execution is appropriately notified to the result object.
     */
    jtk_TestManager_runSuite(manager, suite);

    /* Destroy all the allocated resources. */
    jtk_TestManager_delete(manager);
    jtk_ConsoleProgressListener_delete(consoleProgressListener);
    jtk_TestCase_delete(testIsOdd);
    jtk_TestCase_delete(testIsEven);
    jtk_TestSuite_delete(suite);

    return 0;
}