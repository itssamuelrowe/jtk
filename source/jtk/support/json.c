#include <jtk/support/json.h>

#include <jtk/collection/list/ArrayList.h>
#include <jtk/collection/array/Arrays.h>
#include <jtk/collection/queue/ArrayQueue.h>
#include <jtk/collection/stack/ArrayStack.h>
#include <jtk/io/InputStream.h>
#include <jtk/core/StringBuilder.h>
#include <jtk/core/CString.h>
#include <jtk/collection/map/HashMap.h>
#include <jtk/core/CStringObjectAdapter.h>

#define allocate(type, size) ((type*)malloc(sizeof (type) * (size)))
#define deallocate(object) free(object)

/*******************************************************************************
 * ErrorCode                                                                   *
 *******************************************************************************/

enum jtk_ErrorCode_t {
    JTK_JSON_ERROR_NONE,
    ERROR_UNTERMINATED_STRING,
    ERROR_MALFORMED_UNICODE_CHARACTER_SEQUENCE,
    ERROR_INVALID_ESCAPE_SEQUENCE,
    ERROR_INVALID_KEYWORD,
    ERROR_UNKNOWN_CHARACTER,
    JTK_JSON_ERROR_UNEXPECTED_TOKEN,
    JTK_JSON_ERROR_EXPECTED_OBJECT_OR_ARRAY
};

typedef enum jtk_ErrorCode_t jtk_ErrorCode_t;

/*******************************************************************************
 * TokenType                                                                   *
 *******************************************************************************/

enum TokenType {
    TOKEN_UNKNOWN,
    TOKEN_WHITESPACE,
    TOKEN_NEWLINE,
    TOKEN_EOF,
    TOKEN_LEFT_BRACE,
    TOKEN_RIGHT_BRACE,
    TOKEN_LEFT_BRACKET,
    TOKEN_RIGHT_BRACKET,
    TOKEN_COMMA,
    TOKEN_COLON,
    TOKEN_TRUE,
    TOKEN_FALSE,
    TOKEN_NULL,
    TOKEN_STRING,
    TOKEN_NUMBER,
};

typedef enum TokenType TokenType;

static char tokenNames[][25] = {
    "<unknown>",
    "<whitespace>",
    "<newline>",
    "<eof>",
    "{",
    "}",
    "[",
    "]",
    ","
    ":",
    "true",
    "false",
    "null",
    "<string>",
    "<number>"
};

/*******************************************************************************
 * TokenChannel                                                                *
 *******************************************************************************/

enum TokenChannel {
    TOKEN_CHANNEL_DEFAULT,
    TOKEN_CHANNEL_HIDDEN,
};

typedef enum TokenChannel TokenChannel;

/*******************************************************************************
 * Token                                                                       *
 *******************************************************************************/

/**
 * A token represents the smallest entity that appears
 * in a source code. Each token has two primary attributes:
 * a token type (symbol category) and the text associated
 * with it.
 */
struct Token {
    TokenChannel channel;
    TokenType type;
    uint8_t* text;
    int32_t length;
    int32_t startIndex;
    int32_t stopIndex;
    int32_t startLine;
    int32_t stopLine;
    int32_t startColumn;
    int32_t stopColumn;
    int32_t index;
    const char* file;
};

typedef struct Token Token;

Token* newToken(TokenChannel channel, TokenType type,
    const uint8_t* text, int32_t length, int32_t startIndex, int32_t stopIndex,
    int32_t startLine, int32_t stopLine, int32_t startColumn, int32_t stopColumn,
    const char* file);

void deleteToken(Token* token);

/*******************************************************************************
 * Parser                                                                      *
 *******************************************************************************/

struct Parser {

    /**
     * The input stream of characters.
     */
    uint8_t* input;

    /**
     * The size of the input stream.
     */
    int32_t inputSize;

    /**
     * The character at LA(1), this field is always updated
     * by k_Lexer_consume(...).
     */
    int32_t la1;

    /**
     * The input cursor under which the current look ahead
     * character is located.
     */
    int32_t index;

