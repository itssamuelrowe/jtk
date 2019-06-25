// Monday, May 21, 2018

#ifndef JTK_UNIT_TEST_FIXTURE_H
#define JTK_UNIT_TEST_FIXTURE_H

#include <jtk/Configuration.h>

/*******************************************************************************
 * TestFixture                                                                 *
 *******************************************************************************/

/* Forward References */

typedef struct jtk_TestFixture_t jtk_TestFixture_t;

/**
 * @memberof TestFixture
 */
typedef void (*jtk_TestFixtureSetUpFunction_t)(jtk_TestFixture_t* fixture);

/**
 * @memberof TestFixture
 */
typedef void (*jtk_TestFixtureTearDownFunction_t)(jtk_TestFixture_t* fixture);

/**
 * The TestFixture interface represents an environment to execute one more
 * tests. A fixture is a set of sample objects that can be reused. Each test
 * owns a fixture and is independent of another fixture. Thus, one test cannot
 * affect another test.
 *
 * @class TestFixture
 * @ingroup jtk_unit
 * @author Samuel Rowe <samuelrowe1999@gmail.com>
 * @since  jtk 1.0
 */
struct jtk_TestFixture_t {

    /**
     * The `m_setUp()` function is invoked before a test is executed.
     * It should allocate resources to initialize this fixture to execute a
     * test.
     */
    jtk_TestFixtureSetUpFunction_t m_setUp;

    /**
     * The `m_tearDown()` function is invoked after a test is executed.
     * It should release the resources previously allocated by `setUp()`.
     */
    jtk_TestFixtureTearDownFunction_t m_tearDown;

    /**
     * The resources available to a test.
     */
    void* m_bundle;
};

/**
 * @memberof TestFixture
 */
jtk_TestFixture_t* jtk_TestFixture_new(jtk_TestFixtureSetUpFunction_t m_setUp, jtk_TestFixtureTearDownFunction_t m_tearDown, void* bundle);

/**
 * @memberof TestFixture
 */
void jtk_TestFixture_delete(jtk_TestFixture_t* fixture);

/**
 * @memberof TestFixture
 */
void jtk_TestFixture_setBundle(jtk_TestFixture_t* fixture, void* bundle);

/**
 * @memberof TestFixture
 */
void* jtk_TestFixture_getBundle(jtk_TestFixture_t* fixture);

/**
 * @memberof TestFixture
 */
jtk_TestFixtureSetUpFunction_t jtk_TestFixture_getSetUp(jtk_TestFixture_t* fixture);

/**
 * @memberof TestFixture
 */
void jtk_TestFixture_setSetUp(jtk_TestFixture_t* fixture, jtk_TestFixtureSetUpFunction_t setUp);

/**
 * @memberof TestFixture
 */
jtk_TestFixtureTearDownFunction_t jtk_TestFixture_getTearDown(jtk_TestFixture_t* fixture);

/**
 * @memberof TestFixture
 */
void jtk_TestFixture_setTearDown(jtk_TestFixture_t* fixture, jtk_TestFixtureTearDownFunction_t tearDown);

#endif /* JTK_UNIT_TEST_FIXTURE_H */