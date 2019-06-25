// Wednesday, June 27, 2018

#ifndef JTK_UNIT_TEST_RESULT_ENTRY_H
#define JTK_UNIT_TEST_RESULT_ENTRY_H

#include <jtk/Configuration.h>
#include <jtk/core/SourceLocation.h>

/*******************************************************************************
 * TestResultEntry                                                             *
 *******************************************************************************/

struct jtk_TestResultEntry_t {
    jtk_SourceLocation_t* m_sourceLocation;
    uint8_t* m_message;
};

typedef struct jtk_TestResultEntry_t jtk_TestResultEntry_t;

#endif /* JTK_UNIT_TEST_RESULT_ENTRY_H */