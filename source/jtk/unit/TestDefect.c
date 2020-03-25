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

// Saturday, June 20, 2018

#include <jtk/unit/TestDefect.h>

/*******************************************************************************
 * TestDefect                                                                  *
 *******************************************************************************/

jtk_TestDefect_t* jtk_TestDefect_new(const uint8_t* sourceCodePath,
    int32_t lineNumber, const uint8_t* message, jtk_TestDefectType_t type) {
    jtk_TestDefect_t* defect = jtk_Memory_allocate(jtk_TestDefect_t, 1);
    defect->m_sourceCodePath = (sourceCodePath == NULL)? NULL : jtk_String_new(sourceCodePath);
    defect->m_lineNumber = lineNumber;
    defect->m_message = (message == NULL)? NULL : jtk_String_new(message);
    defect->m_type = type;

    return defect;
}

jtk_TestDefect_t* jtk_TestDefect_newFailure(const uint8_t* sourceCodePath,
    int32_t lineNumber, const uint8_t* message) {
    return jtk_TestDefect_new(sourceCodePath, lineNumber, message, JTK_TEST_DEFECT_FAILURE);
}

jtk_TestDefect_t* jtk_TestDefect_newError(const uint8_t* sourceCodePath,
    int32_t lineNumber, const uint8_t* message) {
    return jtk_TestDefect_new(sourceCodePath, lineNumber, message, JTK_TEST_DEFECT_ERROR);
}

jtk_TestDefect_t* jtk_TestDefect_newUnknownError(const uint8_t* sourceCodePath,
    int32_t lineNumber, const uint8_t* message) {
    return jtk_TestDefect_new(sourceCodePath, lineNumber, message, JTK_TEST_DEFECT_UNKNOWN_ERROR);
}

void jtk_TestDefect_delete(jtk_TestDefect_t* defect) {
    jtk_Assert_assertObject(defect, "The specified test defect is null.");

    if (defect->m_sourceCodePath != NULL) {
        jtk_String_delete(defect->m_sourceCodePath);
    }

    if (defect->m_message != NULL) {
        jtk_String_delete(defect->m_message);
    }

    jtk_Memory_deallocate(defect);
}

const uint8_t* jtk_TestDefect_getMessage(jtk_TestDefect_t* defect) {
    jtk_Assert_assertObject(defect, "The specified test defect is null.");

    return defect->m_message;
}

const uint8_t* jtk_TestDefect_getSourceCodePath(jtk_TestDefect_t* defect) {
    jtk_Assert_assertObject(defect, "The specified test defect is null.");

    return defect->m_sourceCodePath;
}
int32_t jtk_TestDefect_getLineNumber(jtk_TestDefect_t* defect) {
    jtk_Assert_assertObject(defect, "The specified test defect is null.");

    return defect->m_lineNumber;
}

jtk_TestDefectType_t jtk_TestDefect_getType(jtk_TestDefect_t* defect) {
    jtk_Assert_assertObject(defect, "The specified test defect is null.");

    return defect->m_type;
}