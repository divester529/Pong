#ifndef STATE_H_INCLUDED
#define STATE_H_INCLUDED
#include <windows.h>

class State
{
public:
    //State()=0;

    virtual void getInput(MSG* msg)=0;

    virtual void doLogic()=0;

    virtual void render()=0;

    int swapState; // Returns -1 or state number
};

#endif // STATE_H_INCLUDED
