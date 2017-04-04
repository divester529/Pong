#include "Instance.h"
#include <windows.h>
#include <stdio.h>

Instance::Instance()
{
    states[0]= new GameState();
    states[1]= new GameOverState();
    curState=0;
}

void Instance::getInput(MSG* msg)
{
   curState=states[curState]->swapState;

   states[curState]->getInput(msg);
}

void Instance::doLogic()
{
    states[curState]->doLogic();
}

void Instance::render()
{
    states[curState]->render();
}
