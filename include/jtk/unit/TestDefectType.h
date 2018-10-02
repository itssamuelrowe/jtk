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

// Saturday, June 30, 2018

#ifndef JTK_UNIT_TEST_DEFECT_TYPE_H
#define JTK_UNIT_TEST_DEFECT_TYPE_H

/*******************************************************************************
 * TestDefectType                                                              *
 *******************************************************************************/

/**
 * @enum TestDefectType
 * @ingroup jtk_unit
 * @author Samuel Rowe
 * @since JTK 1.0
 */
enum jtk_TestDefectType_t {
    JTK_TEST_DEFECT_FAILURE,
    JTK_TEST_DEFECT_ERROR,
    JTK_TEST_DEFECT_UNKNOWN_ERROR
};

/**
 * @memberof TestDefectType
 */
typedef enum jtk_TestDefectType_t jtk_TestDefectType_t;

#endif /* JTK_UNIT_TEST_DEFECT_TYPE_H */