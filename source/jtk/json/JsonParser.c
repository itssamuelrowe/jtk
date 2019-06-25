// Friday, March 22, 2019

#include <jtk/json/JsonParser.h>

/*******************************************************************************
 * JsonParser                                                                  *
 *******************************************************************************/

#define STARTING_CAPACITY 16
#define MAX_NESTING       2048

/* do not increase precision without incresing NUM_BUF_SIZE */
#define FLOAT_FORMAT "%1.17g" 

/* double printed with "%1.17g" shouldn't be longer than 25 bytes so let's be paranoid and use 64 */
#define NUM_BUF_SIZE 64

#define SIZEOF_TOKEN(a)       (sizeof(a) - 1)
#define SKIP_CHAR(str)        ((*str)++)
#define SKIP_WHITESPACES(str) while (isspace((unsigned char)(**str))) { SKIP_CHAR(str); }
#define MAX(a, b)             ((a) > (b) ? (a) : (b))

#if defined(isnan) && defined(isinf)
#define IS_NUMBER_INVALID(x) (isnan((x)) || isinf((x)))
#else
#define IS_NUMBER_INVALID(x) (((x) * 0.0) != 0.0)
#endif

static JsonMalloc_Function parson_malloc = malloc;
static JsonFree_Function parson_free = free;

static int32_t parson_escape_slashes = 1;

#define IS_CONT(b) (((unsigned char)(b) & 0xC0) == 0x80) /* is utf-8 continuation byte */

union jtk_JsonValueEntry_t {
    char        *string;
    double       number;
    jtk_JsonObject_t *object;
    jtk_JsonArray_t *array;
    int32_t boolean;
    int32_t null;
};

typedef union jtk_JsonValueEntry_t jtk_JsonValueEntry_t;

typedef struct jtk_JsonValue_t jtk_JsonValue_t;

struct jtk_JsonValue_t {
    jtk_JsonValue_t* m_parent;
    jtk_JsonValueType_t type;
    jtk_JsonValueEntry_t value;
};

struct jtk_JsonObject_t {
    jtk_JsonValue_t *m_wrappingValue;
    uint8_t** names;
    jtk_JsonValue_t** m_values;
    int32_t m_size;
    int32_t m_capacity;
};

struct jtk_JsonArray_t {
    jtk_JsonValue_t* m_wrappingValue;
    jtk_JsonValue_t** m_values;
    int32_t m_size;
    int32_t m_capacity;
};

/* Various */
static char * read_file(const char *filename);
static void   remove_comments(char *string, const char *start_token, const char *end_token);
static char * parson_strndup(const char *string, int32_t n);
static char * parson_strdup(const char *string);
static int32_t    hex_char_to_int(char c);
static int32_t    parse_utf16_hex(const char *string, unsigned int32_t *result);
static int32_t    num_bytes_in_utf8_sequence(unsigned char c);
static int32_t    verify_utf8_sequence(const unsigned char *string, int32_t *len);
static int32_t    is_valid_utf8(const char *string, int32_t string_len);
static int32_t    is_decimal(const char *string, int32_t length);

/* JSON Object */
static JsonObject * json_object_init(JsonValue *wrapping_value);
static JsonStatus   json_object_add(JsonObject *object, const char *name, JsonValue *value);
static JsonStatus   json_object_addn(JsonObject *object, const char *name, int32_t name_len, JsonValue *value);
static JsonStatus   json_object_resize(JsonObject *object, int32_t new_capacity);
static JsonValue  * json_object_getn_value(const JsonObject *object, const char *name, int32_t name_len);
static JsonStatus   json_object_remove_internal(JsonObject *object, const char *name, int32_t free_value);
static JsonStatus   json_object_dotremove_internal(JsonObject *object, const char *name, int32_t free_value);
static void          json_object_free(JsonObject *object);

/* JSON Array */
static JsonArray * json_array_init(JsonValue *wrapping_value);
static JsonStatus  json_array_add(JsonArray *array, JsonValue *value);
static JsonStatus  json_array_resize(JsonArray *array, int32_t new_capacity);
static void         json_array_free(JsonArray *array);

/* JSON Value */
static JsonValue * json_value_init_string_no_copy(char *string);

/* Parser */
static JsonStatus  skip_quotes(const char **string);
static int32_t          parse_utf16(const char **unprocessed, char **processed);
static char *       process_string(const char *input, int32_t len);
static char *       get_quoted_string(const char **string);
static JsonValue * parse_object_value(const char **string, int32_t nesting);
static JsonValue * parse_array_value(const char **string, int32_t nesting);
static JsonValue * parse_string_value(const char **string);
static JsonValue * parse_boolean_value(const char **string);
static JsonValue * parse_number_value(const char **string);
static JsonValue * parse_null_value(const char **string);
static JsonValue * parse_value(const char **string, int32_t nesting);

/* Serialization */
static int32_t    json_serialize_to_buffer_r(const JsonValue *value, char *buf, int32_t level, int32_t is_pretty, char *num_buf);
static int32_t    json_serialize_string(const char *string, char *buf);
static int32_t    append_indent(char *buf, int32_t level);
static int32_t    append_string(char *buf, const char *string);

/* Various */
static char * parson_strndup(const char *string, int32_t n) {
    char *output_string = (char*)parson_malloc(n + 1);
    if (!output_string) {
        return NULL;
    }
    output_string[n] = '\0';
    strncpy(output_string, string, n);
    return output_string;
}

static char * parson_strdup(const char *string) {
    return parson_strndup(string, strlen(string));
}

static int32_t hex_char_to_int(char c) {
    if (c >= '0' && c <= '9') {
        return c - '0';
    } else if (c >= 'a' && c <= 'f') {
        return c - 'a' + 10;
    } else if (c >= 'A' && c <= 'F') {
        return c - 'A' + 10;
    }
    return -1;
}

static int32_t parse_utf16_hex(const char *s, unsigned int32_t *result) {
    int32_t x1, x2, x3, x4;
    if (s[0] == '\0' || s[1] == '\0' || s[2] == '\0' || s[3] == '\0') {
        return 0;
    }
    x1 = hex_char_to_int(s[0]);
    x2 = hex_char_to_int(s[1]);
    x3 = hex_char_to_int(s[2]);
    x4 = hex_char_to_int(s[3]);
    if (x1 == -1 || x2 == -1 || x3 == -1 || x4 == -1) {
        return 0;
    }
    *result = (unsigned int32_t)((x1 << 12) | (x2 << 8) | (x3 << 4) | x4);
    return 1;
}

static int32_t num_bytes_in_utf8_sequence(unsigned char c) {
    if (c == 0xC0 || c == 0xC1 || c > 0xF4 || IS_CONT(c)) {
        return 0;
    } else if ((c & 0x80) == 0) {    /* 0xxxxxxx */
        return 1;
    } else if ((c & 0xE0) == 0xC0) { /* 110xxxxx */
        return 2;
    } else if ((c & 0xF0) == 0xE0) { /* 1110xxxx */
        return 3;
    } else if ((c & 0xF8) == 0xF0) { /* 11110xxx */
        return 4;
    }
    return 0; /* won't happen */
}

static int32_t verify_utf8_sequence(const unsigned char *string, int32_t *len) {
    unsigned int32_t cp = 0;
    *len = num_bytes_in_utf8_sequence(string[0]);

    if (*len == 1) {
        cp = string[0];
    } else if (*len == 2 && IS_CONT(string[1])) {
        cp = string[0] & 0x1F;
        cp = (cp << 6) | (string[1] & 0x3F);
    } else if (*len == 3 && IS_CONT(string[1]) && IS_CONT(string[2])) {
        cp = ((unsigned char)string[0]) & 0xF;
        cp = (cp << 6) | (string[1] & 0x3F);
        cp = (cp << 6) | (string[2] & 0x3F);
    } else if (*len == 4 && IS_CONT(string[1]) && IS_CONT(string[2]) && IS_CONT(string[3])) {
        cp = string[0] & 0x7;
        cp = (cp << 6) | (string[1] & 0x3F);
        cp = (cp << 6) | (string[2] & 0x3F);
        cp = (cp << 6) | (string[3] & 0x3F);
    } else {
        return 0;
    }

    /* overlong encodings */
    if ((cp < 0x80    && *len > 1) ||
        (cp < 0x800   && *len > 2) ||
        (cp < 0x10000 && *len > 3)) {
        return 0;
    }

    /* invalid unicode */
    if (cp > 0x10FFFF) {
        return 0;
    }

    /* surrogate halves */
    if (cp >= 0xD800 && cp <= 0xDFFF) {
        return 0;
    }

    return 1;
}

