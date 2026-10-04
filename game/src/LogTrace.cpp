#include "LogTrace.h"

namespace LogTrace
{

static constexpr uint32_t MAX_LOG_MSG_LENGTH = 256;
static LogTrace::Level minLogTypeLevel = LogTrace::Level::LOG_INFO;

void setLevel(LogTrace::Level logType)
{
    minLogTypeLevel = logType;
}

void print(LogTrace::Level logType, const char* text, ...)
{
    if (logType < minLogTypeLevel) return;

    va_list args;
    va_start(args, text);

    char buffer[LogTrace::MAX_LOG_MSG_LENGTH] = { 0 };

    switch (logType)
    {
    case LogTrace::Level::LOG_TRACE:
        strcpy(buffer, "TRACE: ");
        break;
    case LogTrace::Level::LOG_DEBUG:
        strcpy(buffer, "DEBUG: ");
        break;
    case LogTrace::Level::LOG_INFO:
        strcpy(buffer, "INFO: ");
        break;
    case LogTrace::Level::LOG_WARNING:
        strcpy(buffer, "WARNING: ");
        break;
    case LogTrace::Level::LOG_ERROR:
        strcpy(buffer, "ERROR: ");
        break;
    case LogTrace::Level::LOG_FATAL:
        strcpy(buffer, "FATAL: ");
        break;
    }

    size_t textSize = strlen(text);
    memcpy(buffer + strlen(buffer), text, (textSize < (LogTrace::MAX_LOG_MSG_LENGTH - 12))? textSize : (LogTrace::MAX_LOG_MSG_LENGTH - 12));
    strcat(buffer, "\n");
    vprintf(buffer, args);
    fflush(stdout);

    va_end(args);

    if (logType == LogTrace::Level::LOG_FATAL)
    {
        exit(EXIT_FAILURE);
    }
}

}