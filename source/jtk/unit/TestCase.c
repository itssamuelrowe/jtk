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

#include <setjmp.h>
#include <jtk/core/Double.h>
#include <jtk/core/Float.h>
#include <jtk/core/CString.h>
#include <jtk/unit/TestCase.h>

/*******************************************************************************
 * TestCase                                                                    *
 *******************************************************************************/

/* Constructor */

jtk_TestCase_t* jtk_TestCase_new(const uint8_t* name,
    jtk_TestFixture_t* fixture, jtk_TestCaseTargetFunction_t target) {
    jtk_Assert_assertObject(name, "The specified name is null.");

    jtk_TestCase_t* testCase = jtk_Memory_allocate(jtk_TestCase_t, 1);
    testCase->m_name = jtk_CString_new(name);
    testCase->m_fixture = fixture;
    testCase->m_target = target;
    testCase->m_jumpBuffer = NULL;
    testCase->m_internalFlags = JTK_TEST_CASE_FLAG_READY;
    testCase->m_defect = NULL;

    return testCase;
}

/* Destructor */

void jtk_TestCase_delete(jtk_TestCase_t* testCase) {
    jtk_Assert_assertObject(testCase, "The specified test case is null.");

    if (testCase->m_defect != NULL) {
        jtk_TestDefect_delete(testCase->m_defect);
    }

    jtk_CString_delete(testCase->m_name);
    jtk_Memory_deallocate(testCase);
}

/* Assert Equals */

void jtk_TestCase_assertEquals0(jtk_TestCase_t* testCase, void* actualValue,
    void* expectedValue, jtk_ComparatorFunction_t comparator,
    const uint8_t* sourceCodePath, int32_t lineNumber) {
    jtk_Assert_assertObject(testCase, "The specified test case is null.");

    if (((comparator != NULL) && (comparator(actualValue, expectedValue) != 0)) ||
        (actualValue != expectedValue)) {
        jtk_TestCase_fail(testCase, sourceCodePath, lineNumber, NULL);
    }
}

void jtk_TestCase_assertEquals_z0(jtk_TestCase_t* testCase, bool actualValue,
    bool expectedValue, const uint8_t* sourceCodePath, int32_t lineNumber) {
    jtk_Assert_assertObject(testCase, "The specified test case is null.");

    if (actualValue != expectedValue) {
        jtk_TestCase_fail(testCase, sourceCodePath, lineNumber, NULL);
    }
}

void jtk_TestCase_assertEquals_b0(jtk_TestCase_t* testCase, int8_t actualValue,
    int8_t expectedValue, const uint8_t* sourceCodePath, int32_t lineNumber) {
    jtk_Assert_assertObject(testCase, "The specified test case is null.");

    if (actualValue != expectedValue) {
        jtk_TestCase_fail(testCase, sourceCodePath, lineNumber, NULL);
    }
}

void jtk_TestCase_assertEquals_s0(jtk_TestCase_t* testCase, int16_t actualValue,
    int16_t expectedValue, const uint8_t* sourceCodePath, int32_t lineNumber) {
    jtk_Assert_assertObject(testCase, "The specified test case is null.");

    if (actualValue != expectedValue) {
        jtk_TestCase_fail(testCase, sourceCodePath, lineNumber, NULL);
    }
}

void jtk_TestCase_assertEquals_i0(jtk_TestCase_t* testCase, int32_t actualValue,
    int32_t expectedValue, const uint8_t* sourceCodePath, int32_t lineNumber) {
    jtk_Assert_assertObject(testCase, "The specified test case is null.");

    if (actualValue != expectedValue) {
        jtk_TestCase_fail(testCase, sourceCodePath, lineNumber, NULL);
    }
}

void jtk_TestCase_assertEquals_l0(jtk_TestCase_t* testCase, int64_t actualValue,
    int64_t expectedValue, const uint8_t* sourceCodePath, int32_t lineNumber) {
    jtk_Assert_assertObject(testCase, "The specified test case is null.");

    if (actualValue != expectedValue) {
        jtk_TestCase_fail(testCase, sourceCodePath, lineNumber, NULL);
    }
}

