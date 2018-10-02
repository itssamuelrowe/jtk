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

// Monday, May 21, 2018

#ifndef JTK_UNIT_TEST_CASE_H
#define JTK_UNIT_TEST_CASE_H

#include <jtk/Configuration.h>
#include <jtk/collection/array/Array.h>
#include <jtk/function/ComparatorFunction.h>
#include <jtk/unit/TestDefect.h>
#include <jtk/unit/TestFixture.h>

/*******************************************************************************
 * TestCase                                                                    *
 *******************************************************************************/

/* Forward Reference */

typedef struct jtk_TestCase_t jtk_TestCase_t;

/**
 * @memberof TestCase
 */
typedef void (*jtk_TestCaseTargetFunction_t)(jtk_TestCase_t* testCase, void* bundle);

/**
 * @private
 * @memberof TestCase
 */
#define JTK_TEST_CASE_FLAG_READY (1 << 0)

/**
 * @private
 * @memberof TestCase
 */
#define JTK_TEST_CASE_FLAG_DIRTY (1 << 1)

/**
 * @private
 * @memberof TestCase
 */
#define JTK_TEST_CASE_FLAG_SUCCESSFUL (1 << 2)

/**
 * @private
 * @memberof TestCase
 */
#define JTK_TEST_CASE_FLAG_FAILURE (1 << 3)

/**
 * @private
 * @memberof TestCase
 */
#define JTK_TEST_CASE_FLAG_ERROR (1 << 4)

/**
 * @private
 * @memberof TestCase
 */
#define JTK_TEST_CASE_FLAG_UNKNOWN_ERROR (1 << 5)

/**
 * @private
 * @memberof TestCase
 */
#define JTK_TEST_CASE_FLAG_ALLOCATED_RESOURCES (1 << 6)

/**
 * @private
 * @memberof TestCase
 */
#define JTK_TEST_CASE_FLAG_DEALLOCATED_RESOURCES (1 << 7)

/**
 * @class TestCase
 * @ingroup jtk_unit
 * @author Samuel Rowe
 * @since JTK 1.0
 */
struct jtk_TestCase_t {
    uint8_t* m_name;
    uint8_t m_internalFlags;
    jtk_TestFixture_t* m_fixture;
    jtk_TestCaseTargetFunction_t m_target;
    void* m_jumpBuffer;
    jtk_TestDefect_t* m_defect;
};

/* Constructor */

/**
 * @memberof TestCase
 */
jtk_TestCase_t* jtk_TestCase_new(const uint8_t* name, jtk_TestFixture_t* fixture, jtk_TestCaseTargetFunction_t target);

/* Destructor */

/**
 * @memberof TestCase
 */
void jtk_TestCase_delete(jtk_TestCase_t* testCase);

/* Assert Array Equals */

/**
 * @private
 * @memberof TestCase
 */
void jtk_TestCase_assertArrayEquals0(jtk_TestCase_t* testCase, jtk_Array_t* actualValue, jtk_Array_t* expectedValue, const uint8_t* sourceCodePath, int32_t lineNumber);

/**
 * @private
 * @memberof TestCase
 */
void jtk_TestCase_assertArrayEquals_z0(jtk_TestCase_t* testCase, const bool* actualValue, int32_t actualSize, const bool* expectedValue, int32_t expectedSize, const uint8_t* sourceCodePath, int32_t lineNumber);

/**
 * @private
 * @memberof TestCase
 */
void jtk_TestCase_assertArrayEquals_b0(jtk_TestCase_t* testCase, const int8_t* actualValue, int32_t actualSize, const int8_t* expectedValue, int32_t expectedSize, const uint8_t* sourceCodePath, int32_t lineNumber);

/**
 * @private
 * @memberof TestCase
 */
void jtk_TestCase_assertArrayEquals_s0(jtk_TestCase_t* testCase, const int16_t* actualValue, int32_t actualSize, const int16_t* expectedValue, int32_t expectedSize, const uint8_t* sourceCodePath, int32_t lineNumber);

/**
 * @private
 * @memberof TestCase
 */
void jtk_TestCase_assertArrayEquals_i0(jtk_TestCase_t* testCase, const int32_t* actualValue, int32_t actualSize, const int32_t* expectedValue, int32_t expectedSize, const uint8_t* sourceCodePath, int32_t lineNumber);

/**
 * @private
 * @memberof TestCase
 */
void jtk_TestCase_assertArrayEquals_l0(jtk_TestCase_t* testCase, const int64_t* actualValue, int32_t actualSize, const int64_t* expectedValue, int32_t expectedSize, const uint8_t* sourceCodePath, int32_t lineNumber);

/**
 * @private
 * @memberof TestCase
 */
void jtk_TestCase_assertArrayEquals_f0(jtk_TestCase_t* testCase, const float* actualValue, int32_t actualSize, const float* expectedValue, int32_t expectedSize, const uint8_t* sourceCodePath, int32_t lineNumber);

/**
 * @private
 * @memberof TestCase
 */
void jtk_TestCase_assertArrayEquals_d0(jtk_TestCase_t* testCase, const double* actualValue, int32_t actualSize, const double* expectedValue, int32_t expectedSize, const uint8_t* sourceCodePath, int32_t lineNumber);

/**
 * @private
 * @memberof TestCase
 */
