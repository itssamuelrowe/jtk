// Saturday, June 30, 2018

#ifndef JTK_UNIT_TEST_DEFECT_TYPE_H
#define JTK_UNIT_TEST_DEFECT_TYPE_H

/*******************************************************************************
 * TestDefectType                                                              *
 *******************************************************************************/

/**
 * @enum TestDefectType
 * @ingroup jtk_unit
 * @author Samuel Rowe <samuelrowe1999@gmail.com>
 * @since JTK 1.0
 */
enum jtk_TestDefectType_t {
    JTK_TEST_DEFECT_FAILURE,
    JTK_TEST_DEFECT_ERROR,
    JTK_TEST_DEFECT_UNKNOWN_ERROR
};

/**
 * @memberof TestDefectType
 */
typedef enum jtk_TestDefectType_t jtk_TestDefectType_t;

#endif /* JTK_UNIT_TEST_DEFECT_TYPE_H */