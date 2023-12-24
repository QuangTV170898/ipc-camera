#ifndef __BD_TIMER_H__
#define __BD_TIMER_H__

#include <stdint.h>
#include <stdbool.h>


typedef uint32_t (*bd_platform_ticks_t)(void);

typedef struct bd_timer_handle bd_timer;

typedef void (*bd_timer_callback)(bd_timer* timer, void* userData);

struct bd_timer_handle {
    bd_timer* next;
    uint32_t deadline;
    uint32_t period;
    bd_timer_callback callback;
    void* userData;
};

int bd_timer_init(bd_platform_ticks_t ticksFunc);

int bd_timer_create(bd_timer *timer, uint32_t period, bd_timer_callback cb, void *userData);

int bd_timer_start(bd_timer *timer, uint32_t startTime);

int bd_timer_stop(bd_timer *timer);

bool bd_timer_activated(bd_timer *timer);


#endif /* __BD_TIMER_H__ */