void jtk_TestCase_assertArrayEquals_v0(jtk_TestCase_t* testCase, const void** actualValue, int32_t actualSize, const void** expectedValue, int32_t expectedSize, const uint8_t* sourceCodePath, int32_t lineNumber);

/* Assert Array Equals Extended */

/**
 * @private
 * @memberof TestCase
 */
void jtk_TestCase_assertArrayEqualsEx0(jtk_TestCase_t* testCase, jtk_Array_t* actualValue, jtk_Array_t* expectedValue, const uint8_t* sourceCodePath, int32_t lineNumber, const uint8_t* message);

/**
 * @private
 * @memberof TestCase
 */
void jtk_TestCase_assertArrayEqualsEx_z0(jtk_TestCase_t* testCase, const bool* actualValue, int32_t actualSize, const bool* expectedValue, int32_t expectedSize, const uint8_t* sourceCodePath, int32_t lineNumber, const uint8_t* message);

/**
 * @private
 * @memberof TestCase
 */
void jtk_TestCase_assertArrayEqualsEx_b0(jtk_TestCase_t* testCase, const int8_t* actualValue, int32_t actualSize, const int8_t* expectedValue, int32_t expectedSize, const uint8_t* sourceCodePath, int32_t lineNumber, const uint8_t* message);

/**
 * @private
 * @memberof TestCase
 */
void jtk_TestCase_assertArrayEqualsEx_s0(jtk_TestCase_t* testCase, const int16_t* actualValue, int32_t actualSize, const int16_t* expectedValue, int32_t expectedSize, const uint8_t* sourceCodePath, int32_t lineNumber, const uint8_t* message);

/**
 * @private
 * @memberof TestCase
 */
void jtk_TestCase_assertArrayEqualsEx_i0(jtk_TestCase_t* testCase, const int32_t* actualValue, int32_t actualSize, const int32_t* expectedValue, int32_t expectedSize, const uint8_t* sourceCodePath, int32_t lineNumber, const uint8_t* message);

/**
 * @private
 * @memberof TestCase
 */
void jtk_TestCase_assertArrayEqualsEx_l0(jtk_TestCase_t* testCase, const int64_t* actualValue, int32_t actualSize, const int64_t* expectedValue, int32_t expectedSize, const uint8_t* sourceCodePath, int32_t lineNumber, const uint8_t* message);

/**
 * @private
 * @memberof TestCase
 */
void jtk_TestCase_assertArrayEqualsEx_f0(jtk_TestCase_t* testCase, const float* actualValue, int32_t actualSize, const float* expectedValue, int32_t expectedSize, const uint8_t* sourceCodePath, int32_t lineNumber, const uint8_t* message);

/**
 * @private
 * @memberof TestCase
 */
void jtk_TestCase_assertArrayEqualsEx_d0(jtk_TestCase_t* testCase, const double* actualValue, int32_t actualSize, const double* expectedValue, int32_t expectedSize, const uint8_t* sourceCodePath, int32_t lineNumber, const uint8_t* message);

/**
 * @private
 * @memberof TestCase
 */
void jtk_TestCase_assertArrayEqualsEx_v0(jtk_TestCase_t* testCase, const void** actualValue, int32_t actualSize, const void** expectedValue, int32_t expectedSize, const uint8_t* sourceCodePath, int32_t lineNumber, const uint8_t* message);

/* Assert Equals */

/**
 * @private
 * @memberof TestCase
 */
void jtk_TestCase_assertEquals0(jtk_TestCase_t* testCase, void* actualValue, void* expectedValue, jtk_ComparatorFunction_t comparator, const uint8_t* sourceCodePath, int32_t lineNumber);

/**
 * @private
 * @memberof TestCase
 */
void jtk_TestCase_assertEquals_z0(jtk_TestCase_t* testCase, bool actualValue, bool expectedValue, const uint8_t* sourceCodePath, int32_t lineNumber);

/**
 * @private
 * @memberof TestCase
 */
void jtk_TestCase_assertEquals_b0(jtk_TestCase_t* testCase, int8_t actualValue, int8_t expectedValue, const uint8_t* sourceCodePath, int32_t lineNumber);

/**
 * @private
 * @memberof TestCase
 */
void jtk_TestCase_assertEquals_s0(jtk_TestCase_t* testCase, int16_t actualValue, int16_t expectedValue, const uint8_t* sourceCodePath, int32_t lineNumber);

/**
 * @private
 * @memberof TestCase
 */
void jtk_TestCase_assertEquals_i0(jtk_TestCase_t* testCase, int32_t actualValue, int32_t expectedValue, const uint8_t* sourceCodePath, int32_t lineNumber);

/**
 * @private
 * @memberof TestCase
 */
void jtk_TestCase_assertEquals_l0(jtk_TestCase_t* testCase, int64_t actualValue, int64_t expectedValue, const uint8_t* sourceCodePath, int32_t lineNumber);

/**
 * @private
 * @memberof TestCase
 */
void jtk_TestCase_assertEquals_f0(jtk_TestCase_t* testCase, float actualValue, float expectedValue, const uint8_t* sourceCodePath, int32_t lineNumber);

/**
 * @private
 * @memberof TestCase
 */
void jtk_TestCase_assertEquals_d0(jtk_TestCase_t* testCase, double actualValue, double expectedValue, const uint8_t* sourceCodePath, int32_t lineNumber);