    /**
     * The zero based line number at which the lexer is currently
     * reading.
     */
    int32_t line;

    /**
     * The zero based column index within the line, where the
     * lexer is currently reading.
     */
    int32_t column;

    /**
     * The starting index of the current token in the input
     * stream, inclusive.
     */
    int32_t startIndex;

    /**
     * The zero based line number at which the current
     * token begins, inclusive.
     */
    int32_t startLine;

    /**
     * The zero based column at which the current token
     * begins. It is always relative to the starting line.
     */
    int32_t startColumn;

    /**
     * Determines whether the lexer has reached the end of
     * the input stream.
     */
    int32_t hitEndOfStream:1;

    /**
     * The token that was most recently emitted.
     */
    Token* token;

    /**
     * The channel on which the next recognized
     * token will be created on.
     */
    TokenChannel  channel;

    /**
     * The text consumed so far to recognize the next
     * token.
     */
    jtk_StringBuilder_t* text;

    /**
     * The token type of the next recognized token.
     */
    TokenType type;

    const char* file;

    Token* lt1;
};

typedef struct Parser Parser;

/**
 * The primary interface to the lexer. It uses the lookahead
 * character (character under the input cursor) to route control
 * flow to the appropriate recognition function. And returns the
 * next token recognized from the input stream.
 */
static Token* nextToken(Parser* parser);

Parser* parserNew();
void parserDelete(Parser* parser);
jtk_JsonValue_t* parse(Parser* parser);
jtk_JsonValue_t* parseObject(Parser* parser);
jtk_JsonValue_t* parseArray(Parser* parser);
jtk_JsonValue_t* parseValue(Parser* parser);

static void read(Parser* parser);
static Token* createToken(Parser* parser);
static void onNewLine(Parser* parser);
static void decimalIntegerLiteral(Parser* parser);

static void indent(jtk_StringBuilder_t* builder, int32_t depth);
static void toString(jtk_StringBuilder_t* builder, jtk_JsonValue_t* value);
static void toPrettyString(jtk_StringBuilder_t* builder, jtk_JsonValue_t* value, int32_t depth, bool member);


Parser* newParser(const uint8_t* input, int32_t inputSize) {
    /* The constructor invokes consume() to initialize
     * the LA(1) character. Therefore, we assign negative values
     * to certain attributes.
     */

    Parser* parser = allocate(Parser, 1);

    parser->input = input;
    parser->inputSize = inputSize;
    parser->la1 = 0;
    parser->index = -1;
    parser->line = 1;
    parser->column = -1;
    parser->startIndex = 0;
    parser->startLine = 0;
    parser->startColumn = 0;
    parser->hitEndOfStream = false;
    parser->token = NULL;
    parser->channel = TOKEN_CHANNEL_DEFAULT;
    parser->text = jtk_StringBuilder_new();
    parser->type = TOKEN_UNKNOWN;

    read(parser);

    parser->lt1 = nextToken(parser);

    return parser;
}

/*******************************************************************************
 * Token                                                                       *
 *******************************************************************************/

Token* newToken(
    TokenChannel channel,
    TokenType type,
    const uint8_t* text,
    int32_t length,
    int32_t startIndex,
    int32_t stopIndex,
    int32_t startLine,
    int32_t stopLine,
    int32_t startColumn,
    int32_t stopColumn,
    const char* file) {
    Token* token = allocate(Token, 1);
    token->channel = channel;
    token->type = type;
    token->text = jtk_CString_newEx(text, length);
    token->length = length; // This is the length of the text representation!
    token->startIndex = startIndex;
    token->stopIndex = stopIndex;
    token->startLine = startLine;
    token->stopLine = stopLine;
    token->startColumn = startColumn;
    token->stopColumn = stopColumn;
    token->file = file;

    return token;
}

void deleteToken(Token* token) {
    jtk_Assert_assertObject(token, "The specified token is null.");

    jtk_CString_delete(token->text);
    deallocate(token);
}

/*******************************************************************************
 * Lexer                                                                       *
 *******************************************************************************/

