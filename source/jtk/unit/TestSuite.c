/*
 * Copyright 2017-2020 Samuel Rowe
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

// Tuesday, May 22, 2018

#include <jtk/collection/stack/LinkedStack.h>
#include <jtk/unit/TestSuite.h>

/*******************************************************************************
 * TestSuite                                                                   *
 *******************************************************************************/

/* Constructor */

jtk_TestSuite_t* jtk_TestSuite_new(const uint8_t* name) {
    jtk_TestSuite_t* suite = jtk_Memory_allocate(jtk_TestSuite_t, 1);
    suite->m_testCases = jtk_ArrayList_new();
    suite->m_testSuites = jtk_ArrayList_new();
    suite->m_internalFlags = JTK_TEST_SUITE_FLAG_READY;
    suite->m_name = jtk_String_new(name);

    return suite;
}

/* Destructor */

void jtk_TestSuite_delete(jtk_TestSuite_t* suite) {
    jtk_Assert_assertObject(suite, "The specified test suite is null.");

    jtk_ArrayList_delete(suite->m_testCases);
    jtk_ArrayList_delete(suite->m_testSuites);
    jtk_Memory_deallocate(suite);
}

/* Case Count */

int32_t jtk_TestSuite_getCaseCount(jtk_TestSuite_t* suite) {
    jtk_Assert_assertObject(suite, "The specified test suite is null.");

    return jtk_ArrayList_getSize(suite->m_testCases);
}

int32_t jtk_TestSuite_countAllCases(jtk_TestSuite_t* suite) {
    jtk_Assert_assertObject(suite, "The specified test suite is null.");

    int32_t result = 0;
    jtk_LinkedStack_t* stack = jtk_LinkedStack_new();
    jtk_LinkedStack_push(stack, suite);
    while (!jtk_LinkedStack_isEmpty(stack)) {
        jtk_TestSuite_t* currentSuite = (jtk_TestSuite_t*)jtk_LinkedStack_pop(stack);

        jtk_ArrayList_t* childrenCases = currentSuite->m_testCases;
        result += jtk_ArrayList_getSize(childrenCases);

        jtk_ArrayList_t* childrenSuites = currentSuite->m_testSuites;
        jtk_LinkedStack_addAll(stack, JTK_COLLECTION_ARRAY_LIST, childrenSuites);
    }
    jtk_LinkedStack_delete(stack);

    return result;
}

/* Fixture */

void jtk_TestSuite_applyFixture(jtk_TestSuite_t* suite, jtk_TestFixture_t* fixture) {
    jtk_TestSuite_applyFixturePredicatively(suite, fixture, NULL);
}

void jtk_TestSuite_applyFixturePredicatively(jtk_TestSuite_t* suite,
    jtk_TestFixture_t* fixture, jtk_MixedPredicateFunction_t predicate) {
    jtk_Assert_assertObject(suite, "The specified test suite is null.");

    jtk_LinkedStack_t* stack = jtk_LinkedStack_new();
    jtk_LinkedStack_push(stack, suite);
    while (!jtk_LinkedStack_isEmpty(stack)) {
        jtk_TestSuite_t* currentSuite = (jtk_TestSuite_t*)jtk_LinkedStack_pop(stack);

        jtk_ArrayList_t* childrenCases = currentSuite->m_testCases;
        int32_t childrenCaseCount = jtk_ArrayList_getSize(childrenCases);
        for (int32_t i = 0; i < childrenCaseCount; i++) {
            jtk_TestCase_t* testCase = (jtk_TestCase_t*)jtk_ArrayList_getValue(childrenCases, i);
            if ((predicate == NULL) || predicate(testCase)) {
                jtk_TestCase_setFixture(testCase, fixture);
            }
        }

        jtk_ArrayList_t* childrenSuites = currentSuite->m_testSuites;
        jtk_LinkedStack_addAll(stack, JTK_COLLECTION_ARRAY_LIST, childrenSuites);
    }
    jtk_LinkedStack_delete(stack);
}

/* Name */

void jtk_TestSuite_setName(jtk_TestSuite_t* suite, const uint8_t* name) {
    jtk_Assert_assertObject(suite, "The specified test suite is null.");

    suite->m_name = jtk_String_new(name);
}

const uint8_t* jtk_TestSuite_getName(jtk_TestSuite_t* suite) {
    jtk_Assert_assertObject(suite, "The specified test suite is null.");

    return suite->m_name;
}

/* Successful */

