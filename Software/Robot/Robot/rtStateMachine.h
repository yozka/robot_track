#pragma once
#include <Arduino.h>
//-----------------------------------------------------------------------------




namespace SM
{
	//-----------------------------------------------------------------------------




	//-----------------------------------------------------------------------------
#ifndef FAction
	using FAction = void(*)();	//��������
#endif
	//-----------------------------------------------------------------------------






	 ///---------------------------------------------------------------------------
	///
	/// ���� ���������
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
		
		virtual int  onTimeActive() = 0; //����� ���������� �������
	private:

	};
	//-----------------------------------------------------------------------------









	 ///---------------------------------------------------------------------------
	///
	/// ���� ���������
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
	/// ������ ���������
	///
	///----------------------------------------------------------------------------
	class AStateMachine
	{
	public:
		AStateMachine();

		AStateMachine& update();
		AStateMachine& command(AStateObject& state, const int time = 0); //������ �������

		AStateObject& current();
		bool isState(const AStateObject &state) const;

		mutable FAction signal_next = {nullptr}; //��������� �������

	private:
		AStateObject*	mCurrentState;
		AStateObject*	mNextState;
		unsigned long	mTimeActive; //�������� ����� ����������
		int mNextTime;


		void transition(); //�������

	};


}

extern SM::AStateMachine sm;