#define isEscapeSequence(c) \
    (c == 'b') || \
    (c == 'f') || \
    (c == 'n') || \
    (c == 'r') || \
    (c == 't') || \
    (c == '\\') || \
    (c == '\"') || \
    (c == '\'')

#define isLetter(c) ((c >= 'a') && (c <= 'z')) || ((c >= 'A') && (c <= 'Z'))


#define isHexadecimalDigit(c) \
    ((c >= '0') && (c <= '9')) || ((c >= 'a') && (c <= 'f')) || ((c >= 'A') && (c <= 'F'))

/* Destructor */

void lexerDelete(Parser* parser) {
    jtk_Assert_assertObject(parser, "The specified lexer is null.");

    jtk_StringBuilder_delete(parser->text);
    deallocate(parser);
}

/* Create Token */

Token* createToken(Parser* parser) {
    int32_t length = jtk_StringBuilder_getSize(parser->text);
    length = (parser->type == TOKEN_STRING)? length - 2 : length;

    uint8_t* text = parser->text->m_value;
    text = jtk_CString_newEx((parser->type == TOKEN_STRING)? text + 1 : text,
        length);


    Token* token =
        newToken(
            parser->channel,
            parser->type,
            text,
            length,
            parser->startIndex,    /* inclusive */
            parser->index,         /* exclusive */
            parser->startLine,     /* inclusive */
            parser->line,          /* inclusive */
            parser->startColumn,   /* inclusive */
            parser->column,        /* inclusive */
            parser->file
        );

    /* Destroy the text; not required anymore. */
    jtk_CString_delete(text);

    return token;
}

void onNewLine(Parser* parser) {
    parser->line++;
    parser->column = 1;
}

bool isInputStart(Parser* parser) {
    return (parser->startLine == 0) && (parser->startColumn == 0);
}

void read(Parser* parser) {
    jtk_StringBuilder_appendCodePoint(parser->text, parser->la1);

    parser->index++;
    parser->column++;
    /* NOTE: We could have used parser->index >= "length of input stream"
     * Unfortunately, the flexible design of both the lexer and input stream fails
     * to provide a method to determine the stream length in advance.
     *
     * NOTE: The getAvailable() function is only temporarily used. However, the
     * working of this function is not finalized. Therefore, the following expression
     * may be subjected to changes.
     */
    if (parser->index >= parser->inputSize) {
        parser->la1 = TOKEN_EOF;
    }
    else {
        parser->la1 = parser->input[parser->index];
    }
}

/*
 * Check for a buffered token. If found, remove it from the buffer
 * and return it to the user.
 */
