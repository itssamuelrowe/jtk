// Thursday, June 28, 2018

#include <setjmp.h>
#include <jtk/collection/stack/LinkedStack.h>
#include <jtk/unit/TestManager.h>

/*******************************************************************************
 * TestManager                                                                 *
 *******************************************************************************/

jtk_TestManager_t* jtk_TestManager_new() {
    jtk_TestManager_t* manager = jtk_Memory_allocate(jtk_TestManager_t, 1);
    manager->m_listeners = jtk_ArrayList_new();

    return manager;
}

void jtk_TestManager_delete(jtk_TestManager_t* manager) {
    jtk_Assert_assertObject(manager, "The specified test manager is null.");

    jtk_ArrayList_delete(manager->m_listeners);
    jtk_Memory_deallocate(manager);
}

void jtk_TestManager_addTestListener(jtk_TestManager_t* manager,
    jtk_TestListener_t* listener) {
    jtk_Assert_assertObject(manager, "The specified test manager is null.");
    jtk_Assert_assertObject(listener, "The specified test manager is null.");

    jtk_ArrayList_add(manager->m_listeners, listener);
}

void jtk_TestManager_removeTestListener(jtk_TestManager_t* manager,
    jtk_TestListener_t* listener) {
    jtk_Assert_assertObject(manager, "The specified test manager is null.");
    jtk_Assert_assertObject(listener, "The specified test manager is null.");

    jtk_ArrayList_remove(manager->m_listeners, listener);
}

/* Notify Start/Stop Listeners */

void jtk_TestManager_notifyOnStartListeners(jtk_TestManager_t* manager) {
    jtk_Assert_assertObject(manager, "The specified test manager is null.");

    int32_t size = jtk_ArrayList_getSize(manager->m_listeners);
    int32_t i;
    for (i = 0; i < size; i++) {
        jtk_TestListener_t* listener = (jtk_TestListener_t*)jtk_ArrayList_getValue(manager->m_listeners, i);
        listener->m_onStart(listener);
    }
}

void jtk_TestManager_notifyOnStopListeners(jtk_TestManager_t* manager) {
    jtk_Assert_assertObject(manager, "The specified test manager is null.");

    int32_t size = jtk_ArrayList_getSize(manager->m_listeners);
    int32_t i;
    for (i = 0; i < size; i++) {
        jtk_TestListener_t* listener = (jtk_TestListener_t*)jtk_ArrayList_getValue(manager->m_listeners, i);
        listener->m_onStop(listener);
    }
}

/* Notify Suite Listeners */

void jtk_TestManager_notifyOnEnterSuiteListeners(jtk_TestManager_t* manager,
    jtk_TestSuite_t* suite) {
    jtk_Assert_assertObject(manager, "The specified test manager is null.");
    jtk_Assert_assertObject(suite, "The specified test suite is null.");

    int32_t size = jtk_ArrayList_getSize(manager->m_listeners);
    int32_t i;
    for (i = 0; i < size; i++) {
        jtk_TestListener_t* listener = (jtk_TestListener_t*)jtk_ArrayList_getValue(manager->m_listeners, i);
        listener->m_onEnterSuite(listener, suite);
    }
}

void jtk_TestManager_notifyOnExitSuiteListeners(jtk_TestManager_t* manager,
    jtk_TestSuite_t* suite) {
    jtk_Assert_assertObject(manager, "The specified test manager is null.");
    jtk_Assert_assertObject(suite, "The specified test suite is null.");

    int32_t size = jtk_ArrayList_getSize(manager->m_listeners);
    int32_t i;
    for (i = 0; i < size; i++) {
        jtk_TestListener_t* listener = (jtk_TestListener_t*)jtk_ArrayList_getValue(manager->m_listeners, i);
        listener->m_onExitSuite(listener, suite);
    }
}

/* Notify Case Listeners */

