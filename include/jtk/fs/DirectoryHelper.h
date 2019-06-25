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

// Wednesday, August 29, 2018

#ifndef JTK_FS_DIRECTORY_HELPER_H
#define JTK_FS_DIRECTORY_HELPER_H

#define JTK_DIRECTORY_CREATION_FLAG_NORMAL (1 << 0)
#define JTK_DIRECTORY_CREATION_FLAG_EXTENSIVE (1 << 1)

/*******************************************************************************
 * DirectoryHelper                                                             *
 *******************************************************************************/

/* Create */

bool jtk_DirectoryHelper_create(jtk_Path_t* path);

bool jtk_DirectoryHelper_createEx(jtk_Path_t* path, int32_t flags);

/* List */

jtk_ArrayList_t* jtk_DirectoryHelper_list(jtk_Path_t* path);
jtk_ArrayList_t* jtk_DirectoryHelper_listEx(jtk_Path_t* path, jtk_PathFilterFunction_t filter);

/* Remove */

bool jtk_DirectoryHelper_remove(jtk_Path_t* path);

#endif /* JTK_FS_DIRECTORY_HELPER_H */