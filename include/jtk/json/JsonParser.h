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

// Friday, March 22, 2019

#ifndef JTK_JSON_JSON_PARSER_H
#define JTK_JSON_JSON_PARSER_H

/*******************************************************************************
 * JsonParser                                                                  *
 *******************************************************************************/

/**
 * @class JsonParser
 * @ingroup jtk_json
 * @author Samuel Rowe
 * @since JTK 1.1
 */
struct jtk_JsonParser_t {
    jtk_JsonLexer_t* m_lexer;
};

/**
 * @memberof JsonParser
 */
typedef struct jtk_JsonParser_t jtk_JsonParser_t;

jtk_JsonElement_t* jtk_JsonParser_parse(jtk_JsonParser_t* parser, jtk_String_t* string);

#endif /* JTK_JSON_JSON_PARSER_H */