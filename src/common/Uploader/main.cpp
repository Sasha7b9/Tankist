#include "stdafx.h"
#include "Uploader.h"
#include "Utils/_Log.h"
#ifdef WIN32
#pragma warning(push, 0)
#endif
#include <iostream>
#ifdef WIN32
#pragma warning(pop)
#endif


int main(int, char *[]) //-V2504
{
    setlocale(LC_ALL, "Russian");

    Log::Create("Uploader.log");

    if (!gConfig.Load("Uploader.conf"))
    {
        return -1;
    }

    return Uploader().Run();
}