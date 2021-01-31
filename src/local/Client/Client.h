#pragma once


class Client : public Pi::Application, public Pi::Singleton<Client>
{
public:
    Client();
    ~Client();

    virtual void ApplicationTask() override;

private:

    bool needQuit = false;
};