/**
 * @private
 * @memberof TestCase
 */
void jtk_TestCase_assertEquals_v0(jtk_TestCase_t* testCase, void* actualValue, void* expectedValue, const uint8_t* sourceCodePath, int32_t lineNumber);

/**
 * @private
 * @memberof TestCase
 */
void jtk_TestCase_assertEquals_utf80(jtk_TestCase_t* testCase, const uint8_t* actualValue, const uint8_t* expectedValue, const uint8_t* sourceCodePath, int32_t lineNumber);

/* Assert Equals Extended */

/**
 * @private
 * @memberof TestCase
 */
void jtk_TestCase_assertEqualsEx0(jtk_TestCase_t* testCase, void* actualValue, void* expectedValue, jtk_ComparatorFunction_t comparator, const uint8_t* sourceCodePath, int32_t lineNumber, const uint8_t* message);

/**
 * @private
 * @memberof TestCase
 */
void jtk_TestCase_assertEqualsEx_z0(jtk_TestCase_t* testCase, bool actualValue, bool expectedValue, const uint8_t* sourceCodePath, int32_t lineNumber, const uint8_t* message);

/**
 * @private
 * @memberof TestCase
 */
void jtk_TestCase_assertEqualsEx_b0(jtk_TestCase_t* testCase, int8_t actualValue, int8_t expectedValue, const uint8_t* sourceCodePath, int32_t lineNumber, const uint8_t* message);

/**
 * @private
 * @memberof TestCase
 */
void jtk_TestCase_assertEqualsEx_s0(jtk_TestCase_t* testCase, int16_t actualValue, int16_t expectedValue, const uint8_t* sourceCodePath, int32_t lineNumber, const uint8_t* message);

/**
 * @private
 * @memberof TestCase
 */
void jtk_TestCase_assertEqualsEx_i0(jtk_TestCase_t* testCase, int32_t actualValue, int32_t expectedValue, const uint8_t* sourceCodePath, int32_t lineNumber, const uint8_t* message);

/**
 * @private
 * @memberof TestCase
 */
void jtk_TestCase_assertEqualsEx_l0(jtk_TestCase_t* testCase, int64_t actualValue, int64_t expectedValue, const uint8_t* sourceCodePath, int32_t lineNumber, const uint8_t* message);

/**
 * @private
 * @memberof TestCase
 */
void jtk_TestCase_assertEqualsEx_f0(jtk_TestCase_t* testCase, float actualValue, float expectedValue, const uint8_t* sourceCodePath, int32_t lineNumber, const uint8_t* message);

/**
 * @private
 * @memberof TestCase
 */
void jtk_TestCase_assertEqualsEx_d0(jtk_TestCase_t* testCase, double actualValue, double expectedValue, const uint8_t* sourceCodePath, int32_t lineNumber, const uint8_t* message);

/**
 * @private
 * @memberof TestCase
 */
void jtk_TestCase_assertEqualsEx_v0(jtk_TestCase_t* testCase, void* actualValue, void* expectedValue, const uint8_t* sourceCodePath, int32_t lineNumber, const uint8_t* message);

/**
 * @private
 * @memberof TestCase
 */
void jtk_TestCase_assertEqualsEx_utf80(jtk_TestCase_t* testCase, const uint8_t* actualValue, const uint8_t* expectedValue, const uint8_t* sourceCodePath, int32_t lineNumber, const uint8_t* message);

/* Assert Not Equals */

/**
 * @private
 * @memberof TestCase
 */
void jtk_TestCase_assertNotEquals_z0(jtk_TestCase_t* testCase, bool actualValue, bool expectedValue, const uint8_t* sourceCodePath, int32_t lineNumber);

/**
 * @private
 * @memberof TestCase
 */
void jtk_TestCase_assertNotEquals_b0(jtk_TestCase_t* testCase, int8_t actualValue, int8_t expectedValue, const uint8_t* sourceCodePath, int32_t lineNumber);

/**
 * @private
 * @memberof TestCase
 */
void jtk_TestCase_assertNotEquals_s0(jtk_TestCase_t* testCase, int16_t actualValue, int16_t expectedValue, const uint8_t* sourceCodePath, int32_t lineNumber);

/**
 * @private
 * @memberof TestCase
 */
void jtk_TestCase_assertNotEquals_i0(jtk_TestCase_t* testCase, int32_t actualValue, int32_t expectedValue, const uint8_t* sourceCodePath, int32_t lineNumber);

/**
 * @private
 * @memberof TestCase
 */
void jtk_TestCase_assertNotEquals_l0(jtk_TestCase_t* testCase, int64_t actualValue, int64_t expectedValue, const uint8_t* sourceCodePath, int32_t lineNumber);

/**
 * @private
 * @memberof TestCase
 */
void jtk_TestCase_assertNotEquals_f0(jtk_TestCase_t* testCase, float actualValue, float expectedValue, const uint8_t* sourceCodePath, int32_t lineNumber);

/**
 * @private
 * @memberof TestCase
 */
void jtk_TestCase_assertNotEquals_d0(jtk_TestCase_t* testCase, double actualValue, double expectedValue, const uint8_t* sourceCodePath, int32_t lineNumber);

/**
 * @private
 * @memberof TestCase
 */