Token* nextToken(Parser* parser) {
    jtk_Assert_assertObject(parser, "The specified lexer is null.");

    jtk_ErrorCode_t errorCode = JTK_JSON_ERROR_NONE;

    /* We don't exit the loop until
        * -- We have a token.
        * -- We have reached the end of the stream.
        * -- We have encountered an error. (Interestingly, this condition
        *    is not explicitly checked because errorneous token recognition
        *    too generate tokens!)
        */
    loopEntry: {
        parser->token = NULL;
        parser->type = TOKEN_UNKNOWN;
        jtk_StringBuilder_clear(parser->text);
        parser->channel = TOKEN_CHANNEL_DEFAULT;
        parser->startIndex = parser->index;
        parser->startLine = parser->line;
        parser->startColumn = parser->column;

        if (parser->index == parser->inputSize) {
            parser->type = TOKEN_EOF;
            parser->hitEndOfStream = true;
        }
        else {

            switch (parser->la1) {


                case ' '  : {
                    if (parser->la1 == ' ') {
                        do {
                            read(parser);
                        }
                        while (parser->la1 == ' ');
                    }
                    goto loopEntry;
                }

                case '\r' :
                case '\n' : {
                    if (parser->la1 == '\r') {
                        read(parser);
                        if (parser->la1 == '\n') {
                            read(parser);
                            onNewLine(parser);
                        }
                    }
                    else {
                        read(parser);
                        onNewLine(parser);
                    }

                    goto loopEntry;
                }

                /* COMMA
                * :    ','
                * ;
                */
                case ',': {
                    read(parser);
                    parser->type = TOKEN_COMMA;
                    break;
                }

                /*
                * COLON
                * :    ':'
                * ;
                */
                case ':': {
                    read(parser);
                    parser->type = TOKEN_COLON;

                    break;
                }

                /* LEFT_BRACE
                 * :    '{'
                 * ;
                 */
                case '{': {
                    read(parser);
                    parser->type = TOKEN_LEFT_BRACE;
                    break;
                }

                /* RIGHT_BRACE
                * :    '}'
                * ;
                */
                case '}' : {
                    /* Consume and discard the '}' character. */
                    read(parser);
                    /* The lexer has recognized the '}' token. */
                    parser->type = TOKEN_RIGHT_BRACE;
                    break;
                }

                /* LEFT_SQUARE_BRACKET
                * :    '['
                * ;
                */
                case '[' : {
                    /* Consume and discard the '[' character. */
                    read(parser);
                    /* The lexer has recognized the '[' token. */
                    parser->type = TOKEN_LEFT_BRACKET;
                    break;
                }

                /* RIGHT_SQUARE_BRACKET
                * :    ']'
                * ;
                */
                case ']' : {
                    /* Consume and discard the ']' character. */
                    read(parser);
                    /* The lexer has recognized the ']' token. */
                    parser->type = TOKEN_RIGHT_BRACKET;
                    break;
                }

                /* STRING
                * :    '"' STRING_CHARACTER* '"'
                * ;
                *
                * STRING_CHARACTER
                * :    ~["'\\]
                * |    ESCAPE_SEQUENCE
                * ;
                *
                * ESCAPE_SEQUENCE
                * :    '\\' [btnfr"'\\]
                * |    '\\' 'u' HEXADECIMAL_DIGIT HEXADECIMAL_DIGIT HEXADECIMAL_DIGIT HEXADECIMAL_DIGIT
                * ;
                *
                * HEXADECIMAL_DIGIT
                * :    [0-9a-fA-F]
                * ;
                */
                case '"': {
                    read(parser);

                    while (parser->la1 != '"') {
                        if ((parser->index == parser->inputSize) || (parser->la1 == '\n')) {
                            errorCode = ERROR_UNTERMINATED_STRING;
                            break;
                        }
                        else if (parser->la1 == '\\') {
                            read(parser);

                            if (isEscapeSequence(parser->la1)) {
                                read(parser);
                            }
                            else if (parser->la1 == 'u') {
                                read(parser);

                                int32_t i;
                                for (i = 0; i < 4; i++) {
                                    if (isHexadecimalDigit(parser->la1)) {
                                        read(parser);
                                    }
                                    else {
                                        errorCode = ERROR_MALFORMED_UNICODE_CHARACTER_SEQUENCE;
                                        break;
                                    }
                                }
                            }
                            else {
                                errorCode = ERROR_INVALID_ESCAPE_SEQUENCE;
                                read(parser);
                            }
                        }
                        else {
                            read(parser);
                        }
                    }

                    if (parser->la1 == '"') {
                        read(parser);
                    }
                    // else {
                    //      Most likely, we encountered an immature end of line or stream.
                    // }

                    parser->type = TOKEN_STRING;
                    break;
                }

                default: {
                    /* KEYWORD
                    * :    LETTER LETTER*
                    * ;
                    */
                    if (isLetter(parser->la1)) {
                        read(parser);

                        while (isLetter(parser->la1)) {
                            read(parser);
                        }

                        uint8_t* text = parser->text->m_value; // jtk_StringBuilder_toCString(parser->text);
                        int32_t length = parser->text->m_size; // parser->index - parser->startIndex;

                        if (jtk_CString_equals(text, length, tokenNames[(int32_t)TOKEN_FALSE], 5)) {
                            parser->type = TOKEN_FALSE;
                        }
                        else if (jtk_CString_equals(text, length, tokenNames[(int32_t)TOKEN_TRUE], 4)) {
                            parser->type = TOKEN_TRUE;
                        }
                        else if (jtk_CString_equals(text, length, tokenNames[(int32_t)TOKEN_NULL], 4)) {
                            parser->type = TOKEN_NULL;
                        }
                        else {
                            errorCode = ERROR_INVALID_KEYWORD;
                        }
                    }
                    // else if (isDecimalDigit(parser->la1)) {
                    //     TODO
                    // }
                    else {
                        errorCode = ERROR_UNKNOWN_CHARACTER;
                        parser->type = TOKEN_UNKNOWN;
                        read(parser);
                    }
                    break;
                }
            }
        }
    }

    Token* newToken = createToken(parser);
    if (errorCode != JTK_JSON_ERROR_NONE) {
        handleError(parser, newToken, TOKEN_UNKNOWN, errorCode);
    }

    return newToken;
}