static int32_t is_valid_utf8(const char *string, int32_t string_len) {
    int32_t len = 0;
    const char *string_end =  string + string_len;
    while (string < string_end) {
        if (!verify_utf8_sequence((const unsigned char*)string, &len)) {
            return 0;
        }
        string += len;
    }
    return 1;
}

static int32_t is_decimal(const char *string, int32_t length) {
    if (length > 1 && string[0] == '0' && string[1] != '.') {
        return 0;
    }
    if (length > 2 && !strncmp(string, "-0", 2) && string[2] != '.') {
        return 0;
    }
    while (length--) {
        if (strchr("xX", string[length])) {
            return 0;
        }
    }
    return 1;
}

static char * read_file(const char * filename) {
    FILE *fp = fopen(filename, "r");
    int32_t size_to_read = 0;
    int32_t size_read = 0;
    long pos;
    char *file_contents;
    if (!fp) {
        return NULL;
    }
    fseek(fp, 0L, SEEK_END);
    pos = ftell(fp);
    if (pos < 0) {
        fclose(fp);
        return NULL;
    }
    size_to_read = pos;
    rewind(fp);
    file_contents = (char*)parson_malloc(sizeof(char) * (size_to_read + 1));
    if (!file_contents) {
        fclose(fp);
        return NULL;
    }
    size_read = fread(file_contents, 1, size_to_read, fp);
    if (size_read == 0 || ferror(fp)) {
        fclose(fp);
        parson_free(file_contents);
        return NULL;
    }
    fclose(fp);
    file_contents[size_read] = '\0';
    return file_contents;
}

static void remove_comments(char *string, const char *start_token, const char *end_token) {
    int32_t in_string = 0, escaped = 0;
    int32_t i;
    char *ptr = NULL, current_char;
    int32_t start_token_len = strlen(start_token);
    int32_t end_token_len = strlen(end_token);
    if (start_token_len == 0 || end_token_len == 0) {
        return;
    }
    while ((current_char = *string) != '\0') {
        if (current_char == '\\' && !escaped) {
            escaped = 1;
            string++;
            continue;
        } else if (current_char == '\"' && !escaped) {
            in_string = !in_string;
        } else if (!in_string && strncmp(string, start_token, start_token_len) == 0) {
            for(i = 0; i < start_token_len; i++) {
                string[i] = ' ';
            }
            string = string + start_token_len;
            ptr = strstr(string, end_token);
            if (!ptr) {
                return;
            }
            for (i = 0; i < (ptr - string) + end_token_len; i++) {
                string[i] = ' ';
            }
            string = ptr + end_token_len - 1;
        }
        escaped = 0;
        string++;
    }
}

/* JSON Object */
static JsonObject * json_object_init(JsonValue *wrapping_value) {
    JsonObject *new_obj = (JsonObject*)parson_malloc(sizeof(JsonObject));
    if (new_obj == NULL) {
        return NULL;
    }
    new_obj->wrapping_value = wrapping_value;
    new_obj->names = (char**)NULL;
    new_obj->values = (JsonValue**)NULL;
    new_obj->capacity = 0;
    new_obj->count = 0;
    return new_obj;
}

static JsonStatus json_object_add(JsonObject *object, const char *name, JsonValue *value) {
    if (name == NULL) {
        return JSONFailure;
    }
    return json_object_addn(object, name, strlen(name), value);
}

static JsonStatus json_object_addn(JsonObject *object, const char *name, int32_t name_len, JsonValue *value) {
    int32_t index = 0;
    if (object == NULL || name == NULL || value == NULL) {
        return JSONFailure;
    }
    if (json_object_getn_value(object, name, name_len) != NULL) {
        return JSONFailure;
    }
    if (object->count >= object->capacity) {
        int32_t new_capacity = MAX(object->capacity * 2, STARTING_CAPACITY);
        if (json_object_resize(object, new_capacity) == JSONFailure) {
            return JSONFailure;
        }
    }
    index = object->count;
    object->names[index] = parson_strndup(name, name_len);
    if (object->names[index] == NULL) {
        return JSONFailure;
    }
    value->parent = json_object_get_wrapping_value(object);
    object->values[index] = value;
    object->count++;
    return JSONSuccess;
}

static JsonStatus json_object_resize(JsonObject *object, int32_t new_capacity) {
    char **temp_names = NULL;
    JsonValue **temp_values = NULL;

    if ((object->names == NULL && object->values != NULL) ||
        (object->names != NULL && object->values == NULL) ||
        new_capacity == 0) {
            return JSONFailure; /* Shouldn't happen */
    }
    temp_names = (char**)parson_malloc(new_capacity * sizeof(char*));
    if (temp_names == NULL) {
        return JSONFailure;
    }
    temp_values = (JsonValue**)parson_malloc(new_capacity * sizeof(JsonValue*));
    if (temp_values == NULL) {
        parson_free(temp_names);
        return JSONFailure;
    }
    if (object->names != NULL && object->values != NULL && object->count > 0) {
        memcpy(temp_names, object->names, object->count * sizeof(char*));
        memcpy(temp_values, object->values, object->count * sizeof(JsonValue*));
    }
    parson_free(object->names);
    parson_free(object->values);
    object->names = temp_names;
    object->values = temp_values;
    object->capacity = new_capacity;
    return JSONSuccess;
}

static JsonValue * json_object_getn_value(const JsonObject *object, const char *name, int32_t name_len) {
    int32_t i, name_length;
    for (i = 0; i < json_object_get_count(object); i++) {
        name_length = strlen(object->names[i]);
        if (name_length != name_len) {
            continue;
        }
        if (strncmp(object->names[i], name, name_len) == 0) {
            return object->values[i];
        }
    }
    return NULL;
}

static JsonStatus json_object_remove_internal(JsonObject *object, const char *name, int32_t free_value) {
    int32_t i = 0, last_item_index = 0;
    if (object == NULL || json_object_get_value(object, name) == NULL) {
        return JSONFailure;
    }
    last_item_index = json_object_get_count(object) - 1;
    for (i = 0; i < json_object_get_count(object); i++) {
        if (strcmp(object->names[i], name) == 0) {
            parson_free(object->names[i]);
            if (free_value) {
                json_value_free(object->values[i]);
            }
            if (i != last_item_index) { /* Replace key value pair with one from the end */
                object->names[i] = object->names[last_item_index];
                object->values[i] = object->values[last_item_index];
            }
            object->count -= 1;
            return JSONSuccess;
        }
    }
    return JSONFailure; /* No execution path should end here */
}

static JsonStatus json_object_dotremove_internal(JsonObject *object, const char *name, int32_t free_value) {
    JsonValue *temp_value = NULL;
    JsonObject *temp_object = NULL;
    const char *dot_pos = strchr(name, '.');
    if (dot_pos == NULL) {
        return json_object_remove_internal(object, name, free_value);
    }
    temp_value = json_object_getn_value(object, name, dot_pos - name);
    if (json_value_get_type(temp_value) != JSONObject) {
        return JSONFailure;
    }
    temp_object = json_value_get_object(temp_value);
    return json_object_dotremove_internal(temp_object, dot_pos + 1, free_value);
}

static void json_object_free(JsonObject *object) {
    int32_t i;
    for (i = 0; i < object->count; i++) {
        parson_free(object->names[i]);
        json_value_free(object->values[i]);
    }
    parson_free(object->names);
    parson_free(object->values);
    parson_free(object);
}

/* JSON Array */
static JsonArray * json_array_init(JsonValue *wrapping_value) {
    JsonArray *new_array = (JsonArray*)parson_malloc(sizeof(JsonArray));
    if (new_array == NULL) {
        return NULL;
    }
    new_array->wrapping_value = wrapping_value;
    new_array->items = (JsonValue**)NULL;
    new_array->capacity = 0;
    new_array->count = 0;
    return new_array;
}

static JsonStatus json_array_add(JsonArray *array, JsonValue *value) {
    if (array->count >= array->capacity) {
        int32_t new_capacity = MAX(array->capacity * 2, STARTING_CAPACITY);
        if (json_array_resize(array, new_capacity) == JSONFailure) {
            return JSONFailure;
        }
    }
    value->parent = json_array_get_wrapping_value(array);
    array->items[array->count] = value;
    array->count++;
    return JSONSuccess;
}