void jtk_TestCase_assertNotEquals_v0(jtk_TestCase_t* testCase, void* actualValue, void* expectedValue, const uint8_t* sourceCodePath, int32_t lineNumber);

/**
 * @private
 * @memberof TestCase
 */
void jtk_TestCase_assertNotEquals_utf80(jtk_TestCase_t* testCase, const uint8_t* actualValue, const uint8_t* expectedValue, const uint8_t* sourceCodePath, int32_t lineNumber);

/**
 * @private
 * @memberof TestCase
 */
void jtk_TestCase_assertNotEquals0(jtk_TestCase_t* testCase, void* actualValue, void* expectedValue, jtk_ComparatorFunction_t comparator, const uint8_t* sourceCodePath, int32_t lineNumber);

/* Assert Not Equals Extended */

/**
 * @private
 * @memberof TestCase
 */
void jtk_TestCase_assertNotEqualsEx_z0(jtk_TestCase_t* testCase, bool actualValue, bool expectedValue, const uint8_t* sourceCodePath, int32_t lineNumber, const uint8_t* message);

/**
 * @private
 * @memberof TestCase
 */
void jtk_TestCase_assertNotEqualsEx_b0(jtk_TestCase_t* testCase, int8_t actualValue, int8_t expectedValue, const uint8_t* sourceCodePath, int32_t lineNumber, const uint8_t* message);

/**
 * @private
 * @memberof TestCase
 */
void jtk_TestCase_assertNotEqualsEx_s0(jtk_TestCase_t* testCase, int16_t actualValue, int16_t expectedValue, const uint8_t* sourceCodePath, int32_t lineNumber, const uint8_t* message);

/**
 * @private
 * @memberof TestCase
 */
void jtk_TestCase_assertNotEqualsEx_i0(jtk_TestCase_t* testCase, int32_t actualValue, int32_t expectedValue, const uint8_t* sourceCodePath, int32_t lineNumber, const uint8_t* message);

/**
 * @private
 * @memberof TestCase
 */
void jtk_TestCase_assertNotEqualsEx_l0(jtk_TestCase_t* testCase, int64_t actualValue, int64_t expectedValue, const uint8_t* sourceCodePath, int32_t lineNumber, const uint8_t* message);

/**
 * @private
 * @memberof TestCase
 */
void jtk_TestCase_assertNotEqualsEx_f0(jtk_TestCase_t* testCase, float actualValue, float expectedValue, const uint8_t* sourceCodePath, int32_t lineNumber, const uint8_t* message);

/**
 * @private
 * @memberof TestCase
 */
void jtk_TestCase_assertNotEqualsEx_d0(jtk_TestCase_t* testCase, double actualValue, double expectedValue, const uint8_t* sourceCodePath, int32_t lineNumber, const uint8_t* message);

/**
 * @private
 * @memberof TestCase
 */
void jtk_TestCase_assertNotEqualsEx_v0(jtk_TestCase_t* testCase, void* actualValue, void* expectedValue, const uint8_t* sourceCodePath, int32_t lineNumber, const uint8_t* message);

/**
 * @private
 * @memberof TestCase
 */
void jtk_TestCase_assertNotEqualsEx_utf80(jtk_TestCase_t* testCase, const uint8_t* actualValue, const uint8_t* expectedValue, const uint8_t* sourceCodePath, int32_t lineNumber, const uint8_t* message);

/**
 * @private
 * @memberof TestCase
 */
void jtk_TestCase_assertNotEqualsEx0(jtk_TestCase_t* testCase, void* actualValue, void* expectedValue, jtk_ComparatorFunction_t comparator, const uint8_t* sourceCodePath, int32_t lineNumber, const uint8_t* message);

/* Assert Not Null */

/**
 * @private
 * @memberof TestCase
 */
void jtk_TestCase_assertNotNull0(jtk_TestCase_t* testCase, void* object, const uint8_t* sourceCodePath, int32_t lineNumber);

/* Assert Not Null Extended */

/**
 * @private
 * @memberof TestCase
 */
void jtk_TestCase_assertNotNullEx0(jtk_TestCase_t* testCase, void* object, const uint8_t* sourceCodePath, int32_t lineNumber, const uint8_t* message);

/* Assert Null */

/**
 * @private
 * @memberof TestCase
 */
void jtk_TestCase_assertNull0(jtk_TestCase_t* testCase, void* object, const uint8_t* sourceCodePath, int32_t lineNumber);

/* Assert Null Extended */

/**
 * @private
 * @memberof TestCase
 */
void jtk_TestCase_assertNullEx0(jtk_TestCase_t* testCase, void* object, const uint8_t* sourceCodePath, int32_t lineNumber, const uint8_t* message);

/* Assert True/False */

/**
 * @private
 * @memberof TestCase
 */
void jtk_TestCase_assertTrue0(jtk_TestCase_t* testCase, bool value, const uint8_t* sourceCodePath, int32_t lineNumber);

/**
 * @private
 * @memberof TestCase
 */
void jtk_TestCase_assertFalse0(jtk_TestCase_t* testCase, bool value, const uint8_t* sourceCodePath, int32_t lineNumber);

/* Assert True/False Extended */

/**
 * @private
 * @memberof TestCase
 */
void jtk_TestCase_assertTrueEx0(jtk_TestCase_t* testCase, bool value, const uint8_t* sourceCodePath, int32_t lineNumber, const uint8_t* message);

