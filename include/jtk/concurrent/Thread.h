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

// Sunday, August 26, 2018

#ifndef JTK_CONCURRENT_THREAD_H
#define JTK_CONCURRENT_THREAD_H

/*******************************************************************************
 * Thread                                                                      *
 *******************************************************************************/

#define JTK_THREAD_FLAG_WRAPPER (1 << 0)
#define JTK_THREAD_FLAG_INTERRUPTIBLE (1 << 1)

#define JTK_THREAD_STATE_INTERRUPTED

/**
 * Determines whether this thread has begun execution.
 */
#define JTK_THREAD_STATE_ALIVE

/**
 * A thread is an independent path of execution within a process. Multiple
 * threads can run concurrently within a process, either synchronously or
 * asynchronosly. Every thread in JTK is created and controlled by the Thread
 * class.
 *
 * Every thread has a priority. The priority determines ...
 *
 * A thread may have a looper associated with it. A thread with a looper
 * is called a looper thread. A looper thread periodically checks the
 * message queue for new messages. The messages may originate from any
 * thread, but is executed only on an associated looper thread. This
 * continous poll begins with the invocation of loop().
 *
 * The looper makes up the core of a looper thread. Basically, a looper
 * is an infinite loop which exits only when certain conditions arise.
 *
 * A thread may have a single message queue associated with it. A regular
 * thread, by default, has neither a looper nor message queue. The
 * `jtk_Thread_prepare()` attaches a looper and a message queue to the
 * current thread.
 *
 * Interestingly, these features are not limited to non-wrapper threads.
 * Any thread which can invoke `jtk_Thread_prepare()` has access to the
 * looper mechanism.
 *
 *    looper thread (say thread_0)
 *           loop()
 *     <--------------------.
 *     |                    |
 *     V                    |
 * fetch message     dispatch message
 *     |                    |
 *     V                    |
 *  message ----------------'
 *  message queue
 *    ^-------- message from some other thread (say thread_1)
 *    ^----------------- message from some other thread (say thread_2)
 *    ^------------------------- message from some other thread (say thread_2)
 *
 * A looper may encounter two types of messages in the message queue:
 * -- A message holding a predefined message code.
 * -- A message holding a user defined message code.
 * Messages with predefined message code are automatically interpreted
 * by the dispatcher, located in the looper. Whereas, messages with user
 * defined message codes are dispatched to their associated handlers,
 * which in turn receive and interpret the message code.
 *
 * ```
 * jtk_Thread_t* thread = jtk_Thread_getCurrentThread();
 * if (!jtk_Thread_hasLooper(thread)) {
 *     jtk_Thread_prepare(thread);
 *     jtk_Thread_loop(thread);
 * }
 * ```
 *
 * @class Thread
 * @ingroup jtk_concurrent
 * @author Samuel Rowe <samuelrowe1999@gmail.com>
 * @since JTK 1.1
 */
struct jtk_Thread_t {
	/**
	 * The thread attributes requested via one of the constructors, to which
     * the framework makes no promises to acknowledge.
	 */
    jtk_ThreadAttributes_t* m_attributes;

    /**
	 * The top-level error handler for this thread. When no error handler is
	 * specified, by default, the `jtk_DefaultErrorHandler_handleError`
     * is used.
	 */
	jtk_ErrorHandlerFunction_ts m_errorHandler;

    /**
	 * The interruption handler for this thread. It is notified when this
     * thread is interrupted. When no error handler is specified, by default,
     * the `jtk_DefaultInterruptionHandler_handleInterruption` is used.
	 */
    jtk_InterruptionHandlerFunction_t m_interruptionHandler;

    /**
     * The termination status of this thread. This attribute is valid only
     * if this thread is terminated.
     */
    int32_t m_exitCode;

    /**
     * A system dependent handle to the actual thread in memory, used when
     * invoking native functions.
     */
    void* m_handle;

    /**
     * An unique integer value that identifies this thread throughout the
     * system.
     */
    int64_t m_identifier;

    /**
     * The name of this thread.
     */
    jtk_String_t* m_name;

    /**
     * The priority of this thread. By default, it is assigned to a normal
     * priority (to be specific, `JTK_THREAD_PRIORITY_NORMAL`).
     */
    ThreadPriority m_priority;

    /**
     * The entry point of this thread. It is invoked when this thread is
     * started.
     */
    jtk_ThreadEntryFunction_t m_entry;

	int32_T m_flags;

    /**
     * The looper associated with this thread. By default, a thread is
     * not associated with any looper.
     */
    jtk_Looper_t* m_looper;

    /**
     * Determines whether this thread is interruptible, or not.
     */
    bool m_interruptible;

    /**
     * When interruptible, determines whether this thread was interrupted,
     * or not.
     */
    bool m_interrupted;
};

/**
 * @memberof Thread
 */
typedef struct jtk_Thread_t jtk_Thread_t;

/* Constructor */

/**
 * @memberof Thread
 */
jtk_Thread_t* jtk_Thread_new(jtk_ThreadEntryFunction_t entry, jtk_ThreadAttributes_t* attributes);

/* Destructor */

/**
 * @memberof Thread
 */