static JsonStatus json_array_resize(JsonArray *array, int32_t new_capacity) {
    JsonValue **new_items = NULL;
    if (new_capacity == 0) {
        return JSONFailure;
    }
    new_items = (JsonValue**)parson_malloc(new_capacity * sizeof(JsonValue*));
    if (new_items == NULL) {
        return JSONFailure;
    }
    if (array->items != NULL && array->count > 0) {
        memcpy(new_items, array->items, array->count * sizeof(JsonValue*));
    }
    parson_free(array->items);
    array->items = new_items;
    array->capacity = new_capacity;
    return JSONSuccess;
}

static void json_array_free(JsonArray *array) {
    int32_t i;
    for (i = 0; i < array->count; i++) {
        json_value_free(array->items[i]);
    }
    parson_free(array->items);
    parson_free(array);
}

/* JSON Value */
static JsonValue * json_value_init_string_no_copy(char *string) {
    JsonValue *new_value = (JsonValue*)parson_malloc(sizeof(JsonValue));
    if (!new_value) {
        return NULL;
    }
    new_value->parent = NULL;
    new_value->type = JSONString;
    new_value->value.string = string;
    return new_value;
}

/* Parser */
static JsonStatus skip_quotes(const char **string) {
    if (**string != '\"') {
        return JSONFailure;
    }
    SKIP_CHAR(string);
    while (**string != '\"') {
        if (**string == '\0') {
            return JSONFailure;
        } else if (**string == '\\') {
            SKIP_CHAR(string);
            if (**string == '\0') {
                return JSONFailure;
            }
        }
        SKIP_CHAR(string);
    }
    SKIP_CHAR(string);
    return JSONSuccess;
}

static int32_t parse_utf16(const char **unprocessed, char **processed) {
    unsigned int32_t cp, lead, trail;
    int32_t parse_succeeded = 0;
    char *processed_ptr = *processed;
    const char *unprocessed_ptr = *unprocessed;
    unprocessed_ptr++; /* skips u */
    parse_succeeded = parse_utf16_hex(unprocessed_ptr, &cp);
    if (!parse_succeeded) {
        return JSONFailure;
    }
    if (cp < 0x80) {
        processed_ptr[0] = (char)cp; /* 0xxxxxxx */
    } else if (cp < 0x800) {
        processed_ptr[0] = ((cp >> 6) & 0x1F) | 0xC0; /* 110xxxxx */
        processed_ptr[1] = ((cp)      & 0x3F) | 0x80; /* 10xxxxxx */
        processed_ptr += 1;
    } else if (cp < 0xD800 || cp > 0xDFFF) {
        processed_ptr[0] = ((cp >> 12) & 0x0F) | 0xE0; /* 1110xxxx */
        processed_ptr[1] = ((cp >> 6)  & 0x3F) | 0x80; /* 10xxxxxx */
        processed_ptr[2] = ((cp)       & 0x3F) | 0x80; /* 10xxxxxx */
        processed_ptr += 2;
    } else if (cp >= 0xD800 && cp <= 0xDBFF) { /* lead surrogate (0xD800..0xDBFF) */
        lead = cp;
        unprocessed_ptr += 4; /* should always be within the buffer, otherwise previous sscanf would fail */
        if (*unprocessed_ptr++ != '\\' || *unprocessed_ptr++ != 'u') {
            return JSONFailure;
        }
        parse_succeeded = parse_utf16_hex(unprocessed_ptr, &trail);
        if (!parse_succeeded || trail < 0xDC00 || trail > 0xDFFF) { /* valid trail surrogate? (0xDC00..0xDFFF) */
            return JSONFailure;
        }
        cp = ((((lead - 0xD800) & 0x3FF) << 10) | ((trail - 0xDC00) & 0x3FF)) + 0x010000;
        processed_ptr[0] = (((cp >> 18) & 0x07) | 0xF0); /* 11110xxx */
        processed_ptr[1] = (((cp >> 12) & 0x3F) | 0x80); /* 10xxxxxx */
        processed_ptr[2] = (((cp >> 6)  & 0x3F) | 0x80); /* 10xxxxxx */
        processed_ptr[3] = (((cp)       & 0x3F) | 0x80); /* 10xxxxxx */
        processed_ptr += 3;
    } else { /* trail surrogate before lead surrogate */
        return JSONFailure;
    }
    unprocessed_ptr += 3;
    *processed = processed_ptr;
    *unprocessed = unprocessed_ptr;
    return JSONSuccess;
}


/* Copies and processes passed string up to supplied length.
Example: "\u006Corem ipsum" -> lorem ipsum */
static char* process_string(const char *input, int32_t len) {
    const char *input_ptr = input;
    int32_t initial_size = (len + 1) * sizeof(char);
    int32_t final_size = 0;
    char *output = NULL, *output_ptr = NULL, *resized_output = NULL;
    output = (char*)parson_malloc(initial_size);
    if (output == NULL) {
        goto error;
    }
    output_ptr = output;
    while ((*input_ptr != '\0') && (int32_t)(input_ptr - input) < len) {
        if (*input_ptr == '\\') {
            input_ptr++;
            switch (*input_ptr) {
                case '\"': *output_ptr = '\"'; break;
                case '\\': *output_ptr = '\\'; break;
                case '/':  *output_ptr = '/';  break;
                case 'b':  *output_ptr = '\b'; break;
                case 'f':  *output_ptr = '\f'; break;
                case 'n':  *output_ptr = '\n'; break;
                case 'r':  *output_ptr = '\r'; break;
                case 't':  *output_ptr = '\t'; break;
                case 'u':
                    if (parse_utf16(&input_ptr, &output_ptr) == JSONFailure) {
                        goto error;
                    }
                    break;
                default:
                    goto error;
            }
        } else if ((unsigned char)*input_ptr < 0x20) {
            goto error; /* 0x00-0x19 are invalid characters for json string (http://www.ietf.org/rfc/rfc4627.txt) */
        } else {
            *output_ptr = *input_ptr;
        }
        output_ptr++;
        input_ptr++;
    }
    *output_ptr = '\0';
    /* resize to new length */
    final_size = (int32_t)(output_ptr-output) + 1;
    /* todo: don't resize if final_size == initial_size */
    resized_output = (char*)parson_malloc(final_size);
    if (resized_output == NULL) {
        goto error;
    }
    memcpy(resized_output, output, final_size);
    parson_free(output);
    return resized_output;
error:
    parson_free(output);
    return NULL;
}

/* Return processed contents of a string between quotes and
   skips passed argument to a matching quote. */
static char * get_quoted_string(const char **string) {
    const char *string_start = *string;
    int32_t string_len = 0;
    JsonStatus status = skip_quotes(string);
    if (status != JSONSuccess) {
        return NULL;
    }
    string_len = *string - string_start - 2; /* length without quotes */
    return process_string(string_start + 1, string_len);
}

static JsonValue * parse_value(const char **string, int32_t nesting) {
    if (nesting > MAX_NESTING) {
        return NULL;
    }
    SKIP_WHITESPACES(string);
    switch (**string) {
        case '{':
            return parse_object_value(string, nesting + 1);
        case '[':
            return parse_array_value(string, nesting + 1);
        case '\"':
            return parse_string_value(string);
        case 'f': case 't':
            return parse_boolean_value(string);
        case '-':
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
            return parse_number_value(string);
        case 'n':
            return parse_null_value(string);
        default:
            return NULL;
    }
}

static JsonValue * parse_object_value(const char **string, int32_t nesting) {
    JsonValue *output_value = NULL, *new_value = NULL;
    JsonObject *output_object = NULL;
    char *new_key = NULL;
    output_value = json_value_init_object();
    if (output_value == NULL) {
        return NULL;
    }
    if (**string != '{') {
        json_value_free(output_value);
        return NULL;
    }
    output_object = json_value_get_object(output_value);
    SKIP_CHAR(string);
    SKIP_WHITESPACES(string);
    if (**string == '}') { /* empty object */
        SKIP_CHAR(string);
        return output_value;
    }
    while (**string != '\0') {
        new_key = get_quoted_string(string);
        if (new_key == NULL) {
            json_value_free(output_value);
            return NULL;
        }
        SKIP_WHITESPACES(string);
        if (**string != ':') {
            parson_free(new_key);
            json_value_free(output_value);
            return NULL;
        }
        SKIP_CHAR(string);
        new_value = parse_value(string, nesting);
        if (new_value == NULL) {
            parson_free(new_key);
            json_value_free(output_value);
            return NULL;
        }
        if (json_object_add(output_object, new_key, new_value) == JSONFailure) {
            parson_free(new_key);
            json_value_free(new_value);
            json_value_free(output_value);
            return NULL;
        }
        parson_free(new_key);
        SKIP_WHITESPACES(string);
        if (**string != ',') {
            break;
        }
        SKIP_CHAR(string);
        SKIP_WHITESPACES(string);
    }
    SKIP_WHITESPACES(string);
    if (**string != '}' || /* Trim object after parsing is over */
        json_object_resize(output_object, json_object_get_count(output_object)) == JSONFailure) {
            json_value_free(output_value);
            return NULL;
    }
    SKIP_CHAR(string);
    return output_value;
}

