// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "globals.h"
#include "FileSystem/_ConfigurationFile.h"
#include "Utils/_Log.h"
#include <iostream>


int main(int, char *[]) //-V2504
{
    setlocale(LC_ALL, "Russian");

    Log::Create("Updater.log");

    if (!gConfig.Load("Updater.conf"))
    {
        return -1;
    }

    gMaster.Connnect();

    std::string address = gMaster.GetValue(MASTER_GET_ADDRESS_UPLOADER);

    gMaster.Destroy();

    gUploader.Connect(address.c_str());

    return gUploader.UpdateFiles() ? 0 : -1;
}
