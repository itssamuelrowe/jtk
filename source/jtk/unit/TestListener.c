// Friday, June 29, 2018

#include <jtk/unit/TestListener.h>

/*******************************************************************************
 * TestListener                                                                *
 *******************************************************************************/

jtk_TestListener_t* jtk_TestListener_new() {
    return jtk_TestListener_newWithBundle(NULL);
}

jtk_TestListener_t* jtk_TestListener_newWithBundle(void* bundle) {
    jtk_TestListener_t* listener = (jtk_TestListener_t*)jtk_Memory_allocate(jtk_TestListener_t, 1);
    listener->m_onStart = jtk_TestListener_onStart;
    listener->m_onStop = jtk_TestListener_onStop;
    listener->m_onEnterSuite = jtk_TestListener_onEnterSuite;
    listener->m_onExitSuite = jtk_TestListener_onExitSuite;
    listener->m_onEnterCase = jtk_TestListener_onEnterCase;
    listener->m_onExitCase = jtk_TestListener_onExitCase;
    listener->m_onCaseSuccess = jtk_TestListener_onCaseSuccess;
    listener->m_onCaseFailure = jtk_TestListener_onCaseFailure;
    listener->m_onCaseError = jtk_TestListener_onCaseError;
    listener->m_onCaseUnknownError = jtk_TestListener_onCaseUnknownError;
    listener->m_bundle = bundle;

    return listener;
}

void jtk_TestListener_delete(jtk_TestListener_t* listener) {
    jtk_Assert_assertObject(listener, "The specified listener is null.");

    jtk_Memory_deallocate(listener);
}

void jtk_TestListener_onStart(jtk_TestListener_t* listener) {
}

void jtk_TestListener_onStop(jtk_TestListener_t* listener) {
}

void jtk_TestListener_onEnterSuite(jtk_TestListener_t* listener,
    jtk_TestSuite_t* suite) {
}

void jtk_TestListener_onExitSuite(jtk_TestListener_t* listener,
    jtk_TestSuite_t* suite) {
}

void jtk_TestListener_onEnterCase(jtk_TestListener_t* listener,
    jtk_TestCase_t* testCase) {
}

void jtk_TestListener_onExitCase(jtk_TestListener_t* listener,
    jtk_TestCase_t* testCase) {
}

void jtk_TestListener_onCaseSuccess(jtk_TestListener_t* listener,
    jtk_TestCase_t* testCase) {
}

void jtk_TestListener_onCaseFailure(jtk_TestListener_t* listener,
    jtk_TestCase_t* testCase) {
}

void jtk_TestListener_onCaseError(jtk_TestListener_t* listener,
    jtk_TestCase_t* testCase) {
}

void jtk_TestListener_onCaseUnknownError(jtk_TestListener_t* listener,
    jtk_TestCase_t* testCase) {
}