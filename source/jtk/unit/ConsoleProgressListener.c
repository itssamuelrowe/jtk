// Friday, June 29, 2018

#include <stdio.h>
#include <jtk/unit/ConsoleProgressListener.h>
#include <jtk/unit/TestDefect.h>

/*******************************************************************************
 * ConsoleProgressListener                                                     *
 *******************************************************************************/

jtk_ConsoleProgressListener_t* jtk_ConsoleProgressListener_new() {
    jtk_ConsoleProgressListener_t* consoleProgressListener = (jtk_ConsoleProgressListener_t*)jtk_Memory_allocate(jtk_ConsoleProgressListener_t, 1);
    consoleProgressListener->m_listener = jtk_TestListener_newWithBundle(consoleProgressListener);
    consoleProgressListener->m_numberOfCases = 0;
    consoleProgressListener->m_numberOfSuites = 0;
    consoleProgressListener->m_numberOfSuccesses = 0;
    consoleProgressListener->m_numberOfFailures = 0;
    consoleProgressListener->m_numberOfErrors = 0;
    consoleProgressListener->m_numberOfUnknownErrors = 0;

    jtk_TestListener_t* listener = consoleProgressListener->m_listener;
    listener->m_onStart = jtk_ConsoleProgressListener_onStart;
    listener->m_onStop = jtk_ConsoleProgressListener_onStop;
    listener->m_onEnterSuite = jtk_ConsoleProgressListener_onEnterSuite;
    listener->m_onExitSuite = jtk_ConsoleProgressListener_onExitSuite;
    listener->m_onEnterCase = jtk_ConsoleProgressListener_onEnterCase;
    listener->m_onExitCase = jtk_ConsoleProgressListener_onExitCase;
    listener->m_onCaseSuccess = jtk_ConsoleProgressListener_onCaseSuccess;
    listener->m_onCaseFailure = jtk_ConsoleProgressListener_onCaseFailure;
    listener->m_onCaseError = jtk_ConsoleProgressListener_onCaseError;
    listener->m_onCaseUnknownError = jtk_ConsoleProgressListener_onCaseUnknownError;

    return consoleProgressListener;
}

void jtk_ConsoleProgressListener_delete(jtk_ConsoleProgressListener_t* listener) {
    jtk_Assert_assertObject(listener, "The specified console progress listener is null.");

    jtk_TestListener_delete(listener->m_listener);
    jtk_Memory_deallocate(listener);
}

jtk_TestListener_t* jtk_ConsoleProgressListener_getTestListener(jtk_ConsoleProgressListener_t* listener) {
    jtk_Assert_assertObject(listener, "The specified console progress listener is null.");

    return listener->m_listener;
}

void jtk_ConsoleProgressListener_onStart(jtk_TestListener_t* listener) {
    jtk_Assert_assertObject(listener, "The specified test listener is null.");
}

void jtk_ConsoleProgressListener_onStop(jtk_TestListener_t* listener) {
    jtk_Assert_assertObject(listener, "The specified test listener is null.");

    jtk_ConsoleProgressListener_t* consoleProgressListener = (jtk_ConsoleProgressListener_t*)listener->m_bundle;

    fprintf(stdout, "\n");
    fprintf(stdout, "Suites            :    %d\n", consoleProgressListener->m_numberOfSuites);
    fprintf(stdout, "Cases             :    %d\n", consoleProgressListener->m_numberOfCases);
    fprintf(stdout, "Successes         :    %d\n", consoleProgressListener->m_numberOfSuccesses);
    fprintf(stdout, "Failures          :    %d\n", consoleProgressListener->m_numberOfFailures);
    fprintf(stdout, "Errors            :    %d\n", consoleProgressListener->m_numberOfErrors);
    fprintf(stdout, "Unknown Errors    :    %d\n", consoleProgressListener->m_numberOfUnknownErrors);
}

void jtk_ConsoleProgressListener_onEnterSuite(
    jtk_TestListener_t* listener, jtk_TestSuite_t* suite) {
    jtk_Assert_assertObject(listener, "The specified test listener is null.");
    jtk_Assert_assertObject(suite, "The specified test suite is null.");

    jtk_ConsoleProgressListener_t* consoleProgressListener = (jtk_ConsoleProgressListener_t*)listener->m_bundle;
    consoleProgressListener->m_numberOfSuites++;

    fprintf(stdout, "[JTK] [enter] Running test suite '%s'\n", jtk_TestSuite_getName(suite));
}

