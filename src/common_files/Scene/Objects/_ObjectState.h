/* (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by */
#pragma once


struct ObjectState
{
    virtual ~ObjectState() {};
    void Send();

    virtual void Compress(VectorBuffer &buffer) const = 0;
    virtual void Decompress(VectorBuffer &buffer) = 0;
};
