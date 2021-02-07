#pragma once


#define LOG_WRITE(...) LogT::Write(__FILE__, __LINE__, __VA_ARGS__)
#define LOG_FUNC_ENTER LogT::Write(__FILE__, __LINE__, "%s enter", __FUNCTION__);
#define LOG_FUNC_LEAVE LogT::Write(__FILE__, __LINE__, "%s leave", __FUNCTION__);


class LogT
{
public:
    static void Write(char *file, int line, char *format, ...);
};