static JsonValue * parse_array_value(const char **string, int32_t nesting) {
    JsonValue *output_value = NULL, *new_array_value = NULL;
    JsonArray *output_array = NULL;
    output_value = json_value_init_array();
    if (output_value == NULL) {
        return NULL;
    }
    if (**string != '[') {
        json_value_free(output_value);
        return NULL;
    }
    output_array = json_value_get_array(output_value);
    SKIP_CHAR(string);
    SKIP_WHITESPACES(string);
    if (**string == ']') { /* empty array */
        SKIP_CHAR(string);
        return output_value;
    }
    while (**string != '\0') {
        new_array_value = parse_value(string, nesting);
        if (new_array_value == NULL) {
            json_value_free(output_value);
            return NULL;
        }
        if (json_array_add(output_array, new_array_value) == JSONFailure) {
            json_value_free(new_array_value);
            json_value_free(output_value);
            return NULL;
        }
        SKIP_WHITESPACES(string);
        if (**string != ',') {
            break;
        }
        SKIP_CHAR(string);
        SKIP_WHITESPACES(string);
    }
    SKIP_WHITESPACES(string);
    if (**string != ']' || /* Trim array after parsing is over */
        json_array_resize(output_array, json_array_get_count(output_array)) == JSONFailure) {
            json_value_free(output_value);
            return NULL;
    }
    SKIP_CHAR(string);
    return output_value;
}

static JsonValue * parse_string_value(const char **string) {
    JsonValue *value = NULL;
    char *new_string = get_quoted_string(string);
    if (new_string == NULL) {
        return NULL;
    }
    value = json_value_init_string_no_copy(new_string);
    if (value == NULL) {
        parson_free(new_string);
        return NULL;
    }
    return value;
}

static JsonValue * parse_boolean_value(const char **string) {
    int32_t true_token_size = SIZEOF_TOKEN("true");
    int32_t false_token_size = SIZEOF_TOKEN("false");
    if (strncmp("true", *string, true_token_size) == 0) {
        *string += true_token_size;
        return json_value_init_boolean(1);
    } else if (strncmp("false", *string, false_token_size) == 0) {
        *string += false_token_size;
        return json_value_init_boolean(0);
    }
    return NULL;
}

static JsonValue * parse_number_value(const char **string) {
    char *end;
    double number = 0;
    errno = 0;
    number = strtod(*string, &end);
    if (errno || !is_decimal(*string, end - *string)) {
        return NULL;
    }
    *string = end;
    return json_value_init_number(number);
}

static JsonValue * parse_null_value(const char **string) {
    int32_t token_size = SIZEOF_TOKEN("null");
    if (strncmp("null", *string, token_size) == 0) {
        *string += token_size;
        return json_value_init_null();
    }
    return NULL;
}

/* Serialization */
#define APPEND_STRING(str) do { written = append_string(buf, (str));\
                                if (written < 0) { return -1; }\
                                if (buf != NULL) { buf += written; }\
                                written_total += written; } while(0)

#define APPEND_INDENT(level) do { written = append_indent(buf, (level));\
                                  if (written < 0) { return -1; }\
                                  if (buf != NULL) { buf += written; }\
                                  written_total += written; } while(0)

static int32_t json_serialize_to_buffer_r(const JsonValue *value, char *buf, int32_t level, int32_t is_pretty, char *num_buf)
{
    const char *key = NULL, *string = NULL;
    JsonValue *temp_value = NULL;
    JsonArray *array = NULL;
    JsonObject *object = NULL;
    int32_t i = 0, count = 0;
    double num = 0.0;
    int32_t written = -1, written_total = 0;

    switch (json_value_get_type(value)) {
        case JSONArray:
            array = json_value_get_array(value);
            count = json_array_get_count(array);
            APPEND_STRING("[");
            if (count > 0 && is_pretty) {
                APPEND_STRING("\n");
            }
            for (i = 0; i < count; i++) {
                if (is_pretty) {
                    APPEND_INDENT(level+1);
                }
                temp_value = json_array_get_value(array, i);
                written = json_serialize_to_buffer_r(temp_value, buf, level+1, is_pretty, num_buf);
                if (written < 0) {
                    return -1;
                }
                if (buf != NULL) {
                    buf += written;
                }
                written_total += written;
                if (i < (count - 1)) {
                    APPEND_STRING(",");
                }
                if (is_pretty) {
                    APPEND_STRING("\n");
                }
            }
            if (count > 0 && is_pretty) {
                APPEND_INDENT(level);
            }
            APPEND_STRING("]");
            return written_total;
        case JSONObject:
            object = json_value_get_object(value);
            count  = json_object_get_count(object);
            APPEND_STRING("{");
            if (count > 0 && is_pretty) {
                APPEND_STRING("\n");
            }
            for (i = 0; i < count; i++) {
                key = json_object_get_name(object, i);
                if (key == NULL) {
                    return -1;
                }
                if (is_pretty) {
                    APPEND_INDENT(level+1);
                }
                written = json_serialize_string(key, buf);
                if (written < 0) {
                    return -1;
                }
                if (buf != NULL) {
                    buf += written;
                }
                written_total += written;
                APPEND_STRING(":");
                if (is_pretty) {
                    APPEND_STRING(" ");
                }
                temp_value = json_object_get_value(object, key);
                written = json_serialize_to_buffer_r(temp_value, buf, level+1, is_pretty, num_buf);
                if (written < 0) {
                    return -1;
                }
                if (buf != NULL) {
                    buf += written;
                }
                written_total += written;
                if (i < (count - 1)) {
                    APPEND_STRING(",");
                }
                if (is_pretty) {
                    APPEND_STRING("\n");
                }
            }
            if (count > 0 && is_pretty) {
                APPEND_INDENT(level);
            }
            APPEND_STRING("}");
            return written_total;
        case JSONString:
            string = json_value_get_string(value);
            if (string == NULL) {
                return -1;
            }
            written = json_serialize_string(string, buf);
            if (written < 0) {
                return -1;
            }
            if (buf != NULL) {
                buf += written;
            }
            written_total += written;
            return written_total;
        case JSONBoolean:
            if (json_value_get_boolean(value)) {
                APPEND_STRING("true");
            } else {
                APPEND_STRING("false");
            }
            return written_total;
        case JSONNumber:
            num = json_value_get_number(value);
            if (buf != NULL) {
                num_buf = buf;
            }
            written = sprintf(num_buf, FLOAT_FORMAT, num);
            if (written < 0) {
                return -1;
            }
            if (buf != NULL) {
                buf += written;
            }
            written_total += written;
            return written_total;
        case JSONNull:
            APPEND_STRING("null");
            return written_total;
        case JSONError:
            return -1;
        default:
            return -1;
    }
}

