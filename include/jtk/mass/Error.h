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

// Tuesday, August 28, 2018

#ifndef JTK_MASS_ERROR_H
#define JTK_MASS_ERROR_H

/*******************************************************************************
 * Error                                                                       *
 *******************************************************************************/

/**
 * @class Error
 * @ingroup jtk_mass
 * @author Samuel Rowe <samuelrowe1999@gmail.com>
 * @since JTK 1.1
 */
struct jtk_Error_t {
    jtk_StringBuffer_t* m_message;
    int32_t m_code;
};

/**
 * @memberof Error
 */
typedef struct jtk_Error_t jtk_Error_t;

#endif /* JTK_MASS_ERROR_H */