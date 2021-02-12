#pragma once


struct DataNetwork
{
    DataNetwork() {}

    DataNetwork(const String &text) { buffer.WriteString(text); }

    DataNetwork(const Vector3 &vec) { buffer.WriteVector3(vec); }

    VectorBuffer buffer;
};