Token* consume(Parser* parser) {
    Token* temporary = parser->lt1;
    parser->lt1 = nextToken(parser);
    return temporary;
}

Token* match(Parser* parser, TokenType type) {
    jtk_Assert_assertObject(parser, "The specified parser is null.");

    Token* result = parser->lt1;
    if (parser->lt1->type == type) {
        /* Do not consume the end-of-stream token. */
        if (parser->lt1->type != TOKEN_EOF) {
            consume(parser);
        }
    }
    else {
        handleError(parser, parser->lt1, type, JTK_JSON_ERROR_UNEXPECTED_TOKEN);
    }
    return result;
}

jtk_JsonValue_t* jtk_parseJson(const uint8_t* sequence, int32_t size,
    jtk_JsonError_t* error) {
    jtk_JsonValue_t* result = NULL;
    Parser* parser = newParser(sequence, size);
    if (parser->lt1->type == TOKEN_LEFT_BRACKET) {
        result = parseArray(parser);
    }
    else if (parser->lt1->type == TOKEN_LEFT_BRACE) {
        result = parseObject(parser);
    }
    else {
        handleError(parser, parser->lt1, TOKEN_UNKNOWN, JTK_JSON_ERROR_EXPECTED_OBJECT_OR_ARRAY);
        result = NULL;
    }
    match(parser, TOKEN_EOF);
    return result;
}

jtk_JsonValue_t* parseObject(Parser* parser) {
    match(parser, TOKEN_LEFT_BRACE);

    jtk_JsonValue_t* result = jtk_JsonValue_forObject();

    if (parser->lt1->type == TOKEN_STRING) {
        Token* key = consume(parser);
        match(parser, TOKEN_COLON);
        jtk_JsonValue_t* value = parseValue(parser);
        jtk_HashMap_put(result->object, key->text, value);

        while (parser->lt1->type == TOKEN_COMMA) {
            consume(parser);
            Token* key = match(parser, TOKEN_STRING);
            match(parser, TOKEN_COLON);
            jtk_JsonValue_t* value = parseValue(parser);
            jtk_HashMap_put(result->object, key->text, value);
        }
    }

    match(parser, TOKEN_RIGHT_BRACE);

    return result;
}

#define followValue(token) \
    (token == TOKEN_LEFT_BRACE) || \
    (token == TOKEN_LEFT_BRACKET) || \
    (token == TOKEN_STRING) || \
    (token == TOKEN_NUMBER) || \
    (token == TOKEN_TRUE) || \
    (token == TOKEN_FALSE) || \
    (token == TOKEN_NULL)

jtk_JsonValue_t* parseArray(Parser* parser) {
    match(parser, TOKEN_LEFT_BRACKET);

    jtk_JsonValue_t* value = jtk_JsonValue_forArray();
    if (followValue(parser->lt1->type)) {
        jtk_JsonValue_t* result = parseValue(parser);
        jtk_ArrayList_add(value->array, result);

        while (parser->lt1->type == TOKEN_COMMA) {
            consume(parser);
            result = parseValue(parser);
            jtk_ArrayList_add(value->array, result);
        }
    }

    match(parser, TOKEN_RIGHT_BRACKET);

    return value;
}