static int32_t json_serialize_string(const char *string, char *buf) {
    int32_t i = 0, len = strlen(string);
    char c = '\0';
    int32_t written = -1, written_total = 0;
    APPEND_STRING("\"");
    for (i = 0; i < len; i++) {
        c = string[i];
        switch (c) {
            case '\"': APPEND_STRING("\\\""); break;
            case '\\': APPEND_STRING("\\\\"); break;
            case '\b': APPEND_STRING("\\b"); break;
            case '\f': APPEND_STRING("\\f"); break;
            case '\n': APPEND_STRING("\\n"); break;
            case '\r': APPEND_STRING("\\r"); break;
            case '\t': APPEND_STRING("\\t"); break;
            case '\x00': APPEND_STRING("\\u0000"); break;
            case '\x01': APPEND_STRING("\\u0001"); break;
            case '\x02': APPEND_STRING("\\u0002"); break;
            case '\x03': APPEND_STRING("\\u0003"); break;
            case '\x04': APPEND_STRING("\\u0004"); break;
            case '\x05': APPEND_STRING("\\u0005"); break;
            case '\x06': APPEND_STRING("\\u0006"); break;
            case '\x07': APPEND_STRING("\\u0007"); break;
            /* '\x08' duplicate: '\b' */
            /* '\x09' duplicate: '\t' */
            /* '\x0a' duplicate: '\n' */
            case '\x0b': APPEND_STRING("\\u000b"); break;
            /* '\x0c' duplicate: '\f' */
            /* '\x0d' duplicate: '\r' */
            case '\x0e': APPEND_STRING("\\u000e"); break;
            case '\x0f': APPEND_STRING("\\u000f"); break;
            case '\x10': APPEND_STRING("\\u0010"); break;
            case '\x11': APPEND_STRING("\\u0011"); break;
            case '\x12': APPEND_STRING("\\u0012"); break;
            case '\x13': APPEND_STRING("\\u0013"); break;
            case '\x14': APPEND_STRING("\\u0014"); break;
            case '\x15': APPEND_STRING("\\u0015"); break;
            case '\x16': APPEND_STRING("\\u0016"); break;
            case '\x17': APPEND_STRING("\\u0017"); break;
            case '\x18': APPEND_STRING("\\u0018"); break;
            case '\x19': APPEND_STRING("\\u0019"); break;
            case '\x1a': APPEND_STRING("\\u001a"); break;
            case '\x1b': APPEND_STRING("\\u001b"); break;
            case '\x1c': APPEND_STRING("\\u001c"); break;
            case '\x1d': APPEND_STRING("\\u001d"); break;
            case '\x1e': APPEND_STRING("\\u001e"); break;
            case '\x1f': APPEND_STRING("\\u001f"); break;
            case '/':
                if (parson_escape_slashes) {
                    APPEND_STRING("\\/");  /* to make json embeddable in xml\/html */
                } else {
                    APPEND_STRING("/");
                }
                break;
            default:
                if (buf != NULL) {
                    buf[0] = c;
                    buf += 1;
                }
                written_total += 1;
                break;
        }
    }
    APPEND_STRING("\"");
    return written_total;
}

static int32_t append_indent(char *buf, int32_t level) {
    int32_t i;
    int32_t written = -1, written_total = 0;
    for (i = 0; i < level; i++) {
        APPEND_STRING("    ");
    }
    return written_total;
}

static int32_t append_string(char *buf, const char *string) {
    if (buf == NULL) {
        return (int32_t)strlen(string);
    }
    return sprintf(buf, "%s", string);
}

#undef APPEND_STRING
#undef APPEND_INDENT

/* Parser API */
JsonValue * json_parse_file(const char *filename) {
    char *file_contents = read_file(filename);
    JsonValue *output_value = NULL;
    if (file_contents == NULL) {
        return NULL;
    }
    output_value = json_parse_string(file_contents);
    parson_free(file_contents);
    return output_value;
}

JsonValue * json_parse_file_with_comments(const char *filename) {
    char *file_contents = read_file(filename);
    JsonValue *output_value = NULL;
    if (file_contents == NULL) {
        return NULL;
    }
    output_value = json_parse_string_with_comments(file_contents);
    parson_free(file_contents);
    return output_value;
}

JsonValue * json_parse_string(const char *string) {
    if (string == NULL) {
        return NULL;
    }
    if (string[0] == '\xEF' && string[1] == '\xBB' && string[2] == '\xBF') {
        string = string + 3; /* Support for UTF-8 BOM */
    }
    return parse_value((const char**)&string, 0);
}

JsonValue * json_parse_string_with_comments(const char *string) {
    JsonValue *result = NULL;
    char *string_mutable_copy = NULL, *string_mutable_copy_ptr = NULL;
    string_mutable_copy = parson_strdup(string);
    if (string_mutable_copy == NULL) {
        return NULL;
    }
    remove_comments(string_mutable_copy, "/*", "*/");
    remove_comments(string_mutable_copy, "//", "\n");
    string_mutable_copy_ptr = string_mutable_copy;
    result = parse_value((const char**)&string_mutable_copy_ptr, 0);
    parson_free(string_mutable_copy);
    return result;
}

/* JSON Object API */

JsonValue * json_object_get_value(const JsonObject *object, const char *name) {
    if (object == NULL || name == NULL) {
        return NULL;
    }
    return json_object_getn_value(object, name, strlen(name));
}

const char * json_object_get_string(const JsonObject *object, const char *name) {
    return json_value_get_string(json_object_get_value(object, name));
}

double json_object_get_number(const JsonObject *object, const char *name) {
    return json_value_get_number(json_object_get_value(object, name));
}

JsonObject * json_object_get_object(const JsonObject *object, const char *name) {
    return json_value_get_object(json_object_get_value(object, name));
}

JsonArray * json_object_get_array(const JsonObject *object, const char *name) {
    return json_value_get_array(json_object_get_value(object, name));
}

int32_t json_object_get_boolean(const JsonObject *object, const char *name) {
    return json_value_get_boolean(json_object_get_value(object, name));
}

JsonValue * json_object_dotget_value(const JsonObject *object, const char *name) {
    const char *dot_position = strchr(name, '.');
    if (!dot_position) {
        return json_object_get_value(object, name);
    }
    object = json_value_get_object(json_object_getn_value(object, name, dot_position - name));
    return json_object_dotget_value(object, dot_position + 1);
}

const char * json_object_dotget_string(const JsonObject *object, const char *name) {
    return json_value_get_string(json_object_dotget_value(object, name));
}

double json_object_dotget_number(const JsonObject *object, const char *name) {
    return json_value_get_number(json_object_dotget_value(object, name));
}

JsonObject * json_object_dotget_object(const JsonObject *object, const char *name) {
    return json_value_get_object(json_object_dotget_value(object, name));
}

JsonArray * json_object_dotget_array(const JsonObject *object, const char *name) {
    return json_value_get_array(json_object_dotget_value(object, name));
}

int32_t json_object_dotget_boolean(const JsonObject *object, const char *name) {
    return json_value_get_boolean(json_object_dotget_value(object, name));
}

int32_t json_object_get_count(const JsonObject *object) {
    return object ? object->count : 0;
}

const char * json_object_get_name(const JsonObject *object, int32_t index) {
    if (object == NULL || index >= json_object_get_count(object)) {
        return NULL;
    }
    return object->names[index];
}

JsonValue * json_object_get_value_at(const JsonObject *object, int32_t index) {
    if (object == NULL || index >= json_object_get_count(object)) {
        return NULL;
    }
    return object->values[index];
}

JsonValue *json_object_get_wrapping_value(const JsonObject *object) {
    return object->wrapping_value;
}

int32_t json_object_has_value (const JsonObject *object, const char *name) {
    return json_object_get_value(object, name) != NULL;
}

int32_t json_object_has_value_of_type(const JsonObject *object, const char *name, JsonValue_Type type) {
    JsonValue *val = json_object_get_value(object, name);
    return val != NULL && json_value_get_type(val) == type;
}

int32_t json_object_dothas_value (const JsonObject *object, const char *name) {
    return json_object_dotget_value(object, name) != NULL;
}

int32_t json_object_dothas_value_of_type(const JsonObject *object, const char *name, JsonValue_Type type) {
    JsonValue *val = json_object_dotget_value(object, name);
    return val != NULL && json_value_get_type(val) == type;
}

/* JSON Array API */
JsonValue * json_array_get_value(const JsonArray *array, int32_t index) {
    if (array == NULL || index >= json_array_get_count(array)) {
        return NULL;
    }
    return array->items[index];
}

const char * json_array_get_string(const JsonArray *array, int32_t index) {
    return json_value_get_string(json_array_get_value(array, index));
}

double json_array_get_number(const JsonArray *array, int32_t index) {
    return json_value_get_number(json_array_get_value(array, index));
}

JsonObject * json_array_get_object(const JsonArray *array, int32_t index) {
    return json_value_get_object(json_array_get_value(array, index));
}

JsonArray * json_array_get_array(const JsonArray *array, int32_t index) {
    return json_value_get_array(json_array_get_value(array, index));
}

int32_t json_array_get_boolean(const JsonArray *array, int32_t index) {
    return json_value_get_boolean(json_array_get_value(array, index));
}

int32_t json_array_get_count(const JsonArray *array) {
    return array ? array->count : 0;
}

