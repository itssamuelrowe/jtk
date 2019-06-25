/*
 * Copyright 2018-2019 OneCube
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

// Saturday, June 30, 2018

#ifndef JTK_UNIT_TEST_DEFECT_TYPE_H
#define JTK_UNIT_TEST_DEFECT_TYPE_H

/*******************************************************************************
 * TestDefectType                                                              *
 *******************************************************************************/

/**
 * @enum TestDefectType
 * @ingroup jtk_unit
 * @author Samuel Rowe <samuelrowe1999@gmail.com>
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