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

// Friday, October 25, 2019

#include <jtk/collection/Pair.h>

/*******************************************************************************
 * Pair                                                                        *
 *******************************************************************************/

/* Constructor */

jtk_Pair_t* jtk_Pair_new() {
    jtk_Pair_t* pair = jtk_Memory_allocate(jtk_Pair_t, 1);
    pair->m_left = NULL;
    pair->m_right = NULL;
    
    return pair;
}

void jtk_Pair_delete(jtk_Pair_t* pair) {
    jtk_Memory_deallocate(pair);
}

/* Left */

void jtk_Pair_setLeft(jtk_Pair_t* pair, void* element) {
    pair->m_left = element;
}

void* jtk_Pair_getLeft(jtk_Pair_t* pair) {
    return pair->m_left;
}

/* Right */

void jtk_Pair_setRight(jtk_Pair_t* pair, void* element) {
    pair->m_right = element;
}

void* jtk_Pair_getRight(jtk_Pair_t* pair) {
    return pair->m_right;
}