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