/**
 * @private
 * @memberof TestCase
 */
void jtk_TestCase_assertFalseEx0(jtk_TestCase_t* testCase, bool value, const uint8_t* sourceCodePath, int32_t lineNumber, const uint8_t* message);

/* Defect */

/**
 * @memberof TestCase
 */
jtk_TestDefect_t* jtk_TestCase_getDefect(jtk_TestCase_t* testCase);

/* Flags */


/**
 * @memberof TestCase
 */
bool jtk_TestCase_isReady(jtk_TestCase_t* testCase);

/**
 * @memberof TestCase
 */
bool jtk_TestCase_isDirty(jtk_TestCase_t* testCase);

/**
 * @memberof TestCase
 */
bool jtk_TestCase_isSuccessful(jtk_TestCase_t* testCase);

/**
 * @memberof TestCase
 */
bool jtk_TestCase_isFailure(jtk_TestCase_t* testCase);

/**
 * @memberof TestCase
 */
bool jtk_TestCase_hasError(jtk_TestCase_t* testCase);

/**
 * @memberof TestCase
 */
bool jtk_TestCase_hasUnknownError(jtk_TestCase_t* testCase);

/**
 * @memberof TestCase
 */
void jtk_TestCase_setAllocatedResources(jtk_TestCase_t* testCase, bool allocatedResources);

/**
 * @memberof TestCase
 */
bool jtk_TestCase_hasAllocatedResources(jtk_TestCase_t* testCase);

/**
 * @memberof TestCase
 */
void jtk_TestCase_setDeallocatedResources(jtk_TestCase_t* testCase, bool deallocatedResources);

/**
 * @memberof TestCase
 */
bool jtk_TestCase_hasDeallocatedResources(jtk_TestCase_t* testCase, bool deallocatedResources);

/* Fail */

/**
 * @memberof TestCase
 */
void jtk_TestCase_fail(jtk_TestCase_t* testCase, const uint8_t* sourceCodePath, int32_t lineNumber, const uint8_t* message);

/* Fixture */

/**
 * @memberof TestCase
 */
void jtk_TestCase_setFixture(jtk_TestCase_t* testCase, jtk_TestFixture_t* fixture);

/**
 * @memberof TestCase
 */
jtk_TestFixture_t* jtk_TestCase_getFixture(jtk_TestCase_t* testCase);

/* Name */

/**
 * @memberof TestCase
 */
void jtk_TestCase_setName(jtk_TestCase_t* testCase, const uint8_t* name);

/**
 * @memberof TestCase
 */
const uint8_t* jtk_TestCase_getName(jtk_TestCase_t* testCase);

/* Notify Fixture */

/**
 * @memberof TestCase
 */
void jtk_TestCase_setUpFixture(jtk_TestCase_t* testCase);

/**
 * @memberof TestCase
 */
void jtk_TestCase_tearDownFixture(jtk_TestCase_t* testCase);

/*******************************************************************************
 * TestCase (Macros)                                                           *
 *******************************************************************************/

/* Assert Array Equals */

/**
 * @memberof TestCase
 */
#define jtk_TestCase_assertArrayEquals(testCase, actualValue, expectedValue) jtk_TestCase_assertArrayEquals0(testCase, actualValue, expectedValue, __FILE__, __LINE__)

/**
 * @memberof TestCase
 */
#define jtk_TestCase_assertArrayEquals_z(testCase, actualValue, actualSize, expectedValue, expectedSize) jtk_TestCase_assertArrayEquals_z0(testCase, actualValue, actualSize, expectedValue, expectedSize, __FILE__, __LINE__)

/**
 * @memberof TestCase
 */
#define jtk_TestCase_assertArrayEquals_b(testCase, actualValue, actualSize, expectedValue, expectedSize) jtk_TestCase_assertArrayEquals_b0(testCase, actualValue, actualSize, expectedValue, expectedSize, __FILE__, __LINE__)

/**
 * @memberof TestCase
 */
#define jtk_TestCase_assertArrayEquals_s(testCase, actualValue, actualSize, expectedValue, expectedSize) jtk_TestCase_assertArrayEquals_s0(testCase, actualValue, actualSize, expectedValue, expectedSize, __FILE__, __LINE__)

/**
 * @memberof TestCase
 */
#define jtk_TestCase_assertArrayEquals_i(testCase, actualValue, actualSize, expectedValue, expectedSize) jtk_TestCase_assertArrayEquals_i0(testCase, actualValue, actualSize, expectedValue, expectedSize, __FILE__, __LINE__)

/**
 * @memberof TestCase
 */
#define jtk_TestCase_assertArrayEquals_l(testCase, actualValue, actualSize, expectedValue, expectedSize) jtk_TestCase_assertArrayEquals_l0(testCase, actualValue, actualSize, expectedValue, expectedSize, __FILE__, __LINE__)

/**
 * @memberof TestCase
 */
#define jtk_TestCase_assertArrayEquals_f(testCase, actualValue, actualSize, expectedValue, expectedSize) jtk_TestCase_assertArrayEquals_f0(testCase, actualValue, actualSize, expectedValue, expectedSize, __FILE__, __LINE__)

/**
 * @memberof TestCase
 */