jtk_JsonValue_t* parseValue(Parser* parser) {
    TokenType type = parser->lt1->type;
    jtk_JsonValue_t* result = NULL;
    switch (type) {
        case TOKEN_STRING: {
            Token* literal = parser->lt1;
            result = jtk_JsonValue_forString(literal->text, literal->length);
            consume(parser);
            break;
        }

        case TOKEN_NUMBER: {
            Token* literal = consume(parser);
            result = jtk_JsonValue_forNumber(literal->text, literal->length);
            break;
        }

        case TOKEN_TRUE: {
            consume(parser);
            result = jtk_JsonValue_forTrue();
            break;
        }

        case TOKEN_FALSE: {
            consume(parser);
            result = jtk_JsonValue_forFalse();
        }

        case TOKEN_NULL: {
            result = jtk_JsonValue_forTrue();
            consume(parser);
            break;
        }

        case TOKEN_LEFT_BRACKET: {
            result = parseArray(parser);
            break;
        }

        case TOKEN_LEFT_BRACE: {
            result = parseObject(parser);
        }
    }
    return result;
}

jtk_JsonValue_t* newJsonValue(jtk_JsonValueType_t type) {
    jtk_JsonValue_t* value = allocate(jtk_JsonValue_t, 1);
    value->type = type;
    return value;
}

jtk_JsonValue_t* jtk_JsonValue_forObject() {
    jtk_ObjectAdapter_t* adapter = jtk_CStringObjectAdapter_getInstance();
    jtk_JsonValue_t* value = newJsonValue(JTK_JSON_VALUE_OBJECT);
    value->object = jtk_HashMap_new(adapter, NULL);
    return value;
}

jtk_JsonValue_t* jtk_JsonValue_forArray() {
    jtk_JsonValue_t* value = newJsonValue(JTK_JSON_VALUE_ARRAY);
    value->array = jtk_ArrayList_new();
    return value;
}

jtk_JsonValue_t* jtk_JsonValue_forString(const uint8_t* text, int32_t length) {
    jtk_JsonValue_t* value = newJsonValue(JTK_JSON_VALUE_STRING);
    value->string.bytes = jtk_CString_newEx(text, length);
    value->string.length = length;
    return value;
}

jtk_JsonValue_t* jtk_JsonValue_forNumber(const uint8_t* text, int32_t length) {
    jtk_JsonValue_t* value = newJsonValue(JTK_JSON_VALUE_NUMBER);
    value->number = 0; // TODO
    return value;
}

jtk_JsonValue_t* jtk_JsonValue_forFalse() {
    jtk_JsonValue_t* value = newJsonValue(JTK_JSON_VALUE_BOOLEAN);
    value->number = false;
    return value;
}

jtk_JsonValue_t* jtk_JsonValue_forTrue() {
    jtk_JsonValue_t* value = newJsonValue(JTK_JSON_VALUE_BOOLEAN);
    value->number = true;
    return value;
}

void handleError() {
    printf("Errro!\n");
}

void indent(jtk_StringBuilder_t* builder, int32_t depth) {
    jtk_StringBuilder_multiply_z(builder, "    ", 4, depth);
}

