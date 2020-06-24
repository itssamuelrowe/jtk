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

// Tuesday, June 23 2020

#ifndef JTK_SUPPORT_JSON_H
#define JTK_SUPPORT_JSON_H

#include <jtk/Configuration.h>
#include <jtk/collection/list/ArrayList.h>
#include <jtk/collection/map/HashMap.h>

struct jtk_JsonError_t {

};

typedef struct jtk_JsonError_t jtk_JsonError_t;

enum jtk_JsonValueType_t {
    JTK_JSON_VALUE_NULL,
    JTK_JSON_VALUE_BOOLEAN,
    JTK_JSON_VALUE_NUMBER,
    JTK_JSON_VALUE_STRING,
    JTK_JSON_VALUE_ARRAY,
    JTK_JSON_VALUE_OBJECT
};

typedef enum jtk_JsonValueType_t jtk_JsonValueType_t;

struct jtk_JsonValue_t {
    jtk_JsonValueType_t type;
    union {
        bool boolean;
        double number;
        struct {
            int32_t length;
            uint8_t* bytes;
        } string;
        jtk_ArrayList_t* array;
        jtk_HashMap_t* object;
    };
};

typedef struct jtk_JsonValue_t jtk_JsonValue_t;

jtk_JsonValue_t* jtk_JsonValue_forObject();
jtk_JsonValue_t* jtk_JsonValue_forArray();
jtk_JsonValue_t* jtk_JsonValue_forString(const uint8_t* text, int32_t length);
jtk_JsonValue_t* jtk_JsonValue_forNumber(const uint8_t* text, int32_t length);
jtk_JsonValue_t* jtk_JsonValue_forTrue();
jtk_JsonValue_t* jtk_JsonValue_forFalse();

jtk_JsonValue_t* jtk_parseJson(const uint8_t* sequence, int32_t size, jtk_JsonError_t* error);
uint8_t* jtk_toJson(jtk_JsonValue_t* value, int32_t* size);

#endif /* JTK_SUPPORT_JSON_H */