void jtk_TestManager_notifyOnEnterCaseListeners(jtk_TestManager_t* manager,
    jtk_TestCase_t* testCase) {
    jtk_Assert_assertObject(manager, "The specified test manager is null.");
    jtk_Assert_assertObject(testCase, "The specified test case is null.");

    int32_t size = jtk_ArrayList_getSize(manager->m_listeners);
    int32_t i;
    for (i = 0; i < size; i++) {
        jtk_TestListener_t* listener = (jtk_TestListener_t*)jtk_ArrayList_getValue(manager->m_listeners, i);
        listener->m_onEnterCase(listener, testCase);
    }
}

void jtk_TestManager_notifyOnExitCaseListeners(jtk_TestManager_t* manager,
    jtk_TestCase_t* testCase) {
    jtk_Assert_assertObject(manager, "The specified test manager is null.");
    jtk_Assert_assertObject(testCase, "The specified test case is null.");

    int32_t size = jtk_ArrayList_getSize(manager->m_listeners);
    int32_t i;
    for (i = 0; i < size; i++) {
        jtk_TestListener_t* listener = (jtk_TestListener_t*)jtk_ArrayList_getValue(manager->m_listeners, i);
        listener->m_onExitCase(listener, testCase);
    }
}

/* Notify Case Result Listeners */

void jtk_TestManager_notifyOnCaseSuccessListeners(jtk_TestManager_t* manager,
    jtk_TestCase_t* testCase) {
    jtk_Assert_assertObject(manager, "The specified test manager is null.");
    jtk_Assert_assertObject(testCase, "The specified test case is null.");

    int32_t size = jtk_ArrayList_getSize(manager->m_listeners);
    int32_t i;
    for (i = 0; i < size; i++) {
        jtk_TestListener_t* listener = (jtk_TestListener_t*)jtk_ArrayList_getValue(manager->m_listeners, i);
        listener->m_onCaseSuccess(listener, testCase);
    }
}

void jtk_TestManager_notifyOnCaseFailureListeners(jtk_TestManager_t* manager,
    jtk_TestCase_t* testCase) {
    jtk_Assert_assertObject(manager, "The specified test manager is null.");
    jtk_Assert_assertObject(testCase, "The specified test case is null.");

    int32_t size = jtk_ArrayList_getSize(manager->m_listeners);
    int32_t i;
    for (i = 0; i < size; i++) {
        jtk_TestListener_t* listener = (jtk_TestListener_t*)jtk_ArrayList_getValue(manager->m_listeners, i);
        listener->m_onCaseFailure(listener, testCase);
    }
}

void jtk_TestManager_notifyOnCaseErrorListeners(jtk_TestManager_t* manager,
    jtk_TestCase_t* testCase) {
    jtk_Assert_assertObject(manager, "The specified test manager is null.");
    jtk_Assert_assertObject(testCase, "The specified test case is null.");

    int32_t size = jtk_ArrayList_getSize(manager->m_listeners);
    int32_t i;
    for (i = 0; i < size; i++) {
        jtk_TestListener_t* listener = (jtk_TestListener_t*)jtk_ArrayList_getValue(manager->m_listeners, i);
        listener->m_onCaseError(listener, testCase);
    }
}

void jtk_TestManager_notifyOnCaseUnknownErrorListeners(jtk_TestManager_t* manager,
    jtk_TestCase_t* testCase) {
    jtk_Assert_assertObject(manager, "The specified test manager is null.");
    jtk_Assert_assertObject(testCase, "The specified test case is null.");

    int32_t size = jtk_ArrayList_getSize(manager->m_listeners);
    int32_t i;
    for (i = 0; i < size; i++) {
        jtk_TestListener_t* listener = (jtk_TestListener_t*)jtk_ArrayList_getValue(manager->m_listeners, i);
        listener->m_onCaseUnknownError(listener, testCase);
    }
}

/* Run Case */

