#include <stdio.h>
#include "bd_timer.h"

#define MULTIMER_MAX_TIMEOUT 0x7fffffff
#define CHECK_TIME_LESS_THAN(t, compare_to) ((((uint32_t)((t) - (compare_to))) > MULTIMER_MAX_TIMEOUT) ? 1 : 0)

static bd_timer *list = NULL;

static bd_platform_ticks_t ticks = NULL;

int bd_timer_init(bd_platform_ticks_t ticksFunc)
{
    ticks = ticksFunc;
    return 0;
}

int bd_timer_create(bd_timer *timer, uint32_t period, bd_timer_callback cb, void *userData)
{
    if (!timer || !cb)
    {
        return -1;
    }
    timer->callback = cb;
    timer->userData = userData;
    timer->period = period;
    return 0;
}

int bd_timer_start(bd_timer *timer, uint32_t startTime)
{
    bd_timer **next = &list;

    /* Remove the existing target timer. */
    for (; *next; next = &(*next)->next)
    {
        if (timer == *next)
        {
            *next = timer->next; /* remove from list */
            break;
        }
    }

    /* New deadline time. */
    timer->deadline = ticks() + startTime;

    /* Insert timer. */
    for (next = &list;; next = &(*next)->next)
    {
        if (!*next)
        {
            timer->next = NULL;
            *next = timer;
            break;
        }
        if (timer->deadline < (*next)->deadline)
        {
            timer->next = *next;
            *next = timer;
            break;
        }
    }
    return 0;
}

int bd_timer_stop(bd_timer *timer)
{
    bd_timer **next = &list;

    /* Find and remove timer. */
    for (; *next; next = &(*next)->next)
    {
        bd_timer *entry = *next;
        if (entry == timer)
        {
            *next = timer->next;
            break;
        }
    }
    return 0;
}

bool bd_timer_activated(bd_timer *timer)
{
    bd_timer *entry = list;
    while (entry)
    {
        if (entry == timer)
        {
            return true;
        }
        entry = entry->next;
    }
    return false;
}

void bd_timer_start_all(void)
{
    bd_timer **next = &list;

    for (; *next; next = &(*next)->next)
    {
        bd_timer *entry = *next;
        /* Sorted list, just process with the front part. */
        if (CHECK_TIME_LESS_THAN(ticks(), entry->deadline))
        {
            return;
        }
        /* remove expired timer from list */
        *next = entry->next;

        if (entry->period)
        {
            bd_timer_start(entry, entry->period);
        }
        if (entry->callback)
        {
            entry->callback(entry, entry->userData);
        }
        if (entry->next == NULL)
        {
            return;
        }
    }
}
