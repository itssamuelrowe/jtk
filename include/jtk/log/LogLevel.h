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

// Sunday, March 24, 2019

#ifndef JTK_LOG_LOG_LEVEL_H
#define JTK_LOG_LOG_LEVEL_H

#include <jtk/Configuration.h>
#include <jtk/core/Integer.h>

/*******************************************************************************
 * LogLevel                                                                    *
 *******************************************************************************/

/**
 * @class LogLevel
 * @ingroup jtk_log
 * @author Samuel Rowe
 * @since JTK 2.0
 */
enum jtk_LogLevel_t {

    /**
     * {@code JTK_LOG_LEVEL_ALL} indicates that all the messages are logged.
     *
     * This level is equivalent to {@code JTK_INTEGER_MIN_VALUE}.
     */
    JTK_LOG_LEVEL_ALL = JTK_INTEGER_MIN_VALUE,

    /**
     * {@code JTK_LOG_LEVEL_FINEST} indicates all the messages that are
     * considered highly detailed information should be logged.
     *
     * This level is initialized to {@code 1000}.
     */
    JTK_LOG_LEVEL_FINEST = 1000,

    /**
     * {@code JTK_LOG_LEVEL_FINER} indicates that all the messages that are
     * considered fairly detailed information should be logged.
     *
     * Messages that inform entering functions or exiting functions are usually
     * traced at this level.
     *
     * This level is initialized to {@code 2000}.
     */
    JTK_LOG_LEVEL_FINER = 2000,

    /**
     * {@code JTK_LOG_LEVEL_FINE} indicates that all the messages that are
     * considered important information should be logged.
     *
     * Messages that inform recoverable errors, recoverable failures, and issues
     * that that may cause potential performance problems are usually traced
     * at this level.
     *
     * This level is initialized to {@code 3000}.
     */
    JTK_LOG_LEVEL_FINE = 3000,

    /**
     * {@code JTK_LOG_LEVEL_DEBUG} indicates that all the messages that are
     * considered useful for debugging problems should be logged.
     *
     * Messages that inform internal state of the application are usually traced
     * at this level.
     *
     * This level is initialized to {@code 4000}.
     */
    JTK_LOG_LEVEL_DEBUG = 4000,

    /**
     * {@code JTK_LOG_LEVEL_CONFIGURATION} indicates that all the messages that
     * are considered static configuration of the application should be logged.
     *
     * Messages that inform application configuration such as machine architecture,
     * graphics context, and other relevant information are usually traced
     * at this level.
     *
     * This level is initialized to {@code 5000}.
     */
    JTK_LOG_LEVEL_CONFIGURATION = 5000,

    /**
     * {@code JTK_LOG_LEVEL_INFORMATION} indicates that all the messages that
     * are general information should be logged.
     *
     * Messages that inform application configuration such as initialization
     * of modules, beginning and ending of tasks, and other relevant information
     * are usually traced at this level.
     *
     * This level is initialized to {@code 6000}.
     */
    JTK_LOG_LEVEL_INFORMATION = 6000,

    /**
     * {@code JTK_LOG_LEVEL_WARNING} indicates that all the messages that
     * specify potential problems should be logged.
     *
     * This level is initialized to {@code 7000}.
     */
    JTK_LOG_LEVEL_WARNING = 7000,

    /**
     * {@code JTK_LOG_LEVEL_SEVERE} indicates that all the messages that
     * specify serious failures should be logged.
     *
     * In general, messages that inform serious failures that may prevent normal
     * execution of the application are usually traced at this level. Such events
     * may include module initialization failure and other relevant events.
     *
     * This level is initialized to {@code 8000}.
     */
    JTK_LOG_LEVEL_SEVERE = 8000,

    /**
     * {@code JTK_LOG_LEVEL_ERROR} indicates that all the messages that
     * specify serious errors should be logged.
     *
     * In general, messages that inform serious errors that prevented normal
     * execution of the application are usually traced at this level.
     *
     * This level is initialized to {@code 9000}.
     */
    JTK_LOG_LEVEL_ERROR = 9000,

    /**
     * {@code JTK_LOG_LEVEL_NONE} indicates that none of the messages are
     * logged.
     *
     * This level is initialized to {@code JTK_INTEGER_MAX_VALUE}.
     */
    JTK_LOG_LEVEL_NONE = JTK_INTEGER_MAX_VALUE
};

/**
 * @memberof LogLevel
 */
typedef enum jtk_LogLevel_t jtk_LogLevel_t;

#endif /* JTK_LOG_LOG_LEVEL_H */