void jtk_Thread_delete(jtk_Thread_t* thread);

/* Alive */

/**
 * Determines whether the specified thread is alive or not.
 *
 * @param  thread
 *         The thread to test.
 * @return {@code true} if the thread is alive; {@code false} otherwise.
 */
bool jtk_Thread_isAlive(jtk_Thread_t* thread);

/* Attributes */

/**
 * Returns the thread attributes that were requested by the user.
 *
 * @param thread
 *        The thread whose thread attributes are required.
 * @return The thread attributes.
 */
jtk_ThreadAttributes_t* jtk_Thread_getAttributes(jtk_Thread_t* thread);

/* Bundle */

void jtk_Thread_setBundle(jtk_Thread_t* thread, void* bundle);
void* jtk_Thread_getBundle(jtk_Thread_t* thread);

/* Current Thread */

/**
 * @memberof Thread
 */
jtk_Thread_t* jtk_Thread_getCurrentThread();

/* Error Handler */

/**
 * Sets the error handler for the specified thread.
 *
 * @param  errorHandler
 *		   The error handler that is notified when an error is signaled.
 */
void jtk_Thread_setExceptionHandler(jtk_Thread_t* thread, ExceptionHandler* errorHandler);

/**
 * Returns the exception handler of this thread.
 *
 * @return The exception handler of this thread.
 */
jtk_ErrorHandler_t* jtk_Thread_getErrorHandler(jtk_Thread_t* thread);

/* Exit Code */

/**
 * The termination status of this thread.
 *
 * @return The termination status of this thread. It returns `-1` if the thread
 *         is unterminated.
 * @error JTK_ERROR_ILLEGAL_THREAD_STATE
 *        The `JTK_ERROR_ILLEGAL_THREAD_STATE` error code is signaled,
 *        if the thread is not terminated.
 */
int32_t jtk_Thread_getExitCode(jtk_Thread_t* thread);

/* Handle */

/**
 * Returns the native handle of this thread, initialized when start() is
 * invoked. A valid handle is returned thereafter; {@code null} otherwise.
 * Any modifications made using the native application programming
 * interface may not be reflected here. Therefore, use the handle with
 * proper care.
 *
 * @return The native handle of this thread.
 */
void* jtk_Thread_getHandle(jtk_Thread_t* thread);

/* Identifier */

int64_t jtk_Thread_getIdentifier(jtk_Thread_t* thread);

/* Interrupt */

void jtk_Thread_interrupt(jtk_Thread_t* thread);
void jtk_Thread_clear(jtk_Thread_t* thread);

/* Interruption Handler */

void jtk_Thread_setInterruptionHandler(jtk_Thread_t* thread, jtk_InterruptionHandlerFunction_t handler);
jtk_InterruptionHandlerFunction_t jtk_Thread_getInterruptionHandler(jtk_Thread_t* thread);

/* Interruptible */

bool jtk_Thread_isInterruptible(jtk_Thread_t* thread);
void jtk_Thread_setInterruptible(jtk_Thread_t* thread, bool interruptible);

/* Looper */

bool jtk_Thread_hasLooper(jtk_Thread_t* thread);
void jtk_Thread_bindLooper(jtk_Thread_t* thread);
void jtk_Thread_getLooper(jtk_Thread_t* thread);

/* Name */

void jtk_Thread_setName(jtk_Thread_t* thread, const uint8_t* name, int32_t length);
jtk_StringBuffer_t* jtk_Thread_getName(jtk_Thread_t* thread);

/* Priority */

void jtk_Thread_setPriority(jtk_Thread_t* thread, jtk_ThreadPriority_t priority);
jtk_ThreadPriority_t jtk_Thread_getPriority(jtk_Thread_t* thread);

/* Sleep */

/**
 * The `jtk_Thread_sleep()` function causes the currently executing thread to
 * sleep for the specified interval. In other words, it requests the system
 * to temporarily suspend the execution of the current thread. The exact
 * duration of the temporary suspension is system dependent. Moreover, the
 * scheduler is free to ignore the request placed by this function.
 *
 * @param  interval
 *         This argument specifies the time, in milliseconds, for which to
 *         suspend execution. Zero or negative values cause the system to
 *         decide the duration of suspension.
 * @memberof Thread
 */
void jtk_Thread_sleep(int64_t interval);

/* Start */

void jtk_Thread_start(jtk_Thread_t* thread);

/* Wrapper */

/**
 * Determines whether this instance was created by the framework to wrap
 * a thread which was not created by the framework. This condition arises
 * when `getCurrentThread()` is invoked on a thread without a correspoding
 * `Thread` instance. Wrapper threads have limited modification capabilities.
 */
bool jtk_Thread_isWrapper(jtk_Thread_t* thread);

/* Yield */

/**
 * The `jtk_Thread_yield()` function causes the currently executing thread to
 * yield execution to another thread on the current processor. The exact duration
 * of the temporary suspension is system dependent. Moreover, the scheduler
 * is free to ignore the request placed by this function.
 *
 * @memberof Thread
 */
void jtk_Thread_yield();

#endif /* JTK_CONCURRENT_THREAD_H */