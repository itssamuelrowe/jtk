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

// Sunday, April 07, 2019

#ifndef JTK_CLAP_PARAMETER_TYPE_H
#define JTK_CLAP_PARAMETER_TYPE_H

/*******************************************************************************
 * ParameterType                                                                *
 *******************************************************************************/

/**
 * @memberof ParameterType
 */
typedef struct jtk_ParameterType_t jtk_ParameterType_t;

/**
 * @memberof ParameterType
 */
typedef bool (*jtk_ParameterType_ValidateFunction_t)(jtk_ParameterType_t* type, const uint8_t* value);

/**
 * @class ParameterType
 * @ingroup jtk_clap
 * @author Samuel Rowe
 * @since JTK 1.1
 */
struct jtk_ParameterType_t {
    uint8_t* m_name;
    jtk_ParameterType_ValidateFunction_t m_validate;
};

// Constructor

/**
 * @memberof ParameterType
 */
jtk_ParameterType_t* jtk_ParameterType_new(const uint8_t* name, 
    jtk_ParameterType_ValidateFunction_t validate);

// Destructor

/**
 * @memberof ParameterType
 */
void jtk_ParameterType_delete(jtk_ParameterType_t* type);

// Name

/**
 * @memberof ParameterType
 */
const uint8_t* jtk_ParameterType_getName(jtk_ParameterType_t* type);

// Verify Validaty

/**
 * @memberof ParameterType
 */
bool jtk_ParameterType_validate(jtk_ParameterType_t* type, const uint8_t* value);

#endif /* JTK_CLAP_PARAMETER_TYPE_H */