void jtk_ConsoleProgressListener_onExitSuite(
    jtk_TestListener_t* listener, jtk_TestSuite_t* suite) {
    jtk_Assert_assertObject(listener, "The specified test listener is null.");
    jtk_Assert_assertObject(suite, "The specified test suite is null.");

    fprintf(stdout, "[JTK] [exit] Stopping test suite '%s'\n", jtk_TestSuite_getName(suite));
}

void jtk_ConsoleProgressListener_onEnterCase(
    jtk_TestListener_t* listener, jtk_TestCase_t* testCase) {
    jtk_Assert_assertObject(listener, "The specified test listener is null.");
    jtk_Assert_assertObject(testCase, "The specified test case is null.");

    jtk_ConsoleProgressListener_t* consoleProgressListener = (jtk_ConsoleProgressListener_t*)listener->m_bundle;
    consoleProgressListener->m_numberOfCases++;

    fprintf(stdout, "[JTK] [enter] Running test case '%s'\n", jtk_TestCase_getName(testCase));
}

void jtk_ConsoleProgressListener_onExitCase(
    jtk_TestListener_t* listener, jtk_TestCase_t* testCase) {
    jtk_Assert_assertObject(listener, "The specified test listener is null.");
    jtk_Assert_assertObject(testCase, "The specified test case is null.");

    fprintf(stdout, "[JTK] [exit] Stopping test case '%s'\n", jtk_TestCase_getName(testCase));
}

void jtk_ConsoleProgressListener_onCaseSuccess(
    jtk_TestListener_t* listener, jtk_TestCase_t* testCase) {
    jtk_Assert_assertObject(listener, "The specified test listener is null.");
    jtk_Assert_assertObject(testCase, "The specified test case is null.");

    jtk_ConsoleProgressListener_t* consoleProgressListener = (jtk_ConsoleProgressListener_t*)listener->m_bundle;
    consoleProgressListener->m_numberOfSuccesses++;

    fprintf(stdout, "[JTK] [success] Test case '%s' was successful\n", jtk_TestCase_getName(testCase));
}

void jtk_ConsoleProgressListener_onCaseFailure(
    jtk_TestListener_t* listener, jtk_TestCase_t* testCase) {
    jtk_Assert_assertObject(listener, "The specified test listener is null.");
    jtk_Assert_assertObject(testCase, "The specified test case is null.");

    jtk_ConsoleProgressListener_t* consoleProgressListener = (jtk_ConsoleProgressListener_t*)listener->m_bundle;
    consoleProgressListener->m_numberOfFailures++;

    jtk_TestDefect_t* defect = jtk_TestCase_getDefect(testCase);
    const uint8_t* sourceCodePath = jtk_TestDefect_getSourceCodePath(defect);
    int32_t lineNumber = jtk_TestDefect_getLineNumber(defect);
    const uint8_t* message = jtk_TestDefect_getMessage(defect);
    const uint8_t* testName = jtk_TestCase_getName(testCase);
    
    fprintf(stdout, "[JTK] [failure] Test case '%s' failed at %s:%d\n", testName,
        sourceCodePath, lineNumber);
    fprintf(stdout, "[JTK] [message] %s: %s\n", testName,
        (message == NULL)? "No message available." : message);
}

void jtk_ConsoleProgressListener_onCaseError(
    jtk_TestListener_t* listener, jtk_TestCase_t* testCase) {
    jtk_Assert_assertObject(listener, "The specified test listener is null.");
    jtk_Assert_assertObject(testCase, "The specified test case is null.");

    jtk_ConsoleProgressListener_t* consoleProgressListener = (jtk_ConsoleProgressListener_t*)listener->m_bundle;
    consoleProgressListener->m_numberOfErrors++;

    fprintf(stdout, "[JTK] Case Result   : '%s' failed with error\n", jtk_TestCase_getName(testCase));
}

void jtk_ConsoleProgressListener_onCaseUnknownError(
    jtk_TestListener_t* listener, jtk_TestCase_t* testCase) {
    jtk_Assert_assertObject(listener, "The specified test listener is null.");
    jtk_Assert_assertObject(testCase, "The specified test case is null.");

    jtk_ConsoleProgressListener_t* consoleProgressListener = (jtk_ConsoleProgressListener_t*)listener->m_bundle;
    consoleProgressListener->m_numberOfUnknownErrors++;

    fprintf(stdout, "[JTK] Case Result   : '%s' failed with unknown error\n", jtk_TestCase_getName(testCase));
}