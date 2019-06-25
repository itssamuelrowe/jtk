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