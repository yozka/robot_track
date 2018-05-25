#pragma once
#include <Arduino.h>
//-----------------------------------------------------------------------------




namespace SM
{
	//-----------------------------------------------------------------------------




	//-----------------------------------------------------------------------------
#ifndef FAction
	using FAction = void(*)();	//действие
#endif
	//-----------------------------------------------------------------------------






	 ///---------------------------------------------------------------------------
	///
	/// ќдно состо¤ние
	///
	///----------------------------------------------------------------------------
	class AStateObject
	{
	public:
		AStateObject() {};
		virtual ~AStateObject() {};

		virtual void onEnter()		= 0;
		virtual void onUpdate()		= 0;
		virtual void onExit()		= 0;
		
		virtual int  onTimeActive() = 0; //врем¤ выполнени¤ команды
	private:

	};
	//-----------------------------------------------------------------------------









	 ///---------------------------------------------------------------------------
	///
	/// ќдно состо¤ние
	///
	///----------------------------------------------------------------------------
	class AState
		:
			public AStateObject
	{
	public:
		AState(FAction actionUpdate, int time = 100);
		AState(FAction actionEnter, FAction actionUpdate, FAction actionExit, int time = 100);

		void onEnter()		override;
		void onUpdate()		override;
		void onExit()		override;
		int	 onTimeActive() override { return timeActive; };

		mutable FAction signal_enter	= { nullptr };
		mutable FAction signal_update	= { nullptr };
		mutable FAction signal_exit		= { nullptr };
		mutable int		timeActive		= { 0 };

	private:


	};
	//-----------------------------------------------------------------------------









	 ///---------------------------------------------------------------------------
	///
	/// ћашина состо¤ний
	///
	///----------------------------------------------------------------------------
	class AStateMachine
	{
	public:
		AStateMachine();

		AStateMachine& update();
		AStateMachine& command(AStateObject& state, const int time = 0); //запуск команды

		AStateObject& current();
		bool isState(const AStateObject &state) const;

		mutable FAction signal_next = {nullptr}; //следующа¤ команда

	private:
		AStateObject*	mCurrentState;
		AStateObject*	mNextState;
		unsigned long	mTimeActive; //активное врем¤ выполнени¤
		int mNextTime;


		void transition(); //перенос

	};


}

extern SM::AStateMachine sm;