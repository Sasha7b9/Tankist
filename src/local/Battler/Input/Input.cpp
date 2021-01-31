#include "stdafx.h"


MovementAction::MovementAction(unsigned long type, unsigned long flag) : Action(type) //-V126
{
    movementFlag = flag;
}


MovementAction::~MovementAction()
{
}


void MovementAction::Begin(void)
{
    TheMainServer->SendMessage(PlayerType::Server, MovementMessage(movementFlag, true));
}


void MovementAction::End(void)
{
    TheMainServer->SendMessage(PlayerType::Server, MovementMessage(movementFlag, false));
}
