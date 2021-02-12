#pragma once


struct DataNetwork
{
    DataNetwork(const Vector3 &vec) { buffer.WriteVector3(vec); }

    VectorBuffer buffer;
};
