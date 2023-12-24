#include "bd_log.h"

typedef struct
{
  va_list args;
  const char *fmt;
  const char *file;
  struct tm *time;
  void *udata;
  int line;
  int level;
} log_t;

static const char *level_strings[] = {
    "DEBUG", "INFO", "WARN", "ERROR"};

#ifdef LOG_USE_COLOR
static const char *level_colors[] = {
    "\x1b[36m", "\x1b[32m", "\x1b[33m", "\x1b[31m"};
#endif
static void bd_log_init(log_t *log, void *udata)
{
  if (!log->time)
  {
    time_t t = time(NULL);
    log->time = localtime(&t);
  }
  log->udata = udata;
}

static void bd_log_out(log_t *log)
{
  char buf[16];
  buf[strftime(buf, sizeof(buf), "%H:%M:%S", log->time)] = '\0';
#ifdef LOG_USE_COLOR
  fprintf(
      log->udata, "%s%-5s %s\t\x1b[0m \x1b[90m%s:%d:\t\x1b[0m",level_colors[log->level], buf, level_strings[log->level], log->file, log->line);
#else
  fprintf(
      log->udata, "%s %-5s %s:%d: ",
      buf, level_strings[log->level], log->file, log->line);
#endif
  vfprintf(log->udata, log->fmt, log->args);
  fprintf(log->udata, "\n");
  fflush(log->udata);
}

void bd_log(int level, const char *filename, int line, const char *format, ...)
{
  log_t log = {
      .fmt = format,
      .file = filename,
      .line = line,
      .level = level,
  };

  bd_log_init(&log, stdout);
  va_start(log.args, format);
  bd_log_out(&log);
  va_end(log.args);
}