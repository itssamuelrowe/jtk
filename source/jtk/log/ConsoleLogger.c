/*
 * Copyright 2018-2020 Samuel Rowe
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

// Sunday, March 21, 2020

#include <jtk/log/ConsoleLogger.h>

#define JTK_COLOR_RED "\033[0;31m"
#define JTK_COLOR_BOLD_RED "\033[1;31m"
#define JTK_COLOR_GREEN "\033[0;32m"
#define JTK_COLOR_BOLD_GREEN "\033[1;32m"
#define JTK_COLOR_YELLOW "\033[0;33m"
#define JTK_COLOR_BOLD_YELLOW "\033[01;33m"
#define JTK_COLOR_BLUE "\033[0;34m"
#define JTK_COLOR_BOLD_BLUE "\033[1;34m"
#define JTK_COLOR_MAGENTA "\033[0;35m"
#define JTK_COLOR_BOLD_MAGENTA "\033[1;35m"
#define JTK_COLOR_CYAN "\033[0;36m"
#define JTK_COLOR_BOLD_CYAN "\033[1;36m"
#define JTK_COLOR_WHITE "\033[0;37m"
#define JTK_COLOR_BOLD_WHITE "\033[1;37m"
#define JTK_COLOR_RESET "\033[0m"

/*******************************************************************************
 * ConsoleLogger                                                               *
 *******************************************************************************/

// Log

// TODO: Check if time and other details must be printed. The configuration
// can be retrieved from the logger.
void jtk_ConsoleLogger_log(jtk_Logger_t* logger, jtk_LogRecord_t* record) {
    if (!record->m_filtered) {
        const char* color = NULL;
        switch (record->m_level) {
            case JTK_LOG_LEVEL_FINEST: {
                color = JTK_COLOR_BOLD_WHITE;
                break;
            }

            case JTK_LOG_LEVEL_FINER: {
                color = JTK_COLOR_WHITE;
                break;
            }

            case JTK_LOG_LEVEL_FINE: {
                color = JTK_COLOR_CYAN;
                break;
            }

            case JTK_LOG_LEVEL_DEBUG: {
                color = JTK_COLOR_BOLD_BLUE;
                break;
            }

            case JTK_LOG_LEVEL_CONFIGURATION: {
                color = JTK_COLOR_YELLOW;
                break;
            }

            case JTK_LOG_LEVEL_INFORMATION: {
                color = JTK_COLOR_BOLD_GREEN;
                break;
            }

            case JTK_LOG_LEVEL_WARNING: {
                color = JTK_COLOR_BOLD_YELLOW;
                break;
            }

            case JTK_LOG_LEVEL_SEVERE: {
                color = JTK_COLOR_RED;
                break;
            }

            case JTK_LOG_LEVEL_ERROR: {
                color = JTK_COLOR_BOLD_RED;
                break;
            }

            default: {
                color = JTK_COLOR_RESET;
                break;
            }
        }
        
        fprintf(stdout, "%s[%.*s]\033[0m %.*s\n", color, record->m_tag->m_size,
            record->m_tag->m_value, record->m_message->m_size, record->m_message->m_value);
        fflush(stdout);
    }
}