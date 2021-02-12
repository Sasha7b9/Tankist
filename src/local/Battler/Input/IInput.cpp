#include "stdafx.h"


IInput::IInput(Context *context) : Object(context)
{
    input = GetSubsystem<Input>();
}
