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

// Monday, Monday 27, 2019

#ifndef JTK_HOKUM_TAPE_H
#define JTK_HOKUM_TAPE_H

/*******************************************************************************
 * Tape                                                                        *
 *******************************************************************************/

#define JTK_TAPE_FLAG_EXTERNAL_BUFFER (1 << 0)

/**
 * @class Tape
 * @ingroup jtk_hokum
 * @author Samuel Rowe
 * @since JTK 1.1
 */
struct jtk_Tape_t {
    uint8_t* m_value;
    int32_t m_size;
    int32_t m_index;
    uint8_t m_flags;
};

/**
 * @memberof Tape
 */
typedef struct jtk_Tape_t jtk_Tape_t;

// Constructor

jtk_Tape_t* jtk_Tape_wrap(uint8_t* value, int32_t size);

// Destructor

void jtk_Tape_delete(jtk_Tape_t* tape);

// Available

bool jtk_Tape_isAvailable(jtk_Tape_t* tape, int32_t required);

// Read

int8_t jtk_Tape_readByte(jtk_Tape_t* tape);

void jtk_Tape_readUncheckedBytes(jtk_Tape_t* tape, uint8_t* buffer, int32_t size);

int16_t jtk_Tape_readShort(jtk_Tape_t* tape);

int32_t jtk_Tape_readInteger(jtk_Tape_t* tape);

int64_t jtk_Tape_readLong(jtk_Tape_t* tape);

float jtk_Tape_readFloat(jtk_Tape_t* tape);

double jtk_Tape_readDouble(jtk_Tape_t* tape);

#endif /* JTK_HOKUM_TAPE_H */