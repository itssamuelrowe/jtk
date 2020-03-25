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

// Saturday, April 06, 2019

#ifndef JTK_CLAP_PARAMETER_H
#define JTK_CLAP_PARAMETER_H

#include <jtk/Configuration.h>
#include <jtk/clap/ParameterType.h>
#include <jtk/collection/list/ArrayList.h>
#include <jtk/core/String.h>

/*******************************************************************************
 * Parameter                                                                   *
 *******************************************************************************/

#define JTK_PARAMETER_FLAG_DEFAULT_RESULT (1 << 0)
#define JTK_PARAMETER_FLAG_INVALID_RESULT (1 << 1)
#define JTK_PARAMETER_FLAG_GENERIC_RESULT (1 << 2)
#define JTK_PARAMETER_FLAG_EMPTY_VALUE (1 << 3)
#define JTK_PARAMETER_FLAG_SINGLE_VALUE (1 << 4)
#define JTK_PARAMETER_FLAG_MULTIPLE_VALUES (1 << 5)

/**
 * @memberof Parameter
 */
typedef struct jtk_Parameter_t jtk_Parameter_t;

/**
 * @memberof Parameter
 */
typedef void (*jtk_Parameter_OnHandleFunction_t)(jtk_Parameter_t* argument, void* result, int32_t flags);

#define JTK_ARGUMENT_CONSUMPTION_MODE_REQUIRED 1
#define JTK_ARGUMENT_CONSUMPTION_MODE_GREEDY 2
#define JTK_ARGUMENT_CONSUMPTION_MODE_CONSIDERABLE 3

/**
 * @class Parameter
 * @ingroup jtk_clap
 * @author Samuel Rowe
 * @since JTK 1.1
 */
struct jtk_Parameter_t {
    uint8_t* m_usage;
    int32_t m_usageSize;
    bool m_required;
    bool m_hidden;
    jtk_Parameter_OnHandleFunction_t m_onHandle;
    int32_t m_index;
    int32_t m_minValues;
    int32_t m_maxValues;
    int32_t m_consumptionMode;
    uint8_t* m_separator;
    int32_t m_separatorSize;
    uint8_t* m_shortFlag;
    int32_t m_shortFlagSize;
    uint8_t* m_longFlag;
    int32_t m_longFlagSize;
    uint8_t* m_name;
    int32_t m_nameSize;
    bool m_acceptEmptyValue;
    jtk_ArrayList_t* m_dependencies;
    jtk_ArrayList_t* m_forbids;
    jtk_ParameterType_t* m_type;
    void* m_defaultResult;
};

#endif /* JTK_CLAP_PARAMETER_H */