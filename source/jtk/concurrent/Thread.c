// Thursday, August 30, 2018

#include <jtk/concurrent/Thread.h>

/*******************************************************************************
 * Thread                                                                      *
 *******************************************************************************/

/* Constructor */

jtk_Thread_t* jtk_Thread_new(jtk_ThreadEntryFunction_t entry,
    jtk_ThreadAttributes_t* attributes) {
    jtk_Thread_t* thread = jtk_Memory_allocate(jtk_Memory_t, 1);
    thread->m_attributes = attributes;
    thread->m_errorHandler = jtk_DefaultErrorHandler_handleError;
    thread->m_interruptionHandler = jtk_DefaultInterruptionHandler_handleInterruption;
    thread->m_exitCode = -1;
    thread->m_handle = NULL;
    thread->m_identifier = -1;
    thread->m_name = jtk_String_new("Anonymous");
    thread->m_priority = JTK_THREAD_PRIORITY_NORMAL;
    thread->m_entry = NULL;
    thread->m_flags = 0;
    thread->m_looper = NULL;
    thread->m_interruptible = true;
    thread->m_interrupted = false;

    return thread;
}

/* Destructor */

void jtk_Thread_delete(jtk_Thread_t* thread) {
    jtk_Assert_assertObject(thread, "The specified thread is null.");

    if ((thread->m_flags & JTK_THREAD_FLAG_WRAPPER) != 0) {
        if (thread->m_handle != NULL) {
            jtk_Error_t error = JTK_ERROR_NONE;
            jtk_NativeThread_destroy(thread->m_handle, &error);
            jtk_NativeHelper_checkError("jtk_NativeThread_destroy", error);
        }

        if (thread->m_looper != NULL) {
            /* TODO: Should we call jtk_ThreadLooper_quit() or
             * jtk_ThreadLooper_abort() or something?
             */
            jtk_ThreadLooper_delete(thread->m_looper);
        }
    }

    jtk_Memory_deallocate(thread);
}

/* Alive */

bool jtk_Thread_isAlive(jtk_Thread_t* thread) {
    jtk_Assert_assertObject(thread, "The specified thread is null.");

    jtk_Mutex_lock(thread->m_mutex);
    bool result = (thread->m_state & JTK_THREAD_STATE_ALIVE) != 0;
    jtk_Mutex_unlock(thread->m_mutex);

    return result;
}

/* Exit Code */

int32_t jtk_Thread_getExitCode(jtk_Thread_t* thread) {
    jtk_Assert_assertObject(thread, "The specified thread is null.");

    jtk_Mutex_lock(thread->m_mutex);

    int32_t result = -1;
    if ((thread->m_state & JTK_THREAD_STATE_ALIVE) == 0) {
        jtk_System_setError(JTK_ERROR_ILLEGAL_THREAD_STATE, "Thread is alive.");
    }
    else {
        result = jtk_NativeThread_getExitCode(thread->m_handle);
    }

    /* Unlock the lock. */
    jtk_Mutex_unlock(thread->m_mutex);

    return result;
}

/* Handle */

void* jtk_Thread_getHandle(jtk_Thread_t* thread) {
    jtk_Assert_assertObject(thread, "The specified thread is null.");

    jtk_Mutex_lock(thread->m_mutex);

    void* handle = thread->m_handle;

    jtk_Mutex_unlock(thread->m_mutex);

    return handle;
}

/* Identifier */

/* Does not return the native thread identifier. */
int64_t jtk_Thread_getIdentifier(jtk_Thread_t* thread) {
    jtk_Assert_assertObject(thread, "The specified thread is null.");

    jtk_Mutex_lock(thread->m_mutex);

    int64_t identifier = thread->m_identifier;

    jtk_Mutex_unlock(thread->m_mutex);

    return identifier;
}

/* Looper */

void jtk_Thread_prepare(jtk_Thread_t* thread) {
    jtk_Assert_assertObject(thread, "The specified thread is null.");

    jtk_Mutex_lock(thread->m_mutex);

    jtk_Thread_t* currentThread = jtk_Thread_getCurrentThread();
    if (currentThread != thread) {
        jtk_System_setError(JTK_ERROR_ILLEGAL_MUTATOR_THREAD, "Cannot create a looper from a different thread.");
    }
    else {
        if (thread->m_looper->m_looperAvailabilityListener != NULL) {
            jtk_ThreadLooperAvailablityListener_publishBeforeAttachmentEvent(thread->m_looperAvailabilityListener, thread);
        }

        thread->m_looper = jtk_ThreadLooper_new(thread);

        if (thread->m_looper->m_looperAvailabilityListener != NULL) {
            jtk_ThreadLooperAvailablityListener_publishAvailableEvent(thread->m_looperAvailabilityListener, thread);
        }
    }

    jtk_Mutex_unlock(thread->m_mutex);
}

bool jtk_Thread_hasLooper(jtk_Thread_t* thread) {
    jtk_Assert_assertObject(thread, "The specified thread is null.");

    jtk_Mutex_lock(thread->m_mutex);

    bool result = (thread->m_looper != NULL);

    jtk_Mutex_unlock(thread->m_mutex);

    return result;
}

jtk_Looper_t* jtk_Thread_getLooper(jtk_Thread_t* thread) {
    jtk_Assert_assertObject(thread, "The specified thread is null.");

    jtk_Mutex_lock(thread->m_mutex);

    jtk_Looper_t* result = thread->m_looper;

    jtk_Mutex_unlock(thread->m_mutex);

    return result;
}