#define jtk_TestCase_assertArrayEquals_d(testCase, actualValue, actualSize, expectedValue, expectedSize) jtk_TestCase_assertArrayEquals_d0(testCase, actualValue, actualSize, expectedValue, expectedSize, __FILE__, __LINE__)

/**
 * @memberof TestCase
 */
#define jtk_TestCase_assertArrayEquals_v(testCase, actualValue, actualSize, expectedValue, expectedSize) jtk_TestCase_assertArrayEquals_v0(testCase, actualValue, actualSize, expectedValue, expectedSize, __FILE__, __LINE__)

/* Assert Array Equals Extended */

/**
 * @memberof TestCase
 */
#define jtk_TestCase_assertArrayEqualsEx(testCase, actualValue, expectedValue, message) jtk_TestCase_assertArrayEqualsEx0(testCase, actualValue, expectedValue, __FILE__, __LINE__, message)

/**
 * @memberof TestCase
 */
#define jtk_TestCase_assertArrayEqualsEx_z(testCase, actualValue, actualSize, expectedValue, expectedSize, message) jtk_TestCase_assertArrayEqualsEx_z0(testCase, actualValue, actualSize, expectedValue, expectedSize, __FILE__, __LINE__, message)

/**
 * @memberof TestCase
 */
#define jtk_TestCase_assertArrayEqualsEx_b(testCase, actualValue, actualSize, expectedValue, expectedSize, message) jtk_TestCase_assertArrayEqualsEx_b0(testCase, actualValue, actualSize, expectedValue, expectedSize, __FILE__, __LINE__, message)

/**
 * @memberof TestCase
 */
#define jtk_TestCase_assertArrayEqualsEx_s(testCase, actualValue, actualSize, expectedValue, expectedSize, message) jtk_TestCase_assertArrayEqualsEx_s0(testCase, actualValue, actualSize, expectedValue, expectedSize, __FILE__, __LINE__, message)

/**
 * @memberof TestCase
 */
#define jtk_TestCase_assertArrayEqualsEx_i(testCase, actualValue, actualSize, expectedValue, expectedSize, message) jtk_TestCase_assertArrayEqualsEx_i0(testCase, actualValue, actualSize, expectedValue, expectedSize, __FILE__, __LINE__, message)

/**
 * @memberof TestCase
 */
#define jtk_TestCase_assertArrayEqualsEx_l(testCase, actualValue, actualSize, expectedValue, expectedSize, message) jtk_TestCase_assertArrayEqualsEx_l0(testCase, actualValue, actualSize, expectedValue, expectedSize, __FILE__, __LINE__, message)

/**
 * @memberof TestCase
 */
#define jtk_TestCase_assertArrayEqualsEx_f(testCase, actualValue, actualSize, expectedValue, expectedSize, message) jtk_TestCase_assertArrayEqualsEx_f0(testCase, actualValue, actualSize, expectedValue, expectedSize, __FILE__, __LINE__, message)

/**
 * @memberof TestCase
 */
#define jtk_TestCase_assertArrayEqualsEx_d(testCase, actualValue, actualSize, expectedValue, expectedSize, message) jtk_TestCase_assertArrayEqualsEx_d0(testCase, actualValue, actualSize, expectedValue, expectedSize, __FILE__, __LINE__, message)

/**
 * @memberof TestCase
 */
#define jtk_TestCase_assertArrayEqualsEx_v(testCase, actualValue, actualSize, expectedValue, expectedSize, message) jtk_TestCase_assertArrayEqualsEx_v0(testCase, actualValue, actualSize, expectedValue, expectedSize, __FILE__, __LINE__, message)

/* Assert Equals */

/**
 * @memberof TestCase
 */
#define jtk_TestCase_assertEquals(testCase, actualValue, expectedValue, comparator) jtk_TestCase_assertEquals0(testCase, actualValue, expectedValue, comparator, __FILE__, __LINE__)

/**
 * @memberof TestCase
 */
#define jtk_TestCase_assertEquals_z(testCase, actualValue, expectedValue) jtk_TestCase_assertEquals_z0(testCase, actualValue, expectedValue, __FILE__, __LINE__)

/**
 * @memberof TestCase
 */
#define jtk_TestCase_assertEquals_b(testCase, actualValue, expectedValue) jtk_TestCase_assertEquals_b0(testCase, actualValue, expectedValue, __FILE__, __LINE__)

/**
 * @memberof TestCase
 */
#define jtk_TestCase_assertEquals_s(testCase, actualValue, expectedValue) jtk_TestCase_assertEquals_s0(testCase, actualValue, expectedValue, __FILE__, __LINE__)

/**
 * @memberof TestCase
 */
#define jtk_TestCase_assertEquals_i(testCase, actualValue, expectedValue) jtk_TestCase_assertEquals_i0(testCase, actualValue, expectedValue, __FILE__, __LINE__)

/**
 * @memberof TestCase
 */
#define jtk_TestCase_assertEquals_l(testCase, actualValue, expectedValue) jtk_TestCase_assertEquals_l0(testCase, actualValue, expectedValue, __FILE__, __LINE__)

/**
 * @memberof TestCase
 */
#define jtk_TestCase_assertEquals_f(testCase, actualValue, expectedValue) jtk_TestCase_assertEquals_f0(testCase, actualValue, expectedValue, __FILE__, __LINE__)

/**
 * @memberof TestCase
 */