void jtk_TestCase_assertEquals_f0(jtk_TestCase_t* testCase, float actualValue,
    float expectedValue, const uint8_t* sourceCodePath, int32_t lineNumber) {
    jtk_Assert_assertObject(testCase, "The specified test case is null.");

    if (!jtk_Float_equals(actualValue, expectedValue)) {
        jtk_TestCase_fail(testCase, sourceCodePath, lineNumber, NULL);
    }
}

void jtk_TestCase_assertEquals_d0(jtk_TestCase_t* testCase, double actualValue,
    double expectedValue, const uint8_t* sourceCodePath, int32_t lineNumber) {
    jtk_Assert_assertObject(testCase, "The specified test case is null.");

    if (!jtk_Double_equals(actualValue, expectedValue)) {
        jtk_TestCase_fail(testCase, sourceCodePath, lineNumber, NULL);
    }
}

void jtk_TestCase_assertEquals_v0(jtk_TestCase_t* testCase, void* actualValue,
    void* expectedValue, const uint8_t* sourceCodePath, int32_t lineNumber) {
    jtk_Assert_assertObject(testCase, "The specified test case is null.");

    if (actualValue != expectedValue) {
        jtk_TestCase_fail(testCase, sourceCodePath, lineNumber, NULL);
    }
}

void jtk_TestCase_assertEquals_utf80(jtk_TestCase_t* testCase,
    const uint8_t* actualValue, const uint8_t* expectedValue,
    const uint8_t* sourceCodePath, int32_t lineNumber) {
    jtk_Assert_assertObject(testCase, "The specified test case is null.");

    if (!jtk_CString_equals(actualValue, jtk_CString_getSize(actualValue), expectedValue, jtk_CString_getSize(expectedValue))) {
        jtk_TestCase_fail(testCase, sourceCodePath, lineNumber, NULL);
    }
}

/* Assert Equals Extended */

void jtk_TestCase_assertEqualsEx0(jtk_TestCase_t* testCase, void* actualValue,
    void* expectedValue, jtk_ComparatorFunction_t comparator,
    const uint8_t* sourceCodePath, int32_t lineNumber, const uint8_t* message) {
    jtk_Assert_assertObject(testCase, "The specified test case is null.");

    if (((comparator != NULL) && (comparator(actualValue, expectedValue) != 0)) ||
        (actualValue != expectedValue)) {
        jtk_TestCase_fail(testCase, sourceCodePath, lineNumber, message);
    }
}

void jtk_TestCase_assertEqualsEx_z0(jtk_TestCase_t* testCase, bool actualValue,
    bool expectedValue, const uint8_t* sourceCodePath, int32_t lineNumber,
    const uint8_t* message) {
    jtk_Assert_assertObject(testCase, "The specified test case is null.");

    if (actualValue != expectedValue) {
        jtk_TestCase_fail(testCase, sourceCodePath, lineNumber, message);
    }
}

void jtk_TestCase_assertEqualsEx_b0(jtk_TestCase_t* testCase, int8_t actualValue,
    int8_t expectedValue, const uint8_t* sourceCodePath, int32_t lineNumber,
    const uint8_t* message) {
    jtk_Assert_assertObject(testCase, "The specified test case is null.");

    if (actualValue != expectedValue) {
        jtk_TestCase_fail(testCase, sourceCodePath, lineNumber, message);
    }
}

void jtk_TestCase_assertEqualsEx_s0(jtk_TestCase_t* testCase, int16_t actualValue,
    int16_t expectedValue, const uint8_t* sourceCodePath, int32_t lineNumber,
    const uint8_t* message) {
    jtk_Assert_assertObject(testCase, "The specified test case is null.");

    if (actualValue != expectedValue) {
        jtk_TestCase_fail(testCase, sourceCodePath, lineNumber, message);
    }
}

void jtk_TestCase_assertEqualsEx_i0(jtk_TestCase_t* testCase, int32_t actualValue,
    int32_t expectedValue, const uint8_t* sourceCodePath, int32_t lineNumber,
    const uint8_t* message) {
    jtk_Assert_assertObject(testCase, "The specified test case is null.");

    if (actualValue != expectedValue) {
        jtk_TestCase_fail(testCase, sourceCodePath, lineNumber, message);
    }
}