JsonValue * json_array_get_wrapping_value(const JsonArray *array) {
    return array->wrapping_value;
}

/* JSON Value API */
JsonValue_Type json_value_get_type(const JsonValue *value) {
    return value ? value->type : JSONError;
}

JsonObject * json_value_get_object(const JsonValue *value) {
    return json_value_get_type(value) == JSONObject ? value->value.object : NULL;
}

JsonArray * json_value_get_array(const JsonValue *value) {
    return json_value_get_type(value) == JSONArray ? value->value.array : NULL;
}

const char * json_value_get_string(const JsonValue *value) {
    return json_value_get_type(value) == JSONString ? value->value.string : NULL;
}

double json_value_get_number(const JsonValue *value) {
    return json_value_get_type(value) == JSONNumber ? value->value.number : 0;
}

int32_t json_value_get_boolean(const JsonValue *value) {
    return json_value_get_type(value) == JSONBoolean ? value->value.boolean : -1;
}

JsonValue * json_value_get_parent (const JsonValue *value) {
    return value ? value->parent : NULL;
}

void json_value_free(JsonValue *value) {
    switch (json_value_get_type(value)) {
        case JSONObject:
            json_object_free(value->value.object);
            break;
        case JSONString:
            parson_free(value->value.string);
            break;
        case JSONArray:
            json_array_free(value->value.array);
            break;
        default:
            break;
    }
    parson_free(value);
}

JsonValue * json_value_init_object(void) {
    JsonValue *new_value = (JsonValue*)parson_malloc(sizeof(JsonValue));
    if (!new_value) {
        return NULL;
    }
    new_value->parent = NULL;
    new_value->type = JSONObject;
    new_value->value.object = json_object_init(new_value);
    if (!new_value->value.object) {
        parson_free(new_value);
        return NULL;
    }
    return new_value;
}

JsonValue * json_value_init_array(void) {
    JsonValue *new_value = (JsonValue*)parson_malloc(sizeof(JsonValue));
    if (!new_value) {
        return NULL;
    }
    new_value->parent = NULL;
    new_value->type = JSONArray;
    new_value->value.array = json_array_init(new_value);
    if (!new_value->value.array) {
        parson_free(new_value);
        return NULL;
    }
    return new_value;
}

JsonValue * json_value_init_string(const char *string) {
    char *copy = NULL;
    JsonValue *value;
    int32_t string_len = 0;
    if (string == NULL) {
        return NULL;
    }
    string_len = strlen(string);
    if (!is_valid_utf8(string, string_len)) {
        return NULL;
    }
    copy = parson_strndup(string, string_len);
    if (copy == NULL) {
        return NULL;
    }
    value = json_value_init_string_no_copy(copy);
    if (value == NULL) {
        parson_free(copy);
    }
    return value;
}

JsonValue * json_value_init_number(double number) {
    JsonValue *new_value = NULL;
    if (IS_NUMBER_INVALID(number)) {
        return NULL;
    }
    new_value = (JsonValue*)parson_malloc(sizeof(JsonValue));
    if (new_value == NULL) {
        return NULL;
    }
    new_value->parent = NULL;
    new_value->type = JSONNumber;
    new_value->value.number = number;
    return new_value;
}

JsonValue * json_value_init_boolean(int32_t boolean) {
    JsonValue *new_value = (JsonValue*)parson_malloc(sizeof(JsonValue));
    if (!new_value) {
        return NULL;
    }
    new_value->parent = NULL;
    new_value->type = JSONBoolean;
    new_value->value.boolean = boolean ? 1 : 0;
    return new_value;
}

JsonValue * json_value_init_null(void) {
    JsonValue *new_value = (JsonValue*)parson_malloc(sizeof(JsonValue));
    if (!new_value) {
        return NULL;
    }
    new_value->parent = NULL;
    new_value->type = JSONNull;
    return new_value;
}

JsonValue * json_value_deep_copy(const JsonValue *value) {
    int32_t i = 0;
    JsonValue *return_value = NULL, *temp_value_copy = NULL, *temp_value = NULL;
    const char *temp_string = NULL, *temp_key = NULL;
    char *temp_string_copy = NULL;
    JsonArray *temp_array = NULL, *temp_array_copy = NULL;
    JsonObject *temp_object = NULL, *temp_object_copy = NULL;

    switch (json_value_get_type(value)) {
        case JSONArray:
            temp_array = json_value_get_array(value);
            return_value = json_value_init_array();
            if (return_value == NULL) {
                return NULL;
            }
            temp_array_copy = json_value_get_array(return_value);
            for (i = 0; i < json_array_get_count(temp_array); i++) {
                temp_value = json_array_get_value(temp_array, i);
                temp_value_copy = json_value_deep_copy(temp_value);
                if (temp_value_copy == NULL) {
                    json_value_free(return_value);
                    return NULL;
                }
                if (json_array_add(temp_array_copy, temp_value_copy) == JSONFailure) {
                    json_value_free(return_value);
                    json_value_free(temp_value_copy);
                    return NULL;
                }
            }
            return return_value;
        case JSONObject:
            temp_object = json_value_get_object(value);
            return_value = json_value_init_object();
            if (return_value == NULL) {
                return NULL;
            }
            temp_object_copy = json_value_get_object(return_value);
            for (i = 0; i < json_object_get_count(temp_object); i++) {
                temp_key = json_object_get_name(temp_object, i);
                temp_value = json_object_get_value(temp_object, temp_key);
                temp_value_copy = json_value_deep_copy(temp_value);
                if (temp_value_copy == NULL) {
                    json_value_free(return_value);
                    return NULL;
                }
                if (json_object_add(temp_object_copy, temp_key, temp_value_copy) == JSONFailure) {
                    json_value_free(return_value);
                    json_value_free(temp_value_copy);
                    return NULL;
                }
            }
            return return_value;
        case JSONBoolean:
            return json_value_init_boolean(json_value_get_boolean(value));
        case JSONNumber:
            return json_value_init_number(json_value_get_number(value));
        case JSONString:
            temp_string = json_value_get_string(value);
            if (temp_string == NULL) {
                return NULL;
            }
            temp_string_copy = parson_strdup(temp_string);
            if (temp_string_copy == NULL) {
                return NULL;
            }
            return_value = json_value_init_string_no_copy(temp_string_copy);
            if (return_value == NULL) {
                parson_free(temp_string_copy);
            }
            return return_value;
        case JSONNull:
            return json_value_init_null();
        case JSONError:
            return NULL;
        default:
            return NULL;
    }
}

int32_t json_serialization_size(const JsonValue *value) {
    char num_buf[NUM_BUF_SIZE]; /* recursively allocating buffer on stack is a bad idea, so let's do it only once */
    int32_t res = json_serialize_to_buffer_r(value, NULL, 0, 0, num_buf);
    return res < 0 ? 0 : (int32_t)(res + 1);
}

JsonStatus json_serialize_to_buffer(const JsonValue *value, char *buf, int32_t buf_size_in_bytes) {
    int32_t written = -1;
    int32_t needed_size_in_bytes = json_serialization_size(value);
    if (needed_size_in_bytes == 0 || buf_size_in_bytes < needed_size_in_bytes) {
        return JSONFailure;
    }
    written = json_serialize_to_buffer_r(value, buf, 0, 0, NULL);
    if (written < 0) {
        return JSONFailure;
    }
    return JSONSuccess;
}

JsonStatus json_serialize_to_file(const JsonValue *value, const char *filename) {
    JsonStatus return_code = JSONSuccess;
    FILE *fp = NULL;
    char *serialized_string = json_serialize_to_string(value);
    if (serialized_string == NULL) {
        return JSONFailure;
    }
    fp = fopen(filename, "w");
    if (fp == NULL) {
        json_free_serialized_string(serialized_string);
        return JSONFailure;
    }
    if (fputs(serialized_string, fp) == EOF) {
        return_code = JSONFailure;
    }
    if (fclose(fp) == EOF) {
        return_code = JSONFailure;
    }
    json_free_serialized_string(serialized_string);
    return return_code;
}

char * json_serialize_to_string(const JsonValue *value) {
    JsonStatus serialization_result = JSONFailure;
    int32_t buf_size_bytes = json_serialization_size(value);
    char *buf = NULL;
    if (buf_size_bytes == 0) {
        return NULL;
    }
    buf = (char*)parson_malloc(buf_size_bytes);
    if (buf == NULL) {
        return NULL;
    }
    serialization_result = json_serialize_to_buffer(value, buf, buf_size_bytes);
    if (serialization_result == JSONFailure) {
        json_free_serialized_string(buf);
        return NULL;
    }
    return buf;
}

