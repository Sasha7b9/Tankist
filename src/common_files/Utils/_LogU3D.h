#pragma once


#define LOG_WRITE(...) LogT::Write(__FILE__, __LINE__, __VA_ARGS__)


class LogT
{
public:
    static void Write(char *file, int line, char *format, ...);
};