void jtk_TestCase_assertEqualsEx_l0(jtk_TestCase_t* testCase, int64_t actualValue,
    int64_t expectedValue, const uint8_t* sourceCodePath, int32_t lineNumber,
    const uint8_t* message) {
    jtk_Assert_assertObject(testCase, "The specified test case is null.");

    if (actualValue != expectedValue) {
        jtk_TestCase_fail(testCase, sourceCodePath, lineNumber, message);
    }
}

void jtk_TestCase_assertEqualsEx_f0(jtk_TestCase_t* testCase, float actualValue,
    float expectedValue, const uint8_t* sourceCodePath, int32_t lineNumber,
    const uint8_t* message) {
    jtk_Assert_assertObject(testCase, "The specified test case is null.");

    if (!jtk_Float_equals(actualValue, expectedValue)) {
        jtk_TestCase_fail(testCase, sourceCodePath, lineNumber, message);
    }
}

void jtk_TestCase_assertEqualsEx_d0(jtk_TestCase_t* testCase, double actualValue,
    double expectedValue, const uint8_t* sourceCodePath, int32_t lineNumber,
    const uint8_t* message) {
    jtk_Assert_assertObject(testCase, "The specified test case is null.");

    if (!jtk_Double_equals(actualValue, expectedValue)) {
        jtk_TestCase_fail(testCase, sourceCodePath, lineNumber, message);
    }
}

void jtk_TestCase_assertEqualsEx_v0(jtk_TestCase_t* testCase, void* actualValue,
    void* expectedValue, const uint8_t* sourceCodePath, int32_t lineNumber,
    const uint8_t* message) {
    jtk_Assert_assertObject(testCase, "The specified test case is null.");

    if (actualValue != expectedValue) {
        jtk_TestCase_fail(testCase, sourceCodePath, lineNumber, NULL);
    }
}

void jtk_TestCase_assertEqualsEx_utf80(jtk_TestCase_t* testCase,
    const uint8_t* actualValue, const uint8_t* expectedValue,
    const uint8_t* sourceCodePath, int32_t lineNumber, const uint8_t* message) {
    jtk_Assert_assertObject(testCase, "The specified test case is null.");

    if (!jtk_CString_equals(actualValue, jtk_CString_getSize(actualValue), expectedValue, jtk_CString_getSize(expectedValue))) {
        jtk_TestCase_fail(testCase, sourceCodePath, lineNumber, NULL);
    }
}

/* Assert Not Equals */

void jtk_TestCase_assertNotEquals0(jtk_TestCase_t* testCase, void* actualValue,
    void* expectedValue, jtk_ComparatorFunction_t comparator,
    const uint8_t* sourceCodePath, int32_t lineNumber) {
    jtk_Assert_assertObject(testCase, "The specified test case is null.");

    if (((comparator != NULL) && (comparator(actualValue, expectedValue) == 0)) ||
        (actualValue == expectedValue)) {
        jtk_TestCase_fail(testCase, sourceCodePath, lineNumber, NULL);
    }
}

void jtk_TestCase_assertNotEquals_z0(jtk_TestCase_t* testCase, bool actualValue,
    bool expectedValue, const uint8_t* sourceCodePath, int32_t lineNumber) {
    jtk_Assert_assertObject(testCase, "The specified test case is null.");

    if (actualValue == expectedValue) {
        jtk_TestCase_fail(testCase, sourceCodePath, lineNumber, NULL);
    }
}

void jtk_TestCase_assertNotEquals_b0(jtk_TestCase_t* testCase, int8_t actualValue,
    int8_t expectedValue, const uint8_t* sourceCodePath, int32_t lineNumber) {
    jtk_Assert_assertObject(testCase, "The specified test case is null.");

    if (actualValue == expectedValue) {
        jtk_TestCase_fail(testCase, sourceCodePath, lineNumber, NULL);
    }
}

void jtk_TestCase_assertNotEquals_s0(jtk_TestCase_t* testCase, int16_t actualValue,
    int16_t expectedValue, const uint8_t* sourceCodePath, int32_t lineNumber) {
    jtk_Assert_assertObject(testCase, "The specified test case is null.");

    if (actualValue == expectedValue) {
        jtk_TestCase_fail(testCase, sourceCodePath, lineNumber, NULL);
    }
}

