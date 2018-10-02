/*
 *                              Jez Toolkit (JTK)
 *     Copyright (C) 2018 OneCube Software Solutions. All rights reserved.
 *
 * This file is part of Jez Toolkit Test Suite, version 1.0. The contents of
 * this file, either partially or fully, may be used, distributed and modified
 * without any limitation.
 */

// Wednesday, June 27, 2018

#include <jtk/collection/list/ArrayList.h>
#include <jtk/collection/stack/LinkedStack.h>

#include <jtk/unit/TestCase.h>
#include <jtk/unit/TestFixture.h>
#include <jtk/unit/TestSuite.h>
#include <jtk/unit/TestManager.h>
#include <jtk/unit/ConsoleProgressListener.h>

#include <com/jtk/collection/list/ArrayListTest.h>

/*******************************************************************************
 * Main                                                                        *
 *******************************************************************************/

int32_t main() {
    jtk_TestSuite_t* arrayListSuite = jtk_ArrayListTest_getSuite();

    jtk_TestSuite_t* suite = jtk_TestSuite_new("Main");
    jtk_TestSuite_addSuite(suite, arrayListSuite);

    jtk_ConsoleProgressListener_t* consoleProgressListener = jtk_ConsoleProgressListener_new();
    jtk_TestListener_t* listener = jtk_ConsoleProgressListener_getTestListener(consoleProgressListener);

    jtk_TestManager_t* manager = jtk_TestManager_new();
    jtk_TestManager_addTestListener(manager, listener);
    jtk_TestManager_runSuite(manager, suite);

    jtk_TestManager_delete(manager);
    jtk_ConsoleProgressListener_delete(consoleProgressListener);

    jtk_LinkedStack_t* stack = jtk_LinkedStack_new();
    jtk_LinkedStack_push(stack, suite);
    while (!jtk_LinkedStack_isEmpty(stack)) {
        jtk_TestSuite_t* suite = (jtk_TestSuite_t*)jtk_LinkedStack_pop(stack);

        jtk_ArrayList_t* suites = jtk_TestSuite_getSuites(suite);
        jtk_LinkedStack_addAll(stack, JTK_COLLECTION_ARRAY_LIST, suites);

        jtk_ArrayList_t* cases = jtk_TestSuite_getCases(suite);
        int32_t numberOfCases = jtk_ArrayList_getSize(cases);
        int32_t i;
        for (i = 0; i < numberOfCases; i++) {
            jtk_TestCase_t* testCase = (jtk_TestCase_t*)jtk_ArrayList_getValue(cases, i);

            jtk_TestFixture_t* fixture = jtk_TestCase_getFixture(testCase);
            if (fixture != NULL) {
                jtk_TestFixture_delete(fixture);
            }

            jtk_TestCase_delete(testCase);
        }

        jtk_TestSuite_delete(suite);
    }
    jtk_LinkedStack_delete(stack);

    return 0;
}