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

// Wednesday, September 05, 2018

#ifndef JTK_CONCURRENT_LOOPER_THREAD_LOOPER_AVAILABLITY_LISTENER_H
#define JTK_CONCURRENT_LOOPER_THREAD_LOOPER_AVAILABLITY_LISTENER_H

/*******************************************************************************
 * ThreadLooperAvailablityListener                                             *
 *******************************************************************************/

/**
 * @class ThreadLooperAvailablityListener
 * @ingroup jtk_concurrent_looper
 * @author Samuel Rowe <samuelrowe1999@gmail.com>
 * @since 1.1
 */
struct jtk_ThreadLooperAvailablityListener_t {
    jtk_ThreadLooperAvailablityListener_OnBeforeAttachmentFunction_t m_onBeforeAttachment;
    jtk_ThreadLooperAvailablityListener_OnAvailableFunction_t m_onAvailable;
};

/**
 * @memberof ThreadLooperAvailablityListener
 */
typedef struct jtk_ThreadLooperAvailablityListener_t jtk_ThreadLooperAvailablityListener_t;

/* Constructor */

/**
 * @memberof ThreadLooperAvailablityListener
 */
jtk_ThreadLooperAvailablityListener_t* jtk_ThreadLooperAvailablityListener_new();

/* Destructor */

/**
 * @memberof ThreadLooperAvailablityListener
 */
void jtk_ThreadLooperAvailablityListener_delete(jtk_ThreadLooperAvailablityListener_t* listener);

/* Publish */

/**
 * @memberof ThreadLooperAvailablityListener
 */
void jtk_ThreadLooperAvailablityListener_publishBeforeAttachmentEvent(jtk_ThreadLooperAvailablityListener_t* listener, jtk_Thread_t* thread);

/**
 * @memberof ThreadLooperAvailablityListener
 */
void jtk_ThreadLooperAvailablityListener_publishAvailableEvent(jtk_ThreadLooperAvailablityListener_t* listener, jtk_Thread_t* thread);

#endif /* JTK_CONCURRENT_LOOPER_THREAD_LOOPER_AVAILABLITY_LISTENER_H */