void jtk_TestCase_assertNotEquals_i0(jtk_TestCase_t* testCase, int32_t actualValue,
    int32_t expectedValue, const uint8_t* sourceCodePath, int32_t lineNumber) {
    jtk_Assert_assertObject(testCase, "The specified test case is null.");

    if (actualValue == expectedValue) {
        jtk_TestCase_fail(testCase, sourceCodePath, lineNumber, NULL);
    }
}

void jtk_TestCase_assertNotEquals_l0(jtk_TestCase_t* testCase, int64_t actualValue,
    int64_t expectedValue, const uint8_t* sourceCodePath, int32_t lineNumber) {
    jtk_Assert_assertObject(testCase, "The specified test case is null.");

    if (actualValue == expectedValue) {
        jtk_TestCase_fail(testCase, sourceCodePath, lineNumber, NULL);
    }
}

void jtk_TestCase_assertNotEquals_f0(jtk_TestCase_t* testCase, float actualValue,
    float expectedValue, const uint8_t* sourceCodePath, int32_t lineNumber) {
    jtk_Assert_assertObject(testCase, "The specified test case is null.");

    if (jtk_Float_equals(actualValue, expectedValue)) {
        jtk_TestCase_fail(testCase, sourceCodePath, lineNumber, NULL);
    }
}

void jtk_TestCase_assertNotEquals_d0(jtk_TestCase_t* testCase, double actualValue,
    double expectedValue, const uint8_t* sourceCodePath, int32_t lineNumber) {
    jtk_Assert_assertObject(testCase, "The specified test case is null.");

    if (jtk_Double_equals(actualValue, expectedValue)) {
        jtk_TestCase_fail(testCase, sourceCodePath, lineNumber, NULL);
    }
}

void jtk_TestCase_assertNotEquals_v0(jtk_TestCase_t* testCase, void* actualValue,
    void* expectedValue, const uint8_t* sourceCodePath, int32_t lineNumber) {
    jtk_Assert_assertObject(testCase, "The specified test case is null.");

    if (actualValue == expectedValue) {
        jtk_TestCase_fail(testCase, sourceCodePath, lineNumber, NULL);
    }
}

void jtk_TestCase_assertNotEquals_utf80(jtk_TestCase_t* testCase,
    const uint8_t* actualValue, const uint8_t* expectedValue,
    const uint8_t* sourceCodePath, int32_t lineNumber) {
    jtk_Assert_assertObject(testCase, "The specified test case is null.");

    if (jtk_CString_equals(actualValue, jtk_CString_getSize(actualValue), expectedValue, jtk_CString_getSize(expectedValue))) {
        jtk_TestCase_fail(testCase, sourceCodePath, lineNumber, NULL);
    }
}

/* Assert Not Equals Extended */

void jtk_TestCase_assertNotEqualsEx0(jtk_TestCase_t* testCase, void* actualValue,
    void* expectedValue, jtk_ComparatorFunction_t comparator,
    const uint8_t* sourceCodePath, int32_t lineNumber, const uint8_t* message) {
    jtk_Assert_assertObject(testCase, "The specified test case is null.");

    if (((comparator != NULL) && (comparator(actualValue, expectedValue) == 0)) ||
        (actualValue == expectedValue)) {
        jtk_TestCase_fail(testCase, sourceCodePath, lineNumber, message);
    }
}

void jtk_TestCase_assertNotEqualsEx_z0(jtk_TestCase_t* testCase, bool actualValue,
    bool expectedValue, const uint8_t* sourceCodePath, int32_t lineNumber,
    const uint8_t* message) {
    jtk_Assert_assertObject(testCase, "The specified test case is null.");

    if (actualValue == expectedValue) {
        jtk_TestCase_fail(testCase, sourceCodePath, lineNumber, message);
    }
}

void jtk_TestCase_assertNotEqualsEx_b0(jtk_TestCase_t* testCase, int8_t actualValue,
    int8_t expectedValue, const uint8_t* sourceCodePath, int32_t lineNumber,
    const uint8_t* message) {
    jtk_Assert_assertObject(testCase, "The specified test case is null.");

    if (actualValue == expectedValue) {
        jtk_TestCase_fail(testCase, sourceCodePath, lineNumber, message);
    }
}

