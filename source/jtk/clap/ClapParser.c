#include <jtk/clap/ClapParser.h>

/*******************************************************************************
 * ClapParser                                                                  *
 *******************************************************************************/

// Parse

// TODO: BUGS!! We pass some strings to publish without making a defensive copy.
void jtk_ClapParser_parse(jtk_ClapParser_t* parser, jtk_Array_t* arguments) {
    int32_t argumentIndex = 0;
    int32_t numberOfElements = jtk_Array_getSize(arguments);
    int32_t wildcardIndex = -1;
    jtk_ArrayList_t* wildcards = jtk_ClapConfiguration_getWildcardParameters(parser->m_configuration);
    int32_t wildcardSize = jtk_ArrayList_getSize(wildcards);
    
    for (int32_t index = 0; index < numberOfElements; index++) {
        jtk_String_t* argument = (jtk_String_t*)jtk_Array_getValue(arguments, index);
        int32_t argumentSize = jtk_String_getSize(argument);
        
        /* Elements that begin with '-' character are considered as flags. */
        if ((argumentSize > 0) && (jtk_String_getCharacter(argument, 0) == '-')) {
            bool recognizeLongName = false;
            /* Determine whether the flag has short name or long name. */
            if ((argumentSize > 1) && (jtk_String_getCharacter(argument, 1) == '-')) {
                recognizeLongName = true;
            }

            /* The name of the argument recognized, either long or short. */
            jtk_String_t* name = NULL;
            /* The format of the argument recognized. */
            jtk_Parameter_t* format = NULL;
            /* The raw value of the argument recognized, if any. */
            jtk_String_t* rawValue = NULL;
            /* The flags that provide additional details about the result. */
            int32_t flags = 0;
            /* Determines whether the result is publishable, or not. */
            bool publishable = true;
            /* The result to publish, it is either `jtk_String_t*` or `jtk_Array_t*`. */
            void* result = NULL;
            /* The index of the `=` character, if any. */
            int32_t equalIndex = jtk_String_find_c(argument, '=');

            /* If an equal is found within the string, the parser has to extract
             * the values specified.
             */
            if (equalIndex > 0) {
                /* Extract the name of the argument specified. Since, the parser
                 * has already recognized three characters ('-', '-', and '=')
                 * the argument name is valid only if the difference between
                 * start index of the name and the equal symbol is greater than
                 * one. Otherwise, the argument is considered malformed and of
                 * the form `--=...`, where `...` is the value which may or may
                 * not be present.
                 */
                int32_t nameStartIndex = recognizeLongName? 2 : 1;
                if ((equalIndex - nameStartIndex) > 1) {
                    name = jtk_String_substring(nameStartIndex, equalIndex);

                    /* Retrieve the argument format for the extracted name. */
                    format = jtk_ClapConfiguration_getParameterEx(parser->m_configuration,
                        name, recognizeLongName);

                    /* The values specified to the argument may be single or multiple,
                     * in which case each value is separated by a separator.
                     *
                     * Make sure that the argument accepts empty values, in case an empty
                     * value is encountered. Otherwise, delegate the error handling to
                     * the user specified error handler.
                     *
                     * To extract the raw value, the parser looks beyond the `=` symbol.
                     * Therefore, the raw value is considered empty if the difference
                     * between the argument size and index of `=` is equal to one.
                     * Alternatively, `equalIndex + 1 == argumentSize` is equivalent
                     * to the previously mentioned constraint.
                     */
                    if ((argumentSize - equalIndex) == 1) {
                        rawValue = jtk_String_newEmpty();
                        flags |= JTK_PARAMETER_FLAG_EMPTY_VALUE;
                    }
                    else {
                        /* Extract the raw value, excludig the `=` character. */
                        int32_t rawValueStartIndex = equalIndex + 1;
                        rawValue = jtk_String_substring(argument, rawValueStartIndex, argumentSize);

                        /* If a separator was configured, then the raw value will be split
                         * and is processed further.
                         */
                        jtk_String_t* separator = jtk_Parameter_getSeparator(format);
                        if (separator != NULL) {
                            /* Split the raw value at every occurrence of the separator. */
                            jtk_Array_t* values = jtk_String_split(rawValue, separator);
                            /* Determine the number of values derived from the raw value. */
                            int32_t numberOfValues = jtk_Array_getSize(values);
                            
                            /* The number of values must be greater than or equal to
                             * the configured minimum or lesser than or equal to the
                             * configured maximum. Otherwise, report an error.
                             */
                            if (jtk_Parameter_isValidNumberOfValues(argument, numberOfValues)) {
                                jtk_ParameterType_t* type = jtk_Parameter_getType(format);
                                bool valid = true;

                                if (type != NULL) {
                                    int32_t j;
                                    for (j = 0; j < numberOfValues; j++) {
                                        jtk_String_t* value = (jtk_String_t*)jtk_Array_getValue(values, j);
                                        valid = jtk_ParameterType_validate(type, value);

                                        /* If the validation of the value failed, mark the result
                                         * as invalid. The loop is not terminated because empty
                                         * values may be present.
                                         */
                                        if (!valid) {
                                            flags |= JTK_PARAMETER_FLAG_INVALID_RESULT;
                                        }
                                        
                                        if (jtk_String_isEmpty(value)) {
                                            flags |= JTK_PARAMETER_FLAG_EMPTY_VALUE;
                                        }
                                    }
                                }
                                else {
                                    /* The validator was specified, mark the result as generic. */
                                    flags |= JTK_PARAMETER_FLAG_GENERIC_RESULT;
                                }

                                flags |= JTK_PARAMETER_FLAG_MULTIPLE_VALUES;
                                result = values;
                            }
                            else {
                                // parser->m_onError(argument, JTK_CLAP_ERROR_INVALID_VALUE_COUNT);
                            }
                        }
                    }

                }
                else {
                    // parser->m_onError(argument, JTK_CLAP_ERROR_INVALID_ARGUMENT_NAME);
                }
            }
            else {
                /*
                int32_t consumptionMode = jtk_Parameter_getConsumptionMode(format);
                if (consumptionMode == JTK_ARGUMENT_CONSUMPTION_MODE_GREEDY) {
                    int32_t required = numberOfElements - index;
                    jtk_Array_t* values = jtk_Array_new(required);
                    
                    while (index < required) { // No idea why I've written required here! :V
                        jtk_String_t* value = jtk_Array_getValue(arguments, index);
                        jtk_Array_setValue(values, index, value);
                        index++;
                    }
                }
                else if (consumptionMode == JTK_ARGUMENT_CONSUMPTION_MODE_CONSIDERABLE) {
                    int32_t required = jtk_Parameter_getMinExpectedValues(wildcard);
                    int32_t limit = index + required;
                    if (limit <= numberOfElements) {
                        jtk_Array_t* values = jtk_Array_new(required);
                        
                        while (index < limit) {
                            jtk_String_t* value = jtk_Array_getValue(arguments, index);
                            if (jtk_String_startsWith_c(value, '-')) {
                                // error(FAILED TO CONUSME MINIMUM, FOUND --)
                                break;
                            }
                        }
                    }
                    else {
                    // error(MISSING VALUES)
                    }
                }
                else if (consumptionMode == JTK_ARGUMENT_CONSUMPTION_MODE_REQUIRED) {
                    jtk_ArrayList_t* values = jtk_ArrayList_new();
                    int32_t limit = index + jtk_Parameter_getMinExpectedValues(format);
                    if (limit <= numberOfElements) {
                        while (index < limit) {
                            jtk_String_t* value = jtk_Array_getValue(arguments, index);
                            if (jtk_String_startsWith_c(value, '-')) {
                                publishable = false;
                                // error(FAILED TO CONSUME  MINIMUM, FOUND --)
                                break;
                            }
                            
                            jtk_ArrayList_add(values, value);
                            index++;
                        }
                        
                        /* If the results are publishable, the minimum number of values
                         * have been specified. The parser is inherently greedy and will
                         * try to consume more values, with the maximum expected values
                         * preventing the parser from being overly greedy.
                         *
                        if (publishable) {
                            int32_t maxExpectedValues = jtk_Parameter_getMaxExpectedValues(format);
                            limit = index + jtk_Integer_min(numberOfElements - index, maxExpectedValues);
                            while (index < limit) {
                                jtk_String_t* value = jtk_Array_getValue(arguments, index);
                                /* If another flag is encontered, the parse backtracks and avoids
                                 * consumption.
                                 *
                                if (jtk_String_startsWith_c(value, '-')) {
                                    index--;
                                    break;
                                }
                                
                                jtk_ArrayList_add(values, value);
                                index++;
                            }
                            
                            result = jtk_ArrayList_toArray(values);
                        }
                    }
                    else {
                        // error (MISSING VALUES)
                    }
                }
                */
            }
            
            if (publishable) {
                /* Publish the results to the handler associated with the argument. */
                jtk_Parameter_publish(argument, result, flags);
            }

            argumentIndex++;
        }
        else {
            if ((wildcardIndex + 1) < wildcardSize) {
                jtk_Parameter_t* wildcard = jtk_ArrayList_getValue(wildcards, wildcardIndex);
                wildcardIndex++;
                
                int32_t consumptionMode = jtk_Parameter_getConsumptionMode(wildcard);
                if (consumptionMode == JTK_ARGUMENT_CONSUMPTION_MODE_GREEDY) {
                    int32_t required = numberOfElements - index;
                    jtk_Array_t* values = jtk_Array_new(required);
                    
                    while (index < required) { // No idea why I've used required here.
                        jtk_String_t* value = jtk_Array_getValue(arguments, index);
                        jtk_Array_setValue(values, index, value);
                        index++;
                    }
                }
                else if (consumptionMode == JTK_ARGUMENT_CONSUMPTION_MODE_CONSIDERABLE) {
                    int32_t required = jtk_Parameter_getMinExpectedValues(wildcard);
                    int32_t limit = index + required;
                    if (limit <= numberOfElements) {
                        jtk_Array_t* values = jtk_Array_new(required);
                        
                        while (index < limit) {
                            jtk_String_t* value = jtk_Array_getValue(arguments, index);
                            if (jtk_String_startsWith_c(value, '-')) {
                                // error(FAILED TO CONUSME MINIMUM, FOUND --)
                                break;
                            }
                        }
                    }
                    else {
                    }
                    // error(MISSING VALUES)
                    
                }
            }
        }
    }
}
