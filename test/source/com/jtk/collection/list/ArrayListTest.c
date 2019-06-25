// Sunday, July 1, 2018

#include <com/jtk/collection/list/ArrayListTest.h>

/*******************************************************************************
 * ArrayListBundle                                                             *
 *******************************************************************************/

void jtk_ArrayListBundle_delete(jtk_ArrayListBundle_t* bundle) {
    jtk_ArrayList_delete(bundle->m_list);
    jtk_Memory_deallocate(bundle);
}

jtk_ArrayListBundle_t* jtk_ArrayListBundle_new() {
    jtk_ArrayListBundle_t* bundle = jtk_Memory_allocate(jtk_ArrayListBundle_t, 1);
    bundle->m_list = jtk_ArrayList_new();

    return bundle;
}

/*******************************************************************************
 * ArrayListTest                                                               *
 *******************************************************************************/

void jtk_ArrayListTest_setUp(jtk_TestFixture_t* fixture) {
    jtk_ArrayListBundle_t* bundle = jtk_ArrayListBundle_new();
    jtk_TestFixture_setBundle(fixture, bundle);
}

void jtk_ArrayListTest_tearDown(jtk_TestFixture_t* fixture) {
    jtk_ArrayListBundle_t* bundle = jtk_TestFixture_getBundle(fixture);
    jtk_ArrayListBundle_delete(bundle);
}

jtk_TestFixture_t* jtk_ArrayListTest_getFixture() {
    return jtk_TestFixture_new(jtk_ArrayListTest_setUp, jtk_ArrayListTest_tearDown, NULL);
}

jtk_TestSuite_t* jtk_ArrayListTest_getSuite() {
    jtk_TestCase_t* testGetSize = jtk_TestCase_new("testGetSize", jtk_ArrayListTest_getFixture(), (jtk_TestCaseTargetFunction_t)jtk_ArrayListTest_testGetSize);
    jtk_TestCase_t* testIsEmpty = jtk_TestCase_new("testIsEmpty", jtk_ArrayListTest_getFixture(), (jtk_TestCaseTargetFunction_t)jtk_ArrayListTest_testIsEmpty);
    jtk_TestCase_t* testAdd = jtk_TestCase_new("testAdd", jtk_ArrayListTest_getFixture(), (jtk_TestCaseTargetFunction_t)jtk_ArrayListTest_testAdd);

    jtk_TestSuite_t* suite = jtk_TestSuite_new("ArrayListTest");
    jtk_TestSuite_addCase(suite, testGetSize);
    jtk_TestSuite_addCase(suite, testIsEmpty);
    jtk_TestSuite_addCase(suite, testAdd);

    return suite;
}

void jtk_ArrayListTest_testGetSize(jtk_TestCase_t* testCase, jtk_ArrayListBundle_t* bundle) {
    jtk_TestCase_assertEquals_i(testCase, jtk_ArrayList_getSize(bundle->m_list), 0);

    jtk_ArrayList_add(bundle->m_list, NULL);
    jtk_TestCase_assertEquals_i(testCase, jtk_ArrayList_getSize(bundle->m_list), 1);

    jtk_ArrayList_addLast(bundle->m_list, NULL);
    jtk_TestCase_assertEquals_i(testCase, jtk_ArrayList_getSize(bundle->m_list), 2);

    jtk_ArrayList_addFirst(bundle->m_list, NULL);
    jtk_TestCase_assertEquals_i(testCase, jtk_ArrayList_getSize(bundle->m_list), 3);
}

void jtk_ArrayListTest_testIsEmpty(jtk_TestCase_t* testCase, jtk_ArrayListBundle_t* bundle) {
    jtk_TestCase_assertTrue(testCase, jtk_ArrayList_isEmpty(bundle->m_list));

    jtk_ArrayList_add(bundle->m_list, NULL);
    jtk_ArrayList_add(bundle->m_list, NULL);
    jtk_ArrayList_add(bundle->m_list, NULL);
    jtk_ArrayList_add(bundle->m_list, NULL);
    jtk_ArrayList_add(bundle->m_list, NULL);
    jtk_TestCase_assertFalse(testCase, jtk_ArrayList_isEmpty(bundle->m_list));

    jtk_ArrayList_clear(bundle->m_list);
    jtk_TestCase_assertTrue(testCase, jtk_ArrayList_isEmpty(bundle->m_list));
}

void jtk_ArrayListTest_testAdd(jtk_TestCase_t* testCase, jtk_ArrayListBundle_t* bundle) {
    int32_t x1 = 1;
    int32_t x2 = 20;
    int32_t x3 = 300;
    int32_t x4 = 4000;
    int32_t x5 = 50000;

    jtk_ArrayList_add(bundle->m_list, &x1);
    jtk_ArrayList_add(bundle->m_list, &x2);
    jtk_ArrayList_add(bundle->m_list, &x3);
    jtk_ArrayList_add(bundle->m_list, &x4);
    jtk_ArrayList_add(bundle->m_list, &x5);

    int32_t v1 = *(int32_t*)jtk_ArrayList_getValue(bundle->m_list, 0);
    int32_t v2 = *(int32_t*)jtk_ArrayList_getValue(bundle->m_list, 1);
    int32_t v3 = *(int32_t*)jtk_ArrayList_getValue(bundle->m_list, 2);
    int32_t v4 = *(int32_t*)jtk_ArrayList_getValue(bundle->m_list, 3);
    int32_t v5 = *(int32_t*)jtk_ArrayList_getValue(bundle->m_list, 4);

    jtk_TestCase_assertEquals_i(testCase, x1, v1);
    jtk_TestCase_assertEquals_i(testCase, x2, v2);
    jtk_TestCase_assertEquals_i(testCase, x3, v3);
    jtk_TestCase_assertEquals_i(testCase, x4, v4);
    jtk_TestCase_assertEquals_i(testCase, x5, v5);

    jtk_ArrayList_clear(bundle->m_list);

    intptr_t k = 10000;
    intptr_t i;
    for (i = 0; i < k; i++) {
        jtk_ArrayList_add(bundle->m_list, (void*)i);
    }

    for (i = 0; i < k; i++) {
        jtk_TestCase_assertEquals_i(testCase, i, (intptr_t)jtk_ArrayList_getValue(bundle->m_list, i));
    }
    
    printf("Size: %d, Capacity: %d\n", jtk_ArrayList_getSize(bundle->m_list), jtk_ArrayList_getCapacity(bundle->m_list));
}