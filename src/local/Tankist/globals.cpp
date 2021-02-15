// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"


Tankist *TheGame = nullptr;
MainWindow *TheMainWindow = nullptr;
AttemptConnectionWindow *TheAttemptConnectionWindow = nullptr;
FailedConnectionWindow *TheFailedConnectionWindow = nullptr;


ConfigurationFile gConfig;
MasterServer      gMaster;
