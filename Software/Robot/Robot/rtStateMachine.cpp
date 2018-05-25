#include "rtStateMachine.h" 
//-----------------------------------------------------------------------------




//-----------------------------------------------------------------------------
static SM::AStateMachine sm;
//-----------------------------------------------------------------------------





//-----------------------------------------------------------------------------
using namespace SM;
///----------------------------------------------------------------------------





 ///---------------------------------------------------------------------------
///
/// Constructor
///
///----------------------------------------------------------------------------
AState :: AState(FAction actionUpdate, int time)
	:
	signal_enter	(nullptr),
	signal_update	(actionUpdate),
	signal_exit		(nullptr),
	timeActive		(time)
{

}
///----------------------------------------------------------------------------





 ///---------------------------------------------------------------------------
///
/// Constructor
///
///----------------------------------------------------------------------------
AState :: AState(FAction actionEnter, FAction actionUpdate, FAction actionExit, int time)
	:
	signal_enter(actionEnter),
	signal_update(actionUpdate),
	signal_exit(actionExit),
	timeActive(time)
{

}



//what to do when entering this state
void AState::onEnter() 
{
	if (signal_enter)
	{
		signal_enter();
	}
}

//what to do when this state updates
void AState :: onUpdate() 
{
	if (signal_update) 
	{
		signal_update();
	}
}

//what to do when exiting this state
void AState::onExit() 
{
	if (signal_exit) 
	{
		signal_exit();
	}
}
///----------------------------------------------------------------------------







///----------------------------------------------------------------------------
///----------------------------------------------------------------------------
///----------------------------------------------------------------------------
///----------------------------------------------------------------------------
///----------------------------------------------------------------------------
///----------------------------------------------------------------------------
///----------------------------------------------------------------------------






 ///---------------------------------------------------------------------------
///
/// Constructor
///
///----------------------------------------------------------------------------
AStateMachine :: AStateMachine()
	:
	mCurrentState(nullptr),
	mNextState(nullptr),
	mTimeActive(0),
	mNextTime(0)
{

}
///----------------------------------------------------------------------------






 ///---------------------------------------------------------------------------
///
/// обновления действия
///
///----------------------------------------------------------------------------
AStateMachine& AStateMachine :: update()
{
	if (mCurrentState != mNextState) 
	{
		transition();
	}
	
	if (mCurrentState)
	{
		mCurrentState->onUpdate();
	}

	if (millis() >= mTimeActive)
	{
		mNextState = nullptr;
		mNextTime = 0;
		transition();
		if (signal_next)
		{
			signal_next();
		}
	}

	return *this;
}
///----------------------------------------------------------------------------






 ///---------------------------------------------------------------------------
///
/// установка на текущую команду
///
///----------------------------------------------------------------------------
AStateMachine& AStateMachine :: command(AStateObject& state, const int time)
{
	mNextState = &state;
	mNextTime = time;
	return *this;
}
///----------------------------------------------------------------------------






 ///---------------------------------------------------------------------------
///
/// перевод команды
///
///----------------------------------------------------------------------------
void AStateMachine :: transition()
{
	if (mCurrentState)
	{
		mCurrentState->onExit();
	}

	const auto time = millis();

	mCurrentState = mNextState;
	mTimeActive = time + mNextTime;
	if (mCurrentState)
	{
		mCurrentState->onEnter();
		if (mNextTime == 0)
		{
			mTimeActive = time + mCurrentState->onTimeActive();
		}
	}
}

//return the current state
AStateObject& AStateMachine :: current()
{
	return *mCurrentState;
}

//check if state is equal to the currentState
bool AStateMachine :: isState(const AStateObject &state) const
{
	if (&state == mCurrentState)
	{
		return true;
	}
	else 
	{
		return false;
	}
}