#define jtk_TestCase_assertEquals_d(testCase, actualValue, expectedValue) jtk_TestCase_assertEquals_d0(testCase, actualValue, expectedValue, __FILE__, __LINE__)

/**
 * @memberof TestCase
 */
#define jtk_TestCase_assertEquals_v(testCase, actualValue, expectedValue) jtk_TestCase_assertEquals_v0(testCase, actualValue, expectedValue, __FILE__, __LINE__)

/**
 * @memberof TestCase
 */
#define jtk_TestCase_assertEquals_utf8(testCase, actualValue, expectedValue) jtk_TestCase_assertEquals_utf80(testCase, actualValue, expectedValue, __FILE__, __LINE__)

/* Assert Equals Extended */

/**
 * @memberof TestCase
 */
#define jtk_TestCase_assertEqualsEx(testCase, actualValue, expectedValue, comparator, message) jtk_TestCase_assertEqualsEx0(testCase, actualValue, expectedValue, comparator, __FILE__, __LINE__, message)

/**
 * @memberof TestCase
 */
#define jtk_TestCase_assertEqualsEx_z(testCase, actualValue, expectedValue, message) jtk_TestCase_assertEqualsEx_z0(testCase, actualValue, expectedValue, __FILE__, __LINE__, message)

/**
 * @memberof TestCase
 */
#define jtk_TestCase_assertEqualsEx_b(testCase, actualValue, expectedValue, message) jtk_TestCase_assertEqualsEx_b0(testCase, actualValue, expectedValue, __FILE__, __LINE__, message)

/**
 * @memberof TestCase
 */
#define jtk_TestCase_assertEqualsEx_s(testCase, actualValue, expectedValue, message) jtk_TestCase_assertEqualsEx_s0(testCase, actualValue, expectedValue, __FILE__, __LINE__, message)

/**
 * @memberof TestCase
 */
#define jtk_TestCase_assertEqualsEx_i(testCase, actualValue, expectedValue, message) jtk_TestCase_assertEqualsEx_i0(testCase, actualValue, expectedValue, __FILE__, __LINE__, message)

/**
 * @memberof TestCase
 */
#define jtk_TestCase_assertEqualsEx_l(testCase, actualValue, expectedValue, message) jtk_TestCase_assertEqualsEx_l0(testCase, actualValue, expectedValue, __FILE__, __LINE__, message)

/**
 * @memberof TestCase
 */
#define jtk_TestCase_assertEqualsEx_f(testCase, actualValue, expectedValue, message) jtk_TestCase_assertEqualsEx_f0(testCase, actualValue, expectedValue, __FILE__, __LINE__, message)

/**
 * @memberof TestCase
 */
#define jtk_TestCase_assertEqualsEx_d(testCase, actualValue, expectedValue, message) jtk_TestCase_assertEqualsEx_d0(testCase, actualValue, expectedValue, __FILE__, __LINE__, message)

/**
 * @memberof TestCase
 */
#define jtk_TestCase_assertEqualsEx_v(testCase, actualValue, expectedValue, message) jtk_TestCase_assertEqualsEx_v0(testCase, actualValue, expectedValue, __FILE__, __LINE__, message)

/**
 * @memberof TestCase
 */
#define jtk_TestCase_assertEqualsEx_utf8(testCase, actualValue, expectedValue, message) jtk_TestCase_assertEqualsEx_utf80(testCase, actualValue, expectedValue, __FILE__, __LINE__, message)

/* Assert Not Equals */

/**
 * @memberof TestCase
 */
#define jtk_TestCase_assertNotEquals_z(testCase, actualValue, expectedValue) jtk_TestCase_assertNotEquals_z0(testCase, actualValue, expectedValue, __FILE__, __LINE__)

/**
 * @memberof TestCase
 */
#define jtk_TestCase_assertNotEquals_b(testCase, actualValue, expectedValue) jtk_TestCase_assertNotEquals_b0(testCase, actualValue, expectedValue, __FILE__, __LINE__)

/**
 * @memberof TestCase
 */
#define jtk_TestCase_assertNotEquals_s(testCase, actualValue, expectedValue) jtk_TestCase_assertNotEquals_s0(testCase, actualValue, expectedValue, __FILE__, __LINE__)

/**
 * @memberof TestCase
 */
#define jtk_TestCase_assertNotEquals_i(testCase, actualValue, expectedValue) jtk_TestCase_assertNotEquals_i0(testCase, actualValue, expectedValue, __FILE__, __LINE__)

/**
 * @memberof TestCase
 */
#define jtk_TestCase_assertNotEquals_l(testCase, actualValue, expectedValue) jtk_TestCase_assertNotEquals_l0(testCase, actualValue, expectedValue, __FILE__, __LINE__)

/**
 * @memberof TestCase
 */
#define jtk_TestCase_assertNotEquals_f(testCase, actualValue, expectedValue) jtk_TestCase_assertNotEquals_f0(testCase, actualValue, expectedValue, __FILE__, __LINE__)

/**
 * @memberof TestCase
 */
#define jtk_TestCase_assertNotEquals_d(testCase, actualValue, expectedValue) jtk_TestCase_assertNotEquals_d0(testCase, actualValue, expectedValue, __FILE__, __LINE__)

/**
 * @memberof TestCase
 */
