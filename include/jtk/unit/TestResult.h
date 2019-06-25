// Monday, May 21, 2018

#ifndef JTK_UNIT_TEST_RESULT_H
#define JTK_UNIT_TEST_RESULT_H

#include <jtk/Configuration.h>
#include <jtk/unit/TestResultEntry.h>

/*******************************************************************************
 * TestResult                                                                  *
 *******************************************************************************/

struct jtk_TestResult_t {
    jtk_ArrayList_t* m_list;
};

typedef struct jtk_TestResult_t jtk_TestResult_t;

jtk_TestResult_t* jtk_TestResult_new();
void jtk_TestResult_delete(jtk_TestResult_t* result);
void jtk_TestResult_addFailure(jtk_TestResult_t* result, jtk_TestResultEntry_t* failure);
void jtk_TestResult_addError(jtk_TestResult_t* result, jtk_TestResultEntry_t* error);
void jtk_TestResult_addUnknownError(jtk_TestResult_t* result, jtk_TestResultEntry_t* unknownError);

#endif /* JTK_UNIT_TEST_RESULT_H */