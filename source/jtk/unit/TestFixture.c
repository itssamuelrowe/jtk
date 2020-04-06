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

#include <jtk/unit/TestFixture.h>

/*******************************************************************************
 * TestFixture                                                                 *
 *******************************************************************************/

/* Constructor */

jtk_TestFixture_t* jtk_TestFixture_new(jtk_TestFixtureSetUpFunction_t setUp,
    jtk_TestFixtureTearDownFunction_t tearDown, void* bundle) {
    jtk_TestFixture_t* fixture = jtk_Memory_allocate(jtk_TestFixture_t, 1);
    fixture->m_setUp = setUp;
    fixture->m_tearDown = tearDown;
    fixture->m_bundle = bundle;

    return fixture;
}

/* Destructor */

void jtk_TestFixture_delete(jtk_TestFixture_t* fixture) {
    jtk_Assert_assertObject(fixture, "The specified test fixture is null.");
    jtk_Memory_deallocate(fixture);
}

/* Bundle */

void jtk_TestFixture_setBundle(jtk_TestFixture_t* fixture, void* bundle) {
    jtk_Assert_assertObject(fixture, "The specified test fixture is null.");

    fixture->m_bundle = bundle;
}

void* jtk_TestFixture_getBundle(jtk_TestFixture_t* fixture) {
    jtk_Assert_assertObject(fixture, "The specified test fixture is null.");

    return fixture->m_bundle;
}

/* Set Up */

jtk_TestFixtureSetUpFunction_t jtk_TestFixture_getSetUp(jtk_TestFixture_t* fixture) {
    jtk_Assert_assertObject(fixture, "The specified test fixture is null.");

    return fixture->m_setUp;
}

void jtk_TestFixture_setSetUp(jtk_TestFixture_t* fixture,
    jtk_TestFixtureSetUpFunction_t setUp) {
    jtk_Assert_assertObject(fixture, "The specified test fixture is null.");

    fixture->m_setUp = setUp;
}

/* Tear Down */

jtk_TestFixtureTearDownFunction_t jtk_TestFixture_getTearDown(jtk_TestFixture_t* fixture) {
    jtk_Assert_assertObject(fixture, "The specified test fixture is null.");

    return fixture->m_tearDown;
}

void jtk_TestFixture_setTearDown(jtk_TestFixture_t* fixture,
    jtk_TestFixtureTearDownFunction_t tearDown) {
    jtk_Assert_assertObject(fixture, "The specified test fixture is null.");

    fixture->m_tearDown = tearDown;
}