int32_t json_serialization_size_pretty(const JsonValue *value) {
    char num_buf[NUM_BUF_SIZE]; /* recursively allocating buffer on stack is a bad idea, so let's do it only once */
    int32_t res = json_serialize_to_buffer_r(value, NULL, 0, 1, num_buf);
    return res < 0 ? 0 : (int32_t)(res + 1);
}

JsonStatus json_serialize_to_buffer_pretty(const JsonValue *value, char *buf, int32_t buf_size_in_bytes) {
    int32_t written = -1;
    int32_t needed_size_in_bytes = json_serialization_size_pretty(value);
    if (needed_size_in_bytes == 0 || buf_size_in_bytes < needed_size_in_bytes) {
        return JSONFailure;
    }
    written = json_serialize_to_buffer_r(value, buf, 0, 1, NULL);
    if (written < 0) {
        return JSONFailure;
    }
    return JSONSuccess;
}

JsonStatus json_serialize_to_file_pretty(const JsonValue *value, const char *filename) {
    JsonStatus return_code = JSONSuccess;
    FILE *fp = NULL;
    char *serialized_string = json_serialize_to_string_pretty(value);
    if (serialized_string == NULL) {
        return JSONFailure;
    }
    fp = fopen(filename, "w");
    if (fp == NULL) {
        json_free_serialized_string(serialized_string);
        return JSONFailure;
    }
    if (fputs(serialized_string, fp) == EOF) {
        return_code = JSONFailure;
    }
    if (fclose(fp) == EOF) {
        return_code = JSONFailure;
    }
    json_free_serialized_string(serialized_string);
    return return_code;
}

char * json_serialize_to_string_pretty(const JsonValue *value) {
    JsonStatus serialization_result = JSONFailure;
    int32_t buf_size_bytes = json_serialization_size_pretty(value);
    char *buf = NULL;
    if (buf_size_bytes == 0) {
        return NULL;
    }
    buf = (char*)parson_malloc(buf_size_bytes);
    if (buf == NULL) {
        return NULL;
    }
    serialization_result = json_serialize_to_buffer_pretty(value, buf, buf_size_bytes);
    if (serialization_result == JSONFailure) {
        json_free_serialized_string(buf);
        return NULL;
    }
    return buf;
}

void json_free_serialized_string(char *string) {
    parson_free(string);
}

JsonStatus json_array_remove(JsonArray *array, int32_t ix) {
    int32_t to_move_bytes = 0;
    if (array == NULL || ix >= json_array_get_count(array)) {
        return JSONFailure;
    }
    json_value_free(json_array_get_value(array, ix));
    to_move_bytes = (json_array_get_count(array) - 1 - ix) * sizeof(JsonValue*);
    memmove(array->items + ix, array->items + ix + 1, to_move_bytes);
    array->count -= 1;
    return JSONSuccess;
}

JsonStatus json_array_replace_value(JsonArray *array, int32_t ix, JsonValue *value) {
    if (array == NULL || value == NULL || value->parent != NULL || ix >= json_array_get_count(array)) {
        return JSONFailure;
    }
    json_value_free(json_array_get_value(array, ix));
    value->parent = json_array_get_wrapping_value(array);
    array->items[ix] = value;
    return JSONSuccess;
}

JsonStatus json_array_replace_string(JsonArray *array, int32_t i, const char* string) {
    JsonValue *value = json_value_init_string(string);
    if (value == NULL) {
        return JSONFailure;
    }
    if (json_array_replace_value(array, i, value) == JSONFailure) {
        json_value_free(value);
        return JSONFailure;
    }
    return JSONSuccess;
}

JsonStatus json_array_replace_number(JsonArray *array, int32_t i, double number) {
    JsonValue *value = json_value_init_number(number);
    if (value == NULL) {
        return JSONFailure;
    }
    if (json_array_replace_value(array, i, value) == JSONFailure) {
        json_value_free(value);
        return JSONFailure;
    }
    return JSONSuccess;
}

JsonStatus json_array_replace_boolean(JsonArray *array, int32_t i, int32_t boolean) {
    JsonValue *value = json_value_init_boolean(boolean);
    if (value == NULL) {
        return JSONFailure;
    }
    if (json_array_replace_value(array, i, value) == JSONFailure) {
        json_value_free(value);
        return JSONFailure;
    }
    return JSONSuccess;
}

JsonStatus json_array_replace_null(JsonArray *array, int32_t i) {
    JsonValue *value = json_value_init_null();
    if (value == NULL) {
        return JSONFailure;
    }
    if (json_array_replace_value(array, i, value) == JSONFailure) {
        json_value_free(value);
        return JSONFailure;
    }
    return JSONSuccess;
}

JsonStatus json_array_clear(JsonArray *array) {
    int32_t i = 0;
    if (array == NULL) {
        return JSONFailure;
    }
    for (i = 0; i < json_array_get_count(array); i++) {
        json_value_free(json_array_get_value(array, i));
    }
    array->count = 0;
    return JSONSuccess;
}

JsonStatus json_array_append_value(JsonArray *array, JsonValue *value) {
    if (array == NULL || value == NULL || value->parent != NULL) {
        return JSONFailure;
    }
    return json_array_add(array, value);
}

JsonStatus json_array_append_string(JsonArray *array, const char *string) {
    JsonValue *value = json_value_init_string(string);
    if (value == NULL) {
        return JSONFailure;
    }
    if (json_array_append_value(array, value) == JSONFailure) {
        json_value_free(value);
        return JSONFailure;
    }
    return JSONSuccess;
}

JsonStatus json_array_append_number(JsonArray *array, double number) {
    JsonValue *value = json_value_init_number(number);
    if (value == NULL) {
        return JSONFailure;
    }
    if (json_array_append_value(array, value) == JSONFailure) {
        json_value_free(value);
        return JSONFailure;
    }
    return JSONSuccess;
}

JsonStatus json_array_append_boolean(JsonArray *array, int32_t boolean) {
    JsonValue *value = json_value_init_boolean(boolean);
    if (value == NULL) {
        return JSONFailure;
    }
    if (json_array_append_value(array, value) == JSONFailure) {
        json_value_free(value);
        return JSONFailure;
    }
    return JSONSuccess;
}

JsonStatus json_array_append_null(JsonArray *array) {
    JsonValue *value = json_value_init_null();
    if (value == NULL) {
        return JSONFailure;
    }
    if (json_array_append_value(array, value) == JSONFailure) {
        json_value_free(value);
        return JSONFailure;
    }
    return JSONSuccess;
}

JsonStatus json_object_set_value(JsonObject *object, const char *name, JsonValue *value) {
    int32_t i = 0;
    JsonValue *old_value;
    if (object == NULL || name == NULL || value == NULL || value->parent != NULL) {
        return JSONFailure;
    }
    old_value = json_object_get_value(object, name);
    if (old_value != NULL) { /* free and overwrite old value */
        json_value_free(old_value);
        for (i = 0; i < json_object_get_count(object); i++) {
            if (strcmp(object->names[i], name) == 0) {
                value->parent = json_object_get_wrapping_value(object);
                object->values[i] = value;
                return JSONSuccess;
            }
        }
    }
    /* add new key value pair */
    return json_object_add(object, name, value);
}

JsonStatus json_object_set_string(JsonObject *object, const char *name, const char *string) {
    return json_object_set_value(object, name, json_value_init_string(string));
}

JsonStatus json_object_set_number(JsonObject *object, const char *name, double number) {
    return json_object_set_value(object, name, json_value_init_number(number));
}

JsonStatus json_object_set_boolean(JsonObject *object, const char *name, int32_t boolean) {
    return json_object_set_value(object, name, json_value_init_boolean(boolean));
}

JsonStatus json_object_set_null(JsonObject *object, const char *name) {
    return json_object_set_value(object, name, json_value_init_null());
}

