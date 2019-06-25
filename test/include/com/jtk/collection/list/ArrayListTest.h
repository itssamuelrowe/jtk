// Sunday, July 1, 2018

#ifndef COM_JTK_COLLECTION_LIST_ARRAY_LIST_TEST_H
#define COM_JTK_COLLECTION_LIST_ARRAY_LIST_TEST_H

#include <jtk/collection/list/ArrayList.h>
#include <jtk/unit/TestCase.h>
#include <jtk/unit/TestSuite.h>

/*******************************************************************************
 * ArrayListTest                                                               *
 *******************************************************************************/

struct jtk_ArrayListBundle_t {
    jtk_ArrayList_t* m_list;
};

typedef struct jtk_ArrayListBundle_t jtk_ArrayListBundle_t;

jtk_TestSuite_t* jtk_ArrayListTest_getSuite();
void jtk_ArrayListTest_testGetSize(jtk_TestCase_t* testCase, jtk_ArrayListBundle_t* bundle);
void jtk_ArrayListTest_testIsEmpty(jtk_TestCase_t* testCase, jtk_ArrayListBundle_t* bundle);
void jtk_ArrayListTest_testAdd(jtk_TestCase_t* testCase, jtk_ArrayListBundle_t* bundle);

#endif /* COM_JTK_COLLECTION_LIST_ARRAY_LIST_TEST_H */