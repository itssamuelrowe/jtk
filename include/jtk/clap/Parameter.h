// Saturday, April 06, 2019

#ifndef JTK_CLAP_PARAMETER_H
#define JTK_CLAP_PARAMETER_H

#include <jtk/Configuration.h>
#include <jtk/clap/ParameterType.h>
#include <jtk/collection/list/ArrayList.h>
#include <jtk/core/String.h>

/*******************************************************************************
 * Parameter                                                                   *
 *******************************************************************************/

#define JTK_PARAMETER_FLAG_DEFAULT_RESULT (1 << 0)
#define JTK_PARAMETER_FLAG_INVALID_RESULT (1 << 1)
#define JTK_PARAMETER_FLAG_GENERIC_RESULT (1 << 2)
#define JTK_PARAMETER_FLAG_EMPTY_VALUE (1 << 3)
#define JTK_PARAMETER_FLAG_SINGLE_VALUE (1 << 4)
#define JTK_PARAMETER_FLAG_MULTIPLE_VALUES (1 << 5)

/**
 * @memberof Parameter
 */
typedef struct jtk_Parameter_t jtk_Parameter_t;

/**
 * @memberof Parameter
 */
typedef void (*jtk_Parameter_OnHandleFunction_t)(jtk_Parameter_t* argument, void* result, int32_t flags);

#define JTK_ARGUMENT_CONSUMPTION_MODE_REQUIRED 1
#define JTK_ARGUMENT_CONSUMPTION_MODE_GREEDY 2
#define JTK_ARGUMENT_CONSUMPTION_MODE_CONSIDERABLE 3

/**
 * @class Parameter
 * @ingroup jtk_clap
 * @author Samuel Rowe
 * @since JTK 1.1
 */
struct jtk_Parameter_t {
    jtk_String_t* m_usage;
    bool m_required;
    bool m_hidden;
    jtk_Parameter_OnHandleFunction_t m_onHandle;
    int32_t m_index;
    int32_t m_minValues;
    int32_t m_maxValues;
    int32_t m_consumptionMode;
    jtk_String_t* m_separator;
    jtk_String_t* m_shortFlag;
    jtk_String_t* m_longFlag;
    jtk_String_t* m_name;
    bool m_acceptEmptyValue;
    jtk_ArrayList_t* m_dependencies;
    jtk_ArrayList_t* m_forbids;
    jtk_ParameterType_t* m_type;
    void* m_defaultResult;
};

#endif /* JTK_CLAP_PARAMETER_H */