JsonStatus json_object_dotset_value(JsonObject *object, const char *name, JsonValue *value) {
    const char *dot_pos = NULL;
    JsonValue *temp_value = NULL, *new_value = NULL;
    JsonObject *temp_object = NULL, *new_object = NULL;
    JsonStatus status = JSONFailure;
    int32_t name_len = 0;
    if (object == NULL || name == NULL || value == NULL) {
        return JSONFailure;
    }
    dot_pos = strchr(name, '.');
    if (dot_pos == NULL) {
        return json_object_set_value(object, name, value);
    }
    name_len = dot_pos - name;
    temp_value = json_object_getn_value(object, name, name_len);
    if (temp_value) {
        /* Don't overwrite existing non-object (unlike json_object_set_value, but it shouldn't be changed at this point) */
        if (json_value_get_type(temp_value) != JSONObject) {
            return JSONFailure;
        }
        temp_object = json_value_get_object(temp_value);
        return json_object_dotset_value(temp_object, dot_pos + 1, value);
    }
    new_value = json_value_init_object();
    if (new_value == NULL) {
        return JSONFailure;
    }
    new_object = json_value_get_object(new_value);
    status = json_object_dotset_value(new_object, dot_pos + 1, value);
    if (status != JSONSuccess) {
        json_value_free(new_value);
        return JSONFailure;
    }
    status = json_object_addn(object, name, name_len, new_value);
    if (status != JSONSuccess) {
        json_object_dotremove_internal(new_object, dot_pos + 1, 0);
        json_value_free(new_value);
        return JSONFailure;
    }
    return JSONSuccess;
}

JsonStatus json_object_dotset_string(JsonObject *object, const char *name, const char *string) {
    JsonValue *value = json_value_init_string(string);
    if (value == NULL) {
        return JSONFailure;
    }
    if (json_object_dotset_value(object, name, value) == JSONFailure) {
        json_value_free(value);
        return JSONFailure;
    }
    return JSONSuccess;
}

JsonStatus json_object_dotset_number(JsonObject *object, const char *name, double number) {
    JsonValue *value = json_value_init_number(number);
    if (value == NULL) {
        return JSONFailure;
    }
    if (json_object_dotset_value(object, name, value) == JSONFailure) {
        json_value_free(value);
        return JSONFailure;
    }
    return JSONSuccess;
}

JsonStatus json_object_dotset_boolean(JsonObject *object, const char *name, int32_t boolean) {
    JsonValue *value = json_value_init_boolean(boolean);
    if (value == NULL) {
        return JSONFailure;
    }
    if (json_object_dotset_value(object, name, value) == JSONFailure) {
        json_value_free(value);
        return JSONFailure;
    }
    return JSONSuccess;
}

JsonStatus json_object_dotset_null(JsonObject *object, const char *name) {
    JsonValue *value = json_value_init_null();
    if (value == NULL) {
        return JSONFailure;
    }
    if (json_object_dotset_value(object, name, value) == JSONFailure) {
        json_value_free(value);
        return JSONFailure;
    }
    return JSONSuccess;
}

JsonStatus json_object_remove(JsonObject *object, const char *name) {
    return json_object_remove_internal(object, name, 1);
}

JsonStatus json_object_dotremove(JsonObject *object, const char *name) {
    return json_object_dotremove_internal(object, name, 1);
}

JsonStatus json_object_clear(JsonObject *object) {
    int32_t i = 0;
    if (object == NULL) {
        return JSONFailure;
    }
    for (i = 0; i < json_object_get_count(object); i++) {
        parson_free(object->names[i]);
        json_value_free(object->values[i]);
    }
    object->count = 0;
    return JSONSuccess;
}

JsonStatus json_validate(const JsonValue *schema, const JsonValue *value) {
    JsonValue *temp_schema_value = NULL, *temp_value = NULL;
    JsonArray *schema_array = NULL, *value_array = NULL;
    JsonObject *schema_object = NULL, *value_object = NULL;
    JsonValue_Type schema_type = JSONError, value_type = JSONError;
    const char *key = NULL;
    int32_t i = 0, count = 0;
    if (schema == NULL || value == NULL) {
        return JSONFailure;
    }
    schema_type = json_value_get_type(schema);
    value_type = json_value_get_type(value);
    if (schema_type != value_type && schema_type != JSONNull) { /* null represents all values */
        return JSONFailure;
    }
    switch (schema_type) {
        case JSONArray:
            schema_array = json_value_get_array(schema);
            value_array = json_value_get_array(value);
            count = json_array_get_count(schema_array);
            if (count == 0) {
                return JSONSuccess; /* Empty array allows all types */
            }
            /* Get first value from array, rest is ignored */
            temp_schema_value = json_array_get_value(schema_array, 0);
            for (i = 0; i < json_array_get_count(value_array); i++) {
                temp_value = json_array_get_value(value_array, i);
                if (json_validate(temp_schema_value, temp_value) == JSONFailure) {
                    return JSONFailure;
                }
            }
            return JSONSuccess;
        case JSONObject:
            schema_object = json_value_get_object(schema);
            value_object = json_value_get_object(value);
            count = json_object_get_count(schema_object);
            if (count == 0) {
                return JSONSuccess; /* Empty object allows all objects */
            } else if (json_object_get_count(value_object) < count) {
                return JSONFailure; /* Tested object mustn't have less name-value pairs than schema */
            }
            for (i = 0; i < count; i++) {
                key = json_object_get_name(schema_object, i);
                temp_schema_value = json_object_get_value(schema_object, key);
                temp_value = json_object_get_value(value_object, key);
                if (temp_value == NULL) {
                    return JSONFailure;
                }
                if (json_validate(temp_schema_value, temp_value) == JSONFailure) {
                    return JSONFailure;
                }
            }
            return JSONSuccess;
        case JSONString: case JSONNumber: case JSONBoolean: case JSONNull:
            return JSONSuccess; /* equality already tested before switch */
        case JSONError: default:
            return JSONFailure;
    }
}

int32_t json_value_equals(const JsonValue *a, const JsonValue *b) {
    JsonObject *a_object = NULL, *b_object = NULL;
    JsonArray *a_array = NULL, *b_array = NULL;
    const char *a_string = NULL, *b_string = NULL;
    const char *key = NULL;
    int32_t a_count = 0, b_count = 0, i = 0;
    JsonValue_Type a_type, b_type;
    a_type = json_value_get_type(a);
    b_type = json_value_get_type(b);
    if (a_type != b_type) {
        return 0;
    }
    switch (a_type) {
        case JSONArray:
            a_array = json_value_get_array(a);
            b_array = json_value_get_array(b);
            a_count = json_array_get_count(a_array);
            b_count = json_array_get_count(b_array);
            if (a_count != b_count) {
                return 0;
            }
            for (i = 0; i < a_count; i++) {
                if (!json_value_equals(json_array_get_value(a_array, i),
                                       json_array_get_value(b_array, i))) {
                    return 0;
                }
            }
            return 1;
        case JSONObject:
            a_object = json_value_get_object(a);
            b_object = json_value_get_object(b);
            a_count = json_object_get_count(a_object);
            b_count = json_object_get_count(b_object);
            if (a_count != b_count) {
                return 0;
            }
            for (i = 0; i < a_count; i++) {
                key = json_object_get_name(a_object, i);
                if (!json_value_equals(json_object_get_value(a_object, key),
                                       json_object_get_value(b_object, key))) {
                    return 0;
                }
            }
            return 1;
        case JSONString:
            a_string = json_value_get_string(a);
            b_string = json_value_get_string(b);
            if (a_string == NULL || b_string == NULL) {
                return 0; /* shouldn't happen */
            }
            return strcmp(a_string, b_string) == 0;
        case JSONBoolean:
            return json_value_get_boolean(a) == json_value_get_boolean(b);
        case JSONNumber:
            return fabs(json_value_get_number(a) - json_value_get_number(b)) < 0.000001; /* EPSILON */
        case JSONError:
            return 1;
        case JSONNull:
            return 1;
        default:
            return 1;
    }
}

JsonValue_Type json_type(const JsonValue *value) {
    return json_value_get_type(value);
}

JsonObject * json_object (const JsonValue *value) {
    return json_value_get_object(value);
}

JsonArray * json_array  (const JsonValue *value) {
    return json_value_get_array(value);
}

const char * json_string (const JsonValue *value) {
    return json_value_get_string(value);
}

double json_number (const JsonValue *value) {
    return json_value_get_number(value);
}

int32_t json_boolean(const JsonValue *value) {
    return json_value_get_boolean(value);
}

void json_set_allocation_functions(JsonMalloc_Function malloc_fun, JsonFree_Function free_fun) {
    parson_malloc = malloc_fun;
    parson_free = free_fun;
}

void json_set_escape_slashes(int32_t escape_slashes) {
    parson_escape_slashes = escape_slashes;
}
