/* (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by */
#include "stdafx.h"


void ObjectState::Send() const
{
    Message::SendObjectState(*this).Send(true);
}
