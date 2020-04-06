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

// Tuesday, May 03, 2019

#ifndef JTK_FS_PATH_COMPARISON_FLAG_H
#define JTK_FS_PATH_COMPARISON_FLAG_H

/*******************************************************************************
 * PathComparisonFlag                                                          *
 *******************************************************************************/

/**
 * @class PathComparisonFlag
 * @ingroup jtk_fs
 * @author Samuel Rowe
 * @since jtk 1.1
 */
enum jtk_PathComparisonFlag_t {
    JTK_PATH_COMPARISON_FLAG_SIMPLE,
    JTK_PATH_COMPARISON_FLAG_ABSOLUTE,
    JTK_PATH_COMPARISON_FLAG_CANONICAL
};

/**
 * @memberof PathComparisonFlag
 */
typedef enum jtk_PathComparisonFlag_t jtk_PathComparisonFlag_t;

#endif /* JTK_FS_PATH_COMPARISON_FLAG_H */