void jtk_TestManager_runCase(jtk_TestManager_t* manager, jtk_TestCase_t* testCase) {
    jtk_Assert_assertObject(manager, "The specified test manager is null.");
    jtk_Assert_assertObject(testCase, "The specified test case is null.");

    jmp_buf jumpBuffer;
    testCase->m_jumpBuffer = &jumpBuffer;

    jtk_TestManager_notifyOnEnterCaseListeners(manager, testCase);

    int32_t jumpCode = setjmp(jumpBuffer);
    switch (jumpCode) {
        case 0: {
            jtk_TestCase_setUpFixture(testCase);

            jtk_Assert_assertTrue(((testCase->m_internalFlags & JTK_TEST_CASE_FLAG_READY) != 0),
                "The specified test case is not initialized.");
            jtk_Assert_assertTrue(((testCase->m_internalFlags & JTK_TEST_CASE_FLAG_DIRTY) == 0),
                "The specified test case was previously executed.");

            /* Each test case can be run only once. Therefore, we mark this test case
             * as dirty.
             */
            testCase->m_internalFlags |= JTK_TEST_CASE_FLAG_DIRTY;

            /* Run the user defined test statements. The assert statements are wired
             * to automatically jump out of the function in case of any failure, known
             * errors, or some other unknown errors.
             */
            void* bundle = NULL;
            if (testCase->m_fixture != NULL) {
                bundle = jtk_TestFixture_getBundle(testCase->m_fixture);
            }
            testCase->m_target(testCase, bundle);

            /* Since we still have control, the test case must have been successful.
             * Mark the test case to be successful.
             */
            testCase->m_internalFlags |= JTK_TEST_CASE_FLAG_SUCCESSFUL;
            /* Notify all the registered listeners regarding the success of this
             * test case.
             */
            jtk_TestManager_notifyOnCaseSuccessListeners(manager, testCase);

            break;
        }

        case JTK_TEST_CASE_FLAG_FAILURE: {
            testCase->m_internalFlags |= JTK_TEST_CASE_FLAG_FAILURE;
            /* Notify all the registered listeners regarding the failure of this
             * test case.
             */
            jtk_TestManager_notifyOnCaseFailureListeners(manager, testCase);

            break;
        }

        case JTK_TEST_CASE_FLAG_ERROR: {
            testCase->m_internalFlags |= JTK_TEST_CASE_FLAG_ERROR;
            break;
        }

        case JTK_TEST_CASE_FLAG_UNKNOWN_ERROR: {
            testCase->m_internalFlags |= JTK_TEST_CASE_FLAG_UNKNOWN_ERROR;
            break;
        }

        default : {
            // LOG: "The test case long jumped with an unknown jump code."

            break;
        }
    }

    /* Tear down the fixture regardless of the test case being successful,
     * or not.
     */
    jtk_TestCase_tearDownFixture(testCase);

    /* Invalidate the jump buffer. */
    testCase->m_jumpBuffer = NULL;

    jtk_TestManager_notifyOnExitCaseListeners(manager, testCase);
}

/* Run Suite */

