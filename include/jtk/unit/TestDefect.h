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

// Saturday, June 20, 2018

#ifndef JTK_UNIT_TEST_DEFECT_H
#define JTK_UNIT_TEST_DEFECT_H

#include <jtk/Configuration.h>
#include <jtk/unit/TestDefectType.h>

/*******************************************************************************
 * TestDefect                                                                  *
 *******************************************************************************/

/**
 * @class TestDefect
 * @ingroup jtk_unit
 * @author Samuel Rowe
 * @since JTK 1.0
 */
struct jtk_TestDefect_t {
    int32_t m_lineNumber;
    uint8_t* m_message;
    uint8_t* m_sourceCodePath;
    jtk_TestDefectType_t m_type;
};

/**
 * @memberof TestDefect
 */
typedef struct jtk_TestDefect_t jtk_TestDefect_t;

/**
 * @memberof TestDefect
 */
jtk_TestDefect_t* jtk_TestDefect_new(const uint8_t* sourceCodePath, int32_t lineNumber, const uint8_t* message, jtk_TestDefectType_t type);

/**
 * @memberof TestDefect
 */
jtk_TestDefect_t* jtk_TestDefect_newFailure(const uint8_t* sourceCodePath, int32_t lineNumber, const uint8_t* message);

/**
 * @memberof TestDefect
 */
jtk_TestDefect_t* jtk_TestDefect_newError(const uint8_t* sourceCodePath, int32_t lineNumber, const uint8_t* message);

/**
 * @memberof TestDefect
 */
jtk_TestDefect_t* jtk_TestDefect_newUnknownError(const uint8_t* sourceCodePath, int32_t lineNumber, const uint8_t* message);

/**
 * @memberof TestDefect
 */
void jtk_TestDefect_delete(jtk_TestDefect_t* defect);

/**
 * @memberof TestDefect
 */
const uint8_t* jtk_TestDefect_getMessage(jtk_TestDefect_t* defect);

/**
 * @memberof TestDefect
 */
const uint8_t* jtk_TestDefect_getSourceCodePath(jtk_TestDefect_t* defect);

/**
 * @memberof TestDefect
 */
int32_t jtk_TestDefect_getLineNumber(jtk_TestDefect_t* defect);

/**
 * @memberof TestDefect
 */
jtk_TestDefectType_t jtk_TestDefect_getType(jtk_TestDefect_t* defect);

#endif /* JTK_UNIT_TEST_DEFECT_H */