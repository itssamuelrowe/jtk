// Monday, May 21, 2018

#ifndef JTK_UNIT_TEST_SUITE_H
#define JTK_UNIT_TEST_SUITE_H

#include <jtk/Configuration.h>
#include <jtk/collection/list/ArrayList.h>
#include <jtk/unit/TestCase.h>
#include <jtk/unit/TestFixture.h>
#include <jtk/unit/TestListener.h>

/*******************************************************************************
 * TestSuite                                                                   *
 *******************************************************************************/

/**
 * @private
 * @memberof TestSuite
 */
#define JTK_TEST_SUITE_FLAG_READY (1 << 0)

/**
 * @private
 * @memberof TestSuite
 */
#define JTK_TEST_SUITE_FLAG_DIRTY (1 << 1)

/**
 * @private
 * @memberof TestSuite
 */
#define JTK_TEST_SUITE_FLAG_SUCCESSFUL (1 << 2)
 
/**
 * @class TestSuite
 * @ingroup jtk_unit
 * @author Samuel Rowe <samuelrowe1999@gmail.com>
 * @since JTK 1.0
 */
struct jtk_TestSuite_t {
    jtk_ArrayList_t* m_testCases;
    jtk_ArrayList_t* m_testSuites;
    int8_t m_internalFlags;
    uint8_t* m_name;
};

/**
 * @memberof TestSuite
 */
typedef struct jtk_TestSuite_t jtk_TestSuite_t;

/**
 * @memberof TestSuite
 */
jtk_TestSuite_t* jtk_TestSuite_new(const uint8_t* name);

/**
 * @memberof TestSuite
 */
void jtk_TestSuite_delete(jtk_TestSuite_t* suite);

/**
 * @memberof TestSuite
 */
int32_t jtk_TestSuite_getCaseCount(jtk_TestSuite_t* suite);

/**
 * @memberof TestSuite
 */
int32_t jtk_TestSuite_countAllCases(jtk_TestSuite_t* suite);

/**
 * @memberof TestSuite
 */
void jtk_TestSuite_applyFixture(jtk_TestSuite_t* suite, jtk_TestFixture_t* fixture);

/**
 * @memberof TestSuite
 */
void jtk_TestSuite_applyFixturePredicatively(jtk_TestSuite_t* suite, jtk_TestFixture_t* fixture, jtk_PredicateFunction_t predicate);

/**
 * @memberof TestSuite
 */
void jtk_TestSuite_setName(jtk_TestSuite_t* suite, const uint8_t* name);

/**
 * @memberof TestSuite
 */
const uint8_t* jtk_TestSuite_getName(jtk_TestSuite_t* suite);

/**
 * @memberof TestSuite
 */
bool jtk_TestSuite_isSuccessful(jtk_TestSuite_t* suite);

/**
 * @memberof TestSuite
 */
bool jtk_TestSuite_isCompletelySuccessful(jtk_TestSuite_t* suite);

/**
 * @memberof TestSuite
 */
bool jtk_TestSuite_isPartiallySuccessful(jtk_TestSuite_t* suite);

/**
 * @memberof TestSuite
 */
int32_t jtk_TestSuite_getSuiteCount(jtk_TestSuite_t* suite);

/**
 * @memberof TestSuite
 */
int32_t jtk_TestSuite_countAllSuites(jtk_TestSuite_t* suite);

/**
 * @memberof TestSuite
 */
void jtk_TestSuite_addCase(jtk_TestSuite_t* suite, jtk_TestCase_t* testCase);

/**
 * @memberof TestSuite
 */
jtk_ArrayList_t* jtk_TestSuite_getCases(jtk_TestSuite_t* suite);

/**
 * @memberof TestSuite
 */
void jtk_TestSuite_addSuite(jtk_TestSuite_t* suite, jtk_TestSuite_t* other);

/**
 * @memberof TestSuite
 */
jtk_ArrayList_t* jtk_TestSuite_getSuites(jtk_TestSuite_t* suite);

#endif /* JTK_UNIT_TEST_SUITE_H */