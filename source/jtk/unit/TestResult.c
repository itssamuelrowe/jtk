// Thursday, June 28, 2018

#include <jtk/unit/TestResult.h>

/*******************************************************************************
 * TestResult                                                                 *
 *******************************************************************************/

jtk_TestResult_t* jtk_TestResult_new() {
    jtk_TestResult_t* result = jtk_Memory_allocate(jtk_TestResult_t, 1);
    result->m_list = jtk_ArrayList_new();
    
    return result;
}

void jtk_TestResult_delete(jtk_TestResult_t* result) {
    jtk_Assert_assertObject(manager, "The specified test result is null.");
    
    jtk_ArrayList_delete(result->m_list);
    jtk_Memory_deallocate(result);
}