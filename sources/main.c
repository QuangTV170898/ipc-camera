#include <stdio.h>
#include <unistd.h>
#include "bd_log.h"

int main()
{
    BD_LOG_INFO("APP start");
    BD_LOG_DEBUG("APP start");
    BD_LOG_WARN("APP start");
    BD_LOG_ERROR("APP start");
    while (1)
    {
        usleep(1000);
    }

    return 0;
}