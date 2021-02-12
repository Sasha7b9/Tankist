#include "defines.h"


DataNetwork::DataNetwork(const Vector3 &vec)
{
    buffer.WriteVector3(vec);
}
