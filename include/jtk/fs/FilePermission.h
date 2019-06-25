
// Sunday, May 05, 2019

#ifndef JTK_FS_FILE_PERMISSION_H
#define JTK_FS_FILE_PERMISSION_H

/*******************************************************************************
 * FilePermission                                                              *
 *******************************************************************************/

#define JTK_FILE_PERMISSION_OWNER_ALL ((1 << 0) | (1 << 1) | (1 << 2))
#define JTK_FILE_PERMISSION_OWNER_READ (1 << 0)
#define JTK_FILE_PERMISSION_OWNER_WRITE (1 << 1)
#define JTK_FILE_PERMISSION_OWNER_EXECUTE (1 << 2)
#define JTK_FILE_PERMISSION_GROUP_ALL ((1 << 3) | (1 << 4) | (1 << 5))
#define JTK_FILE_PERMISSION_GROUP_READ (1 << 3)
#define JTK_FILE_PERMISSION_GROUP_WRITE (1 << 4)
#define JTK_FILE_PERMISSION_GROUP_EXECUTE (1 << 5)
#define JTK_FILE_PERMISSION_EVERYONE_ALL ((1 << 6) | (1 << 7) | (1 << 8))
#define JTK_FILE_PERMISSION_EVERYONE_READ (1 << 6)
#define JTK_FILE_PERMISSION_EVERYONE_WRITE (1 << 7)
#define JTK_FILE_PERMISSION_EVERYONE_EXECUTE (1 << 8)

#endif /* JTK_FS_FILE_PERMISSION_H */