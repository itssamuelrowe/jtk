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

// Monday, May 13, 2019

#ifndef JTK_CORE_ERROR_FLAG_H
#define JTK_CORE_ERROR_FLAG_H

/*******************************************************************************
 * ErrorFlag                                                                   *
 *******************************************************************************/

/*
 * [8][7][6][5][4][3][2][1][0] - 4 (MSB)
 *  ^  ^  ^  ^  ^  ^  ^  ^  ^--------------------------------
 *  |  |  |  |  |  |  |  ^--------------------------------
 *  |  |  |  |  |  |  ^--------------------------------
 *  |  |  |  |  |  ^--------------------------------
 *  |  |  |  |  ^--------------------------------
 *  |  |  |  ^--------------------------------
 *  |  |  ^--------------------------------
 *  |  ^--------------------------------
 *  ^--------------------------------
 *
 * [8][7][6][5][4][3][2][1][0] - 3
 *  ^  ^  ^  ^  ^  ^  ^  ^  ^--------------------------------
 *  |  |  |  |  |  |  |  ^--------------------------------
 *  |  |  |  |  |  |  ^--------------------------------
 *  |  |  |  |  |  ^--------------------------------
 *  |  |  |  |  ^--------------------------------
 *  |  |  |  ^--------------------------------
 *  |  |  ^--------------------------------
 *  |  ^--------------------------------
 *  ^--------------------------------
 *
 * [8][7][6][5][4][3][2][1][0] - 2
 *  ^  ^  ^  ^  ^  ^  ^  ^  ^--------------------------------
 *  |  |  |  |  |  |  |  ^--------------------------------
 *  |  |  |  |  |  |  ^--------------------------------
 *  |  |  |  |  |  ^--------------------------------
 *  |  |  |  |  ^--------------------------------
 *  |  |  |  ^--------------------------------
 *  |  |  ^--------------------------------
 *  |  ^--------------------------------
 *  ^--------------------------------
 *
 * [8][7][6][5][4][3][2][1][0] - 1 (LSB)
 *  ^  ^  ^  ^  ^  ^  ^  ^  ^-------------------------------- --
 *  |  |  |  |  |  |  |  ^--------------------------------     |----- Source
 *  |  |  |  |  |  |  ^--------------------------------       --
 *  |  |  |  |  |  ^--------------------------------          --
 *  |  |  |  |  ^--------------------------------              |----- Level
 *  |  |  |  ^--------------------------------                --
 *  |  |  ^--------------------------------                   --
 *  |  ^--------------------------------                       |----- Reserved
 *  ^--------------------------------                         --
 */

#define JTK_ERROR_FLAG_SOURCE_NATIVE (1 << 0)
#define JTK_ERROR_FLAG_SOURCE_LIBRARY (1 << 1)
#define JTK_ERROR_FLAG_SOURCE_APPLICATION (1 << 2)

/**
 * NOTE: Use the bitwise AND operator to "set" this flag.
 */
#define JTK_ERROR_FLAG_SOURCE_UNKNOWN (~JTK_ERROR_FLAG_SOURCE_NATIVE & \
                                       ~JTK_ERROR_FLAG_SOURCE_LIBRARY & \
                                       ~JTK_ERROR_FLAG_SOURCE_APPLICATION)

#define JTK_ERROR_FLAG_LEVEL_HIGH (1 << 3)
#define JTK_ERROR_FLAG_LEVEL_MEDIUM (1 << 4)
#define JTK_ERROR_FLAG_LEVEL_LOW (1 << 5)

/**
 * NOTE: Use the bitwise AND operator to "set" this flag.
 */
#define JTK_ERROR_FLAG_LEVEL_UNKNOWN (~JTK_ERROR_FLAG_LEVEL_HIGH & \
                                      ~JTK_ERROR_FLAG_LEVEL_MEDIUM & \
                                      ~JTK_ERROR_FLAG_LEVEL_LOW)

#define JTK_ERROR_FLAG_DEFAULT 0

#endif /* JTK_CORE_ERROR_FLAG_H */