#define jtk_TestCase_assertNotEquals_v(testCase, actualValue, expectedValue) jtk_TestCase_assertNotEquals_v0(testCase, actualValue, expectedValue)

/**
 * @memberof TestCase
 */
#define jtk_TestCase_assertNotEquals_utf8(testCase, actualValue, expectedValue) jtk_TestCase_assertNotEquals_utf80(testCase, actualValue, expectedValue, __FILE__, __LINE__)

/**
 * @memberof TestCase
 */
#define jtk_TestCase_assertNotEquals(testCase, actualValue, expectedValue, comparator) jtk_TestCase_assertNotEquals0(testCase, actualValue, expectedValue, comparator, __FILE__, __LINE__)

/* Assert Not Equals Extended */

/**
 * @memberof TestCase
 */
#define jtk_TestCase_assertNotEqualsEx_z(testCase, actualValue, expectedValue, message) jtk_TestCase_assertNotEqualsEx_z0(testCase, actualValue, expectedValue, __FILE__, __LINE__, message)

/**
 * @memberof TestCase
 */
#define jtk_TestCase_assertNotEqualsEx_b(testCase, actualValue, expectedValue, message) jtk_TestCase_assertNotEqualsEx_b0(testCase, actualValue, expectedValue, __FILE__, __LINE__, message)

/**
 * @memberof TestCase
 */
#define jtk_TestCase_assertNotEqualsEx_s(testCase, actualValue, expectedValue, message) jtk_TestCase_assertNotEqualsEx_s0(testCase, actualValue, expectedValue, __FILE__, __LINE__, message)

/**
 * @memberof TestCase
 */
#define jtk_TestCase_assertNotEqualsEx_i(testCase, actualValue, expectedValue, message) jtk_TestCase_assertNotEqualsEx_i0(testCase, actualValue, expectedValue, __FILE__, __LINE__, message)

/**
 * @memberof TestCase
 */
#define jtk_TestCase_assertNotEqualsEx_l(testCase, actualValue, expectedValue, message) jtk_TestCase_assertNotEqualsEx_l0(testCase, actualValue, expectedValue, __FILE__, __LINE__, message)

/**
 * @memberof TestCase
 */
#define jtk_TestCase_assertNotEqualsEx_f(testCase, actualValue, expectedValue, message) jtk_TestCase_assertNotEqualsEx_f0(testCase, actualValue, expectedValue, __FILE__, __LINE__, message)

/**
 * @memberof TestCase
 */
#define jtk_TestCase_assertNotEqualsEx_d(testCase, actualValue, expectedValue, message) jtk_TestCase_assertNotEqualsEx_d0(testCase, actualValue, expectedValue, __FILE__, __LINE__, message)

/**
 * @memberof TestCase
 */
#define jtk_TestCase_assertNotEqualsEx_v(testCase, actualValue, expectedValue, message) jtk_TestCase_assertNotEqualsEx_v0(testCase, actualValue, expectedValue, __FILE__, __LINE__, message)

/**
 * @memberof TestCase
 */
#define jtk_TestCase_assertNotEqualsEx_utf8(testCase, actualValue, expectedValue, message) jtk_TestCase_assertNotEqualsEx_utf80(testCase, actualValue, expectedValue, __FILE__, __LINE__, message)

/**
 * @memberof TestCase
 */
#define jtk_TestCase_assertNotEqualsEx(testCase, actualValue, expectedValue, comparator, message) jtk_TestCase_assertNotEqualsEx0(testCase, actualValue, expectedValue, comparator, __FILE__, __LINE__, message)

/* Assert Not Null */

/**
 * @memberof TestCase
 */
#define jtk_TestCase_assertNotNull(testCase, object) jtk_TestCase_assertNotNull0(testCase, object, __FILE__, __LINE__)

/* Assert Not Null Extended */

/**
 * @memberof TestCase
 */
#define jtk_TestCase_assertNotNullEx(testCase, object, message) jtk_TestCase_assertNotNullEx0(testCase, object, __FILE__, __LINE__, message)

/* Assert Null */

/**
 * @memberof TestCase
 */
#define jtk_TestCase_assertNull(testCase, object) jtk_TestCase_assertNull0(testCase, object, __FILE__, __LINE__)

/* Assert Null Extended */

/**
 * @memberof TestCase
 */
#define jtk_TestCase_assertNullEx(testCase, object, message) jtk_TestCase_assertNullEx0(testCase, object, __FILE__, __LINE__, message)

/* Assert True/False */

/**
 * @memberof TestCase
 */
#define jtk_TestCase_assertTrue(testCase, value) jtk_TestCase_assertTrue0(testCase, value, __FILE__, __LINE__)

/**
 * @memberof TestCase
 */
#define jtk_TestCase_assertFalse(testCase, value) jtk_TestCase_assertFalse0(testCase, value, __FILE__, __LINE__)

/* Assert True/False Extended */

/**
 * @memberof TestCase
 */
#define jtk_TestCase_assertTrueEx(testCase, value, message) jtk_TestCase_assertTrueEx0(testCase, value, __FILE__, __LINE__, message)

/**
 * @memberof TestCase
 */
#define jtk_TestCase_assertFalseEx(testCase, value, message) jtk_TestCase_assertFalseEx0(testCase, value, __FILE__, __LINE__, message)

#endif /* JTK_UNIT_TEST_CASE_H */