static void jtk_TestManager_runSuite0(jtk_TestManager_t* manager, jtk_TestSuite_t* suite) {
    jtk_Assert_assertTrue(((suite->m_internalFlags & JTK_TEST_SUITE_FLAG_READY) != 0),
            "The specified test suite is not initialized.");
    jtk_Assert_assertTrue(((suite->m_internalFlags & JTK_TEST_SUITE_FLAG_DIRTY) == 0),
        "The specified test suite was previously executed.");

    /* Each test suite can be run only once. Therefore, we mark the current
     * test suite as dirty.
     */
    suite->m_internalFlags |= JTK_TEST_SUITE_FLAG_DIRTY;

    /* Notify all the registered listeners that a suite of test cases
     * are about to be executed.
     */
    jtk_TestManager_notifyOnEnterSuiteListeners(manager, suite);

    bool successful = true;
    int32_t numberOfCases = jtk_ArrayList_getSize(suite->m_testCases);
    int32_t i;
    for (i = 0; i < numberOfCases; i++) {
        jtk_TestCase_t* testCase = (jtk_TestCase_t*)jtk_ArrayList_getValue(suite->m_testCases, i);
        jtk_TestManager_runCase(manager, testCase);
        if (!jtk_TestCase_isSuccessful(testCase)) {
            successful = false;
        }
    }
    suite->m_internalFlags |= (successful? JTK_TEST_SUITE_FLAG_SUCCESSFUL : 0);

    jtk_ArrayList_t* childrenSuites = jtk_TestSuite_getSuites(suite);
    int32_t numberOfSuites = jtk_ArrayList_getSize(childrenSuites);
    int32_t j;
    for (j = 0; j < numberOfSuites; j++) {
        jtk_TestSuite_t* childSuite = (jtk_TestSuite_t*)jtk_ArrayList_getValue(childrenSuites, j);
        jtk_TestManager_runSuite0(manager, childSuite);
    }

    jtk_TestManager_notifyOnExitSuiteListeners(manager, suite);
}

void jtk_TestManager_runSuite(jtk_TestManager_t* manager, jtk_TestSuite_t* suite) {
    jtk_Assert_assertObject(manager, "The specified test manager is null.");
    jtk_Assert_assertObject(suite, "The specified test suite is null.");

    /*
    jtk_TestManager_notifyOnStartListeners(manager);

    jtk_LinkedStack_t* stack = jtk_LinkedStack_new();
    jtk_LinkedStack_push(stack, suite);
    while (!jtk_LinkedStack_isEmpty(stack)) {
        jtk_TestSuite_t* currentSuite = (jtk_TestSuite_t*)jtk_LinkedStack_pop(stack);

        jtk_Assert_assertTrue(((currentSuite->m_internalFlags & JTK_TEST_SUITE_FLAG_READY) != 0),
            "The specified test suite is not initialized.");
        jtk_Assert_assertTrue(((currentSuite->m_internalFlags & JTK_TEST_SUITE_FLAG_DIRTY) == 0),
            "The specified test suite was previously executed.");

        /* Each test suite can be run only once. Therefore, we mark the current
         * test suite as dirty.
         *
        currentSuite->m_internalFlags |= JTK_TEST_SUITE_FLAG_DIRTY;

        /* Notify all the registered listeners that a suite of test cases
         * are about to be executed.
         *
        jtk_TestManager_notifyOnEnterSuiteListeners(manager, currentSuite);

        bool successful = true;
        int32_t numberOfCases = jtk_ArrayList_getSize(currentSuite->m_testCases);
        int32_t i;
        for (i = 0; i < numberOfCases; i++) {
            jtk_TestCase_t* testCase = (jtk_TestCase_t*)jtk_ArrayList_getValue(currentSuite->m_testCases, i);
            jtk_TestManager_runCase(manager, testCase);
            if (!jtk_TestCase_isSuccessful(testCase)) {
                successful = false;
            }
        }
        currentSuite->m_internalFlags |= (successful? JTK_TEST_SUITE_FLAG_SUCCESSFUL : 0);

        jtk_ArrayList_t* childrenSuites = jtk_TestSuite_getSuites(currentSuite);
        jtk_LinkedStack_addAll(stack, JTK_COLLECTION_ARRAY_LIST, childrenSuites);

        jtk_TestManager_notifyOnExitSuiteListeners(manager, currentSuite);
    }
    jtk_LinkedStack_delete(stack);

    jtk_TestManager_notifyOnStopListeners(manager);
    */
    
    jtk_TestManager_notifyOnStartListeners(manager);
    
    jtk_TestManager_runSuite0(manager, suite);
    
    jtk_TestManager_notifyOnStopListeners(manager);
}