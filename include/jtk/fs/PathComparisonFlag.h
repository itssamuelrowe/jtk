// Tuesday, May 03, 2019

#ifndef JTK_FS_PATH_COMPARISON_FLAG_H
#define JTK_FS_PATH_COMPARISON_FLAG_H

/*******************************************************************************
 * PathComparisonFlag                                                          *
 *******************************************************************************/

/**
 * @class PathComparisonFlag
 * @ingroup jtk_fs
 * @author Samuel Rowe
 * @since jtk 1.1
 */
enum jtk_PathComparisonFlag_t {
    JTK_PATH_COMPARISON_FLAG_SIMPLE,
    JTK_PATH_COMPARISON_FLAG_ABSOLUTE,
    JTK_PATH_COMPARISON_FLAG_CANONICAL
};

/**
 * @memberof PathComparisonFlag
 */
typedef enum jtk_PathComparisonFlag_t jtk_PathComparisonFlag_t;

#endif /* JTK_FS_PATH_COMPARISON_FLAG_H */