bool jtk_TestSuite_isSuccessful(jtk_TestSuite_t* suite) {
    jtk_Assert_assertObject(suite, "The specified test suite is null.");

    return (suite->m_internalFlags & JTK_TEST_SUITE_FLAG_SUCCESSFUL) != 0;
}

bool jtk_TestSuite_isCompletelySuccessful(jtk_TestSuite_t* suite) {
    jtk_Assert_assertObject(suite, "The specified test suite is null.");

    bool result = true;
    jtk_LinkedStack_t* stack = jtk_LinkedStack_new();
    jtk_LinkedStack_push(stack, suite);
    while (!jtk_LinkedStack_isEmpty(stack)) {
        jtk_TestSuite_t* currentSuite = (jtk_TestSuite_t*)jtk_LinkedStack_pop(stack);

        if ((currentSuite->m_internalFlags & JTK_TEST_SUITE_FLAG_SUCCESSFUL) != 0) {
            jtk_ArrayList_t* childrenSuites = currentSuite->m_testSuites;
            jtk_LinkedStack_addAll(stack, JTK_COLLECTION_ARRAY_LIST, childrenSuites);
        }
        else {
            result = false;
            break;
        }
    }
    jtk_LinkedStack_delete(stack);
    return result;
}

bool jtk_TestSuite_isPartiallySuccessful(jtk_TestSuite_t* suite) {
    jtk_Assert_assertObject(suite, "The specified test suite is null.");

    bool result = false;
    jtk_LinkedStack_t* stack = jtk_LinkedStack_new();
    jtk_LinkedStack_push(stack, suite);
    while (!jtk_LinkedStack_isEmpty(stack)) {
        jtk_TestSuite_t* currentSuite = (jtk_TestSuite_t*)jtk_LinkedStack_pop(stack);

        if ((currentSuite->m_internalFlags & JTK_TEST_SUITE_FLAG_SUCCESSFUL) != 0) {
            result = true;
            break;
        }

        jtk_ArrayList_t* childrenSuites = currentSuite->m_testSuites;
        jtk_LinkedStack_addAll(stack, JTK_COLLECTION_ARRAY_LIST, childrenSuites);
    }
    jtk_LinkedStack_delete(stack);
    return result;
}

/* Suite Count */

int32_t jtk_TestSuite_getSuiteCount(jtk_TestSuite_t* suite) {
    jtk_Assert_assertObject(suite, "The specified test suite is null.");

    return jtk_ArrayList_getSize(suite->m_testSuites);
}

int32_t jtk_TestSuite_countAllSuites(jtk_TestSuite_t* suite) {
    jtk_Assert_assertObject(suite, "The specified test suite is null.");

    int32_t result = 0;
    jtk_LinkedStack_t* stack = jtk_LinkedStack_new();
    jtk_LinkedStack_push(stack, suite);
    while (!jtk_LinkedStack_isEmpty(stack)) {
        jtk_TestSuite_t* currentSuite = (jtk_TestSuite_t*)jtk_LinkedStack_pop(stack);
        jtk_ArrayList_t* childrenSuites = currentSuite->m_testSuites;
        result += jtk_ArrayList_getSize(childrenSuites);
        jtk_LinkedStack_addAll(stack, JTK_COLLECTION_ARRAY_LIST, childrenSuites);
    }
    jtk_LinkedStack_delete(stack);
    return result;
}

/* Test Case */

void jtk_TestSuite_addCase(jtk_TestSuite_t* suite, jtk_TestCase_t* testCase) {
    jtk_Assert_assertObject(suite, "The specified test suite is null.");
    jtk_Assert_assertObject(testCase, "The specified test case is null.");

    jtk_ArrayList_add(suite->m_testCases, testCase);
}

jtk_ArrayList_t* jtk_TestSuite_getCases(jtk_TestSuite_t* suite) {
    jtk_Assert_assertObject(suite, "The specified test suite is null.");

    return suite->m_testCases;
}

/* Test Suite */

/* WARNING: Enforces no constraints to prevent parent suites from being added
 * to children suites.
 */
void jtk_TestSuite_addSuite(jtk_TestSuite_t* suite, jtk_TestSuite_t* other) {
    jtk_Assert_assertObject(suite, "The specified test suite is null.");

    jtk_ArrayList_add(suite->m_testSuites, other);
}

jtk_ArrayList_t* jtk_TestSuite_getSuites(jtk_TestSuite_t* suite) {
    jtk_Assert_assertObject(suite, "The specified test suite is null.");

    return suite->m_testSuites;
}