void jtk_TestCase_assertNotEqualsEx_s0(jtk_TestCase_t* testCase, int16_t actualValue,
    int16_t expectedValue, const uint8_t* sourceCodePath, int32_t lineNumber,
    const uint8_t* message) {
    jtk_Assert_assertObject(testCase, "The specified test case is null.");

    if (actualValue == expectedValue) {
        jtk_TestCase_fail(testCase, sourceCodePath, lineNumber, message);
    }
}

void jtk_TestCase_assertNotEqualsEx_i0(jtk_TestCase_t* testCase, int32_t actualValue,
    int32_t expectedValue, const uint8_t* sourceCodePath, int32_t lineNumber,
    const uint8_t* message) {
    jtk_Assert_assertObject(testCase, "The specified test case is null.");

    if (actualValue == expectedValue) {
        jtk_TestCase_fail(testCase, sourceCodePath, lineNumber, message);
    }
}

void jtk_TestCase_assertNotEqualsEx_l0(jtk_TestCase_t* testCase, int64_t actualValue,
    int64_t expectedValue, const uint8_t* sourceCodePath, int32_t lineNumber,
    const uint8_t* message) {
    jtk_Assert_assertObject(testCase, "The specified test case is null.");

    if (actualValue == expectedValue) {
        jtk_TestCase_fail(testCase, sourceCodePath, lineNumber, message);
    }
}

void jtk_TestCase_assertNotEqualsEx_f0(jtk_TestCase_t* testCase, float actualValue,
    float expectedValue, const uint8_t* sourceCodePath, int32_t lineNumber,
    const uint8_t* message) {
    jtk_Assert_assertObject(testCase, "The specified test case is null.");

    if (jtk_Float_equals(actualValue, expectedValue)) {
        jtk_TestCase_fail(testCase, sourceCodePath, lineNumber, message);
    }
}

void jtk_TestCase_assertNotEqualsEx_d0(jtk_TestCase_t* testCase, double actualValue,
    double expectedValue, const uint8_t* sourceCodePath, int32_t lineNumber,
    const uint8_t* message) {
    jtk_Assert_assertObject(testCase, "The specified test case is null.");

    if (jtk_Double_equals(actualValue, expectedValue)) {
        jtk_TestCase_fail(testCase, sourceCodePath, lineNumber, message);
    }
}

void jtk_TestCase_assertNotEqualsEx_v0(jtk_TestCase_t* testCase, void* actualValue,
    void* expectedValue, const uint8_t* sourceCodePath, int32_t lineNumber,
    const uint8_t* message) {
    jtk_Assert_assertObject(testCase, "The specified test case is null.");

    if (actualValue == expectedValue) {
        jtk_TestCase_fail(testCase, sourceCodePath, lineNumber, message);
    }
}

void jtk_TestCase_assertNotEqualsEx_utf80(jtk_TestCase_t* testCase,
    const uint8_t* actualValue, const uint8_t* expectedValue,
    const uint8_t* sourceCodePath, int32_t lineNumber, const uint8_t* message) {
    jtk_Assert_assertObject(testCase, "The specified test case is null.");

    if (jtk_CString_equals(actualValue, jtk_CString_getSize(actualValue), expectedValue, jtk_CString_getSize(expectedValue))) {
        jtk_TestCase_fail(testCase, sourceCodePath, lineNumber, message);
    }
}

/* Assert Not Null */

void jtk_TestCase_assertNotNull0(jtk_TestCase_t* testCase, void* object,
    const uint8_t* sourceCodePath, int32_t lineNumber) {
    jtk_Assert_assertObject(testCase, "The specified test case is null.");

    if (object == NULL) {
        jtk_TestCase_fail(testCase, sourceCodePath, lineNumber, NULL);
    }
}

/* Assert Not Null Extended */

void jtk_TestCase_assertNotNullEx0(jtk_TestCase_t* testCase, void* object,
    const uint8_t* sourceCodePath, int32_t lineNumber, const uint8_t* message) {
    jtk_Assert_assertObject(testCase, "The specified test case is null.");

    if (object == NULL) {
        jtk_TestCase_fail(testCase, sourceCodePath, lineNumber, message);
    }
}

