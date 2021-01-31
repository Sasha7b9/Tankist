#include "stdafx.h"


void System::DisplayLastError(const char *file, int line)
{
#ifdef WIN32

#define LMEM_ZEROINIT       0x0040
typedef LPCSTR PCTSTR, LPCTSTR, PCUTSTR, LPCUTSTR;

    void* lpMsgBuf = nullptr;
    void* lpDisplayBuf = nullptr;
    DWORD dw = GetLastError();

    FormatMessageA(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL,
        dw,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR)&lpMsgBuf,
        0, NULL);

    lpDisplayBuf = (void *)LocalAlloc(LMEM_ZEROINIT, (lstrlenA((LPCTSTR)lpMsgBuf) + 40) * sizeof(TCHAR)); //-V2571 //-V303 //-V104

    char buffer[500];
    std::sprintf(buffer, "%s:%d : Error %d : %s", file, line, (int)dw, (char *)lpMsgBuf); //-V2571
    buffer[std::strlen(buffer) - 1] = '\0';

    LOG_ERROR(buffer); //-V576

    LocalFree(lpMsgBuf);
    LocalFree(lpDisplayBuf);

#else

    LOG_ERROR("error %d in line %s : %d", errno, file, line);

#endif
}
