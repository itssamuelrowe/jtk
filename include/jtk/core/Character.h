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

// Saturday, November 04, 2017

#ifndef JTK_CHARACTER_H
#define JTK_CHARACTER_H

#include <jtk/Configuration.h>

/*******************************************************************************
 * Character                                                                   *
 *******************************************************************************/

/**
 * @memberof Character
 */
#define JTK_CHARACTER_MIN_RADIX 2

/**
 * @memberof Character
 */
#define JTK_CHARACTER_MAX_RADIX 36

/**
 * @memberof Character
 */
#define JTK_CHARACTER_DEFAULT_RADIX 10

/**
 * @memberof Character
 */
#define JTK_CHARACTER_BINARY_RADIX 2

/**
 * @memberof Character
 */
#define JTK_CHARACTER_OCTAL_RADIX 8

/**
 * @memberof Character
 */
#define JTK_CHARACTER_DECIMAL_RADIX 10

/**
 * @memberof Character
 */
#define JTK_CHARACTER_HEXADECIMAL_RADIX 16

bool jtk_Character_isDigit(uint8_t character);
int32_t jtk_Character_getDigitValue(uint8_t character, int32_t radix);
int32_t jtk_Character_toUtf8(int32_t codePoint, uint8_t* buffer, int32_t size, int32_t index);

#endif /* JTK_CHARACTER_H */