#ifndef __BD_LOG_H__
#define __BD_LOG_H__

#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>

#define LOG_USE_COLOR

enum
{
    LOG_DEBUG,
    LOG_INFO,
    LOG_WARN,
    LOG_ERROR
};
#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#define BD_LOG_DEBUG(...) bd_log(LOG_DEBUG, __FILENAME__, __LINE__, __VA_ARGS__)
#define BD_LOG_INFO(...) bd_log(LOG_INFO, __FILENAME__, __LINE__, __VA_ARGS__)
#define BD_LOG_WARN(...) bd_log(LOG_WARN, __FILENAME__, __LINE__, __VA_ARGS__)
#define BD_LOG_ERROR(...) bd_log(LOG_ERROR, __FILENAME__, __LINE__, __VA_ARGS__)

void bd_log(int level, const char *filename, int line, const char *format, ...);

#endif /* __BD_LOG_H__ */