/* Assert Null */

void jtk_TestCase_assertNull0(jtk_TestCase_t* testCase, void* object,
    const uint8_t* sourceCodePath, int32_t lineNumber) {
    jtk_Assert_assertObject(testCase, "The specified test case is null.");

    if (object != NULL) {
        jtk_TestCase_fail(testCase, sourceCodePath, lineNumber, NULL);
    }
}

/* Assert Null Extended */

void jtk_TestCase_assertNullEx0(jtk_TestCase_t* testCase, void* object,
    const uint8_t* sourceCodePath, int32_t lineNumber, const uint8_t* message) {
    jtk_Assert_assertObject(testCase, "The specified test case is null.");

    if (object != NULL) {
        jtk_TestCase_fail(testCase, sourceCodePath, lineNumber, message);
    }
}

/* Assert True/False */

void jtk_TestCase_assertTrue0(jtk_TestCase_t* testCase, bool value,
    const uint8_t* sourceCodePath, int32_t lineNumber) {
    jtk_Assert_assertObject(testCase, "The specified test case is null.");

    if (!value) {
        jtk_TestCase_fail(testCase, sourceCodePath, lineNumber, NULL);
    }
}

void jtk_TestCase_assertFalse0(jtk_TestCase_t* testCase, bool value,
    const uint8_t* sourceCodePath, int32_t lineNumber) {
    jtk_Assert_assertObject(testCase, "The specified test case is null.");

    if (value) {
        jtk_TestCase_fail(testCase, sourceCodePath, lineNumber, NULL);
    }
}

/* Assert True/False Extended */

void jtk_TestCase_assertTrueEx0(jtk_TestCase_t* testCase, bool value,
    const uint8_t* sourceCodePath, int32_t lineNumber, const uint8_t* message) {
    jtk_Assert_assertObject(testCase, "The specified test case is null.");

    if (!value) {
        jtk_TestCase_fail(testCase, sourceCodePath, lineNumber, message);
    }
}

void jtk_TestCase_assertFalseEx0(jtk_TestCase_t* testCase, bool value,
    const uint8_t* sourceCodePath, int32_t lineNumber, const uint8_t* message) {
    jtk_Assert_assertObject(testCase, "The specified test case is null.");

    if (value) {
        jtk_TestCase_fail(testCase, sourceCodePath, lineNumber, message);
    }
}

/* Defect */

jtk_TestDefect_t* jtk_TestCase_getDefect(jtk_TestCase_t* testCase) {
    jtk_Assert_assertObject(testCase, "The specified test case is null.");

    return testCase->m_defect;
}

/* Flags */

bool jtk_TestCase_isReady(jtk_TestCase_t* testCase) {
    jtk_Assert_assertObject(testCase, "The specified test case is null.");

    return (testCase->m_internalFlags & JTK_TEST_CASE_FLAG_READY) != 0;
}

bool jtk_TestCase_isDirty(jtk_TestCase_t* testCase) {
    jtk_Assert_assertObject(testCase, "The specified test case is null.");

    return (testCase->m_internalFlags & JTK_TEST_CASE_FLAG_DIRTY) != 0;
}

bool jtk_TestCase_isSuccessful(jtk_TestCase_t* testCase) {
    jtk_Assert_assertObject(testCase, "The specified test case is null.");

    return (testCase->m_internalFlags & JTK_TEST_CASE_FLAG_SUCCESSFUL) != 0;
}

bool jtk_TestCase_isFailure(jtk_TestCase_t* testCase) {
    jtk_Assert_assertObject(testCase, "The specified test case is null.");

    return (testCase->m_internalFlags & JTK_TEST_CASE_FLAG_FAILURE) != 0;
}

bool jtk_TestCase_hasError(jtk_TestCase_t* testCase) {
    jtk_Assert_assertObject(testCase, "The specified test case is null.");

    return (testCase->m_internalFlags & JTK_TEST_CASE_FLAG_ERROR) != 0;
}

