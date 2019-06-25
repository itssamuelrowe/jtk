// Friday, October 12, 2018

#ifndef JTK_SUPPORT_TIME_LOGGER_H
#define JTK_SUPPORT_TIME_LOGGER_H

#include <jtk/chrono/Timer.h>

/*******************************************************************************
 * TimeLogger                                                                  *
 *******************************************************************************/

struct jtk_TimeLogger_t {
    jtk_Timer_t* m_timer;
};

typedef struct jtk_TimeLogger_t jtk_TimeLogger_t;

#endif /* JTK_SUPPORT_TIME_LOGGER_H */