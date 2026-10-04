#ifndef LOGTRACE_SOLITAIRE_H
#define LOGTRACE_SOLITAIRE_H

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <cstdint>

namespace LogTrace
{

enum class Level
{
    LOG_ALL = 0,
    LOG_TRACE,
    LOG_DEBUG,
    LOG_INFO,
    LOG_WARNING,
    LOG_ERROR,
    LOG_FATAL,
    LOG_NONE
};

void setLevel(Level logType);
void print(Level logType, const char* text, ...);

} // namespace LogTrace

#define LOG_INFO(...)    LogTrace::print(LogTrace::Level::LOG_INFO, __VA_ARGS__)
#define LOG_WARNING(...) LogTrace::print(LogTrace::Level::LOG_WARNING, __VA_ARGS__)
#define LOG_ERROR(...)   LogTrace::print(LogTrace::Level::LOG_ERROR, __VA_ARGS__)
#define LOG_FATAL(...)   LogTrace::print(LogTrace::Level::LOG_FATAL, __VA_ARGS__)

#endif