bool jtk_TestCase_hasUnknownError(jtk_TestCase_t* testCase) {
    jtk_Assert_assertObject(testCase, "The specified test case is null.");

    return (testCase->m_internalFlags & JTK_TEST_CASE_FLAG_UNKNOWN_ERROR) != 0;
}

void jtk_TestCase_setAllocatedResources(jtk_TestCase_t* testCase,
    bool allocatedResources) {
    jtk_Assert_assertObject(testCase, "The specified test case is null.");

    testCase->m_internalFlags = allocatedResources?
        (testCase->m_internalFlags | JTK_TEST_CASE_FLAG_ALLOCATED_RESOURCES) :
        (testCase->m_internalFlags & ~JTK_TEST_CASE_FLAG_ALLOCATED_RESOURCES);
}

bool jtk_TestCase_hasAllocatedResources(jtk_TestCase_t* testCase) {
    jtk_Assert_assertObject(testCase, "The specified test case is null.");

    return (testCase->m_internalFlags & JTK_TEST_CASE_FLAG_ALLOCATED_RESOURCES) != 0;
}

void jtk_TestCase_setDeallocatedResources(jtk_TestCase_t* testCase,
    bool deallocatedResources) {
    jtk_Assert_assertObject(testCase, "The specified test case is null.");

    testCase->m_internalFlags = deallocatedResources?
        (testCase->m_internalFlags | JTK_TEST_CASE_FLAG_DEALLOCATED_RESOURCES) :
        (testCase->m_internalFlags & ~JTK_TEST_CASE_FLAG_DEALLOCATED_RESOURCES);
}

bool jtk_TestCase_hasDeallocatedResources(jtk_TestCase_t* testCase,
    bool deallocatedResources) {
    jtk_Assert_assertObject(testCase, "The specified test case is null.");

    return (testCase->m_internalFlags & JTK_TEST_CASE_FLAG_DEALLOCATED_RESOURCES) != 0;
}

/* Fail */

void jtk_TestCase_fail(jtk_TestCase_t* testCase, const uint8_t* sourceCodePath,
    int32_t lineNumber, const uint8_t* message) {
    jtk_Assert_assertObject(testCase, "The specified test case is null.");
    jtk_Assert_assertObject(testCase->m_jumpBuffer, "Assertions must be done by a test case within the context of a test manager.");

    testCase->m_defect = jtk_TestDefect_newFailure(sourceCodePath, lineNumber, message);

    jmp_buf* jumpBuffer = (jmp_buf*)testCase->m_jumpBuffer;
    longjmp(*jumpBuffer, JTK_TEST_CASE_FLAG_FAILURE);
}

/* Fixture */

void jtk_TestCase_setFixture(jtk_TestCase_t* testCase,
    jtk_TestFixture_t* fixture) {
    jtk_Assert_assertObject(testCase, "The specified test case is null.");

    testCase->m_fixture = fixture;
}

jtk_TestFixture_t* jtk_TestCase_getFixture(jtk_TestCase_t* testCase) {
    jtk_Assert_assertObject(testCase, "The specified test case is null.");

    return testCase->m_fixture;
}

/* Name */

void jtk_TestCase_setName(jtk_TestCase_t* testCase, const uint8_t* name) {
    jtk_Assert_assertObject(testCase, "The specified test case is null.");
    jtk_Assert_assertObject(name, "The specified name is null.");

    jtk_CString_delete(testCase->m_name);
    testCase->m_name = jtk_CString_new(name);
}

const uint8_t* jtk_TestCase_getName(jtk_TestCase_t* testCase) {
    jtk_Assert_assertObject(testCase, "The specified test case is null.");

    return testCase->m_name;
}

/* Notify Fixture */

void jtk_TestCase_setUpFixture(jtk_TestCase_t* testCase) {
    jtk_Assert_assertObject(testCase, "The specified test case is null.");

    if (testCase->m_fixture != NULL) {
        testCase->m_fixture->m_setUp(testCase->m_fixture);
    }
}

void jtk_TestCase_tearDownFixture(jtk_TestCase_t* testCase) {
    jtk_Assert_assertObject(testCase, "The specified test case is null.");

    if (testCase->m_fixture != NULL) {
        testCase->m_fixture->m_tearDown(testCase->m_fixture);
    }
}