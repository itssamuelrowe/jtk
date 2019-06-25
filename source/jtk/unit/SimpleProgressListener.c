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

// Saturday, June 30, 2018

#include <stdio.h>
#include <jtk/unit/SimpleProgressListener.h>

/*******************************************************************************
 * SimpleProgressListener                                                      *
 *******************************************************************************/

jtk_SimpleProgressListener_t* jtk_SimpleProgressListener_new() {
    jtk_SimpleProgressListener_t* consoleProgressListener = (jtk_SimpleProgressListener_t*)jtk_Memory_allocate(jtk_SimpleProgressListener_t, 1);
    consoleProgressListener->m_listener = jtk_TestListener_newWithBundle(consoleProgressListener);
    consoleProgressListener->m_numberOfCases = 0;
    consoleProgressListener->m_numberOfSuites = 0;
    consoleProgressListener->m_numberOfSuccesses = 0;
    consoleProgressListener->m_numberOfFailures = 0;
    consoleProgressListener->m_numberOfErrors = 0;
    consoleProgressListener->m_numberOfUnknownErrors = 0;

    jtk_TestListener_t* listener = consoleProgressListener->m_listener;
    listener->m_onStart = jtk_SimpleProgressListener_onStart;
    listener->m_onStop = jtk_SimpleProgressListener_onStop;
    listener->m_onEnterSuite = jtk_SimpleProgressListener_onEnterSuite;
    listener->m_onExitSuite = jtk_SimpleProgressListener_onExitSuite;
    listener->m_onEnterCase = jtk_SimpleProgressListener_onEnterCase;
    listener->m_onExitCase = jtk_SimpleProgressListener_onExitCase;
    listener->m_onCaseSuccess = jtk_SimpleProgressListener_onCaseSuccess;
    listener->m_onCaseFailure = jtk_SimpleProgressListener_onCaseFailure;
    listener->m_onCaseError = jtk_SimpleProgressListener_onCaseError;
    listener->m_onCaseUnknownError = jtk_SimpleProgressListener_onCaseUnknownError;

    return consoleProgressListener;
}

void jtk_SimpleProgressListener_delete(jtk_SimpleProgressListener_t* listener) {
    jtk_Assert_assertObject(listener, "The specified console progress listener is null.");

    jtk_TestListener_delete(listener->m_listener);
    jtk_Memory_deallocate(listener);
}

jtk_TestListener_t* jtk_SimpleProgressListener_getTestListener(jtk_SimpleProgressListener_t* listener) {
    jtk_Assert_assertObject(listener, "The specified console progress listener is null.");

    return listener->m_listener;
}

void jtk_SimpleProgressListener_onStart(jtk_TestListener_t* listener) {
    jtk_Assert_assertObject(listener, "The specified test listener is null.");
}

void jtk_SimpleProgressListener_onStop(jtk_TestListener_t* listener) {
    jtk_Assert_assertObject(listener, "The specified test listener is null.");

    jtk_SimpleProgressListener_t* consoleProgressListener = (jtk_SimpleProgressListener_t*)listener->m_bundle;

    fprintf(stdout, "\n\n");
    fprintf(stdout, "Cases             :    %d\n", consoleProgressListener->m_numberOfCases);
    fprintf(stdout, "Suites            :    %d\n", consoleProgressListener->m_numberOfSuites);
    fprintf(stdout, "Successes         :    %d\n", consoleProgressListener->m_numberOfSuccesses);
    fprintf(stdout, "Failures          :    %d\n", consoleProgressListener->m_numberOfFailures);
    fprintf(stdout, "Errors            :    %d\n", consoleProgressListener->m_numberOfErrors);
    fprintf(stdout, "Unknown Errors    :    %d\n", consoleProgressListener->m_numberOfUnknownErrors);
}

void jtk_SimpleProgressListener_onEnterSuite(
    jtk_TestListener_t* listener, jtk_TestSuite_t* suite) {
    jtk_Assert_assertObject(listener, "The specified test listener is null.");
    jtk_Assert_assertObject(suite, "The specified test suite is null.");

    jtk_SimpleProgressListener_t* consoleProgressListener = (jtk_SimpleProgressListener_t*)listener->m_bundle;
    consoleProgressListener->m_numberOfSuites++;
}

void jtk_SimpleProgressListener_onExitSuite(
    jtk_TestListener_t* listener, jtk_TestSuite_t* suite) {
    jtk_Assert_assertObject(listener, "The specified test listener is null.");
    jtk_Assert_assertObject(suite, "The specified test suite is null.");
}

void jtk_SimpleProgressListener_onEnterCase(
    jtk_TestListener_t* listener, jtk_TestCase_t* testCase) {
    jtk_Assert_assertObject(listener, "The specified test listener is null.");
    jtk_Assert_assertObject(testCase, "The specified test case is null.");

    jtk_SimpleProgressListener_t* consoleProgressListener = (jtk_SimpleProgressListener_t*)listener->m_bundle;
    consoleProgressListener->m_numberOfCases++;
}

void jtk_SimpleProgressListener_onExitCase(
    jtk_TestListener_t* listener, jtk_TestCase_t* testCase) {
    jtk_Assert_assertObject(listener, "The specified test listener is null.");
    jtk_Assert_assertObject(testCase, "The specified test case is null.");
}

void jtk_SimpleProgressListener_onCaseSuccess(
    jtk_TestListener_t* listener, jtk_TestCase_t* testCase) {
    jtk_Assert_assertObject(listener, "The specified test listener is null.");
    jtk_Assert_assertObject(testCase, "The specified test case is null.");

    jtk_SimpleProgressListener_t* consoleProgressListener = (jtk_SimpleProgressListener_t*)listener->m_bundle;
    consoleProgressListener->m_numberOfSuccesses++;

    fprintf(stdout, "O");
}

void jtk_SimpleProgressListener_onCaseFailure(
    jtk_TestListener_t* listener, jtk_TestCase_t* testCase) {
    jtk_Assert_assertObject(listener, "The specified test listener is null.");
    jtk_Assert_assertObject(testCase, "The specified test case is null.");

    jtk_SimpleProgressListener_t* consoleProgressListener = (jtk_SimpleProgressListener_t*)listener->m_bundle;
    consoleProgressListener->m_numberOfFailures++;

    fprintf(stdout, "X");
}

void jtk_SimpleProgressListener_onCaseError(
    jtk_TestListener_t* listener, jtk_TestCase_t* testCase) {
    jtk_Assert_assertObject(listener, "The specified test listener is null.");
    jtk_Assert_assertObject(testCase, "The specified test case is null.");

    jtk_SimpleProgressListener_t* consoleProgressListener = (jtk_SimpleProgressListener_t*)listener->m_bundle;
    consoleProgressListener->m_numberOfErrors++;

    fprintf(stdout, "E");
}

void jtk_SimpleProgressListener_onCaseUnknownError(
    jtk_TestListener_t* listener, jtk_TestCase_t* testCase) {
    jtk_Assert_assertObject(listener, "The specified test listener is null.");
    jtk_Assert_assertObject(testCase, "The specified test case is null.");

    jtk_SimpleProgressListener_t* consoleProgressListener = (jtk_SimpleProgressListener_t*)listener->m_bundle;
    consoleProgressListener->m_numberOfUnknownErrors++;

    fprintf(stdout, "U");
}