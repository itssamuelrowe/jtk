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

#ifndef JTK_FS_FILE_HELPER_H
#define JTK_FS_FILE_HELPER_H

/*******************************************************************************
 * FileHelper                                                                  *
 *******************************************************************************/
 
/* Create */

bool jtk_FileHelper_create(jtk_Path_t* path);
bool jtk_FileHelper_createEx(jtk_Path_t* path, int32_t flags);

/* Create Temporary */

jtk_Path_t* jtk_FileHelper_createTemporary(const uint8_t* prefix, int32_t prefixLength, const uint8_t* suffix, int32_t suffixLength);
jtk_Path_t* jtk_FileHelper_createTemporaryEx(const uint8_t* prefix, int32_t prefixLength, const uint8_t* suffix, int32_t suffixLength, jtk_Path_t* directory);

/* Remove */

bool jtk_FileHelper_remove(jtk_Path_t* path);

/* Size */

bool jtk_FileHelper_getSize(jtk_Path_t* path);

#endif /* JTK_FS_FILE_HELPER_H */