void toString(jtk_StringBuilder_t* builder, jtk_JsonValue_t* value) {
    if (value->type == JTK_JSON_VALUE_OBJECT) {
        jtk_StringBuilder_appendCodePoint(builder, '{');
        jtk_Iterator_t* iterator = jtk_HashMap_getEntryIterator(value->object);
        bool first = true;
        while (jtk_Iterator_hasNext(iterator)) {
            jtk_HashMapEntry_t* entry = (jtk_HashMapEntry_t*)jtk_Iterator_getNext(iterator);

            if (!first) {
                jtk_StringBuilder_appendCodePoint(builder, ',');
            }

            jtk_StringBuilder_appendCodePoint(builder, '"');
            jtk_StringBuilder_append_z(builder, (char*)entry->m_key);
            jtk_StringBuilder_appendCodePoint(builder, ':');
            toString(builder, (jtk_JsonValue_t*)entry->m_value);

            first = false;
        }
        jtk_StringBuilder_appendCodePoint(builder, '}');
    }
    else if (value->type == JTK_JSON_VALUE_ARRAY) {
        jtk_StringBuilder_appendCodePoint(builder, '[');
        int32_t limit = jtk_ArrayList_getSize(value->array);
        int32_t i;
        for (i = 0; i < limit; i++) {
            jtk_JsonValue_t* element = (jtk_JsonValue_t*)jtk_ArrayList_getValue(value->array, i);
            toString(builder, element);

            if (i + 1 < limit) {
                jtk_StringBuilder_appendCodePoint(builder, ',');
            }
        }
        jtk_StringBuilder_appendCodePoint(builder, ']');
    }
    else if (value->type == JTK_JSON_VALUE_STRING) {
        jtk_StringBuilder_appendCodePoint(builder, '"');
        jtk_StringBuilder_appendEx_z(builder, value->string.bytes, value->string.length);
        jtk_StringBuilder_appendCodePoint(builder, '"');
    }
}

void toPrettyString(jtk_StringBuilder_t* builder, jtk_JsonValue_t* value,
    int32_t depth, bool member) {
    if (value->type == JTK_JSON_VALUE_OBJECT) {
        jtk_StringBuilder_appendEx_z(builder, "{\n", 2);
        jtk_Iterator_t* iterator = jtk_HashMap_getEntryIterator(value->object);
        bool first = true;
        while (jtk_Iterator_hasNext(iterator)) {
            jtk_HashMapEntry_t* entry = (jtk_HashMapEntry_t*)jtk_Iterator_getNext(iterator);

            if (!first) {
                jtk_StringBuilder_appendEx_z(builder, ",\n", 2);
            }

            indent(builder, depth + 1);
            jtk_StringBuilder_appendCodePoint(builder, '"');
            jtk_StringBuilder_append_z(builder, (char*)entry->m_key);
            jtk_StringBuilder_appendEx_z(builder, "\": ", 3);
            toPrettyString(builder, (jtk_JsonValue_t*)entry->m_value, depth + 1, true);

            first = false;
        }
        jtk_StringBuilder_appendCodePoint(builder, '\n');
        indent(builder, depth);
        jtk_StringBuilder_appendCodePoint(builder, '}');
    }
    else if (value->type == JTK_JSON_VALUE_ARRAY) {
        jtk_StringBuilder_appendEx_z(builder, "[\n", 2);
        int32_t limit = jtk_ArrayList_getSize(value->array);
        int32_t i;
        for (i = 0; i < limit; i++) {
            jtk_JsonValue_t* element = (jtk_JsonValue_t*)jtk_ArrayList_getValue(value->array, i);
            indent(builder, depth + 1);
            toPrettyString(builder, element, depth + 1, true);

            if (i + 1 < limit) {
                jtk_StringBuilder_appendCodePoint(builder, ',');
            }
            jtk_StringBuilder_appendCodePoint(builder, '\n');
        }
        indent(builder, depth);
        jtk_StringBuilder_appendCodePoint(builder, ']');
    }
    else if (value->type == JTK_JSON_VALUE_STRING) {
        jtk_StringBuilder_appendCodePoint(builder, '"');
        jtk_StringBuilder_appendEx_z(builder, (char*)value->string.bytes, value->string.length);
        jtk_StringBuilder_appendCodePoint(builder, '"');
    }

    if (!member) {
        jtk_StringBuilder_appendCodePoint(builder, '\n');
    }
}

uint8_t* jtk_toJson(jtk_JsonValue_t* value, int32_t* size, bool pretty) {
    jtk_StringBuilder_t* builder = jtk_StringBuilder_new();
    if (pretty) {
        toPrettyString(builder, value, 0, false);
    }
    else {
        toString(builder, value);
    }
    uint8_t* result = jtk_StringBuilder_toCString(builder, size);
    jtk_StringBuilder_delete(builder);
    return result;
}
