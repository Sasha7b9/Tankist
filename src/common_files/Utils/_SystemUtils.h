#pragma once


#define DISPLAY_LAST_ERROR() System::DisplayLastError(__FILE__, __LINE__)

namespace System
{
    void DisplayLastError(const char *file, int line);
}
