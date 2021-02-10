#pragma once


#define LOG_WRITE(...)   LogT::Write(__FILE__, __LINE__, __VA_ARGS__)
#define LOG_FUNC_ENTER() URHO3D_LOGINFOF(">>>>>>>>>>>>>>>            %s", __FUNCTION__);
#define LOG_FUNC_LEAVE() URHO3D_LOGINFOF("<<<<<<<<<<<<<<<            %s", __FUNCTION__);


class LogT
{
public:
    static void Write(const char *file, int line, const char *format, ...);
};
