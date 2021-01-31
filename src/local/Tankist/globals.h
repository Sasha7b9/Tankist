#pragma once


class Tankist;
class MainWindow;
class AttemptConnectionWindow;
class FailedConnectionWindow;

extern Tankist *TheGame;
extern MainWindow *TheMainWindow;
extern AttemptConnectionWindow* TheAttemptConnectionWindow;
extern FailedConnectionWindow* TheFailedConnectionWindow;

extern ConfigurationFile gConfig;
extern MasterServer      gMaster;
