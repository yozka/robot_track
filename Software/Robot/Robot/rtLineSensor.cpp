﻿#include "rtLineSensor.h"
///----------------------------------------------------------------------------





///----------------------------------------------------------------------------
static ALineSensor line;
///----------------------------------------------------------------------------






 ///---------------------------------------------------------------------------
///
/// Constructor
///
///----------------------------------------------------------------------------
ALineSensor :: ALineSensor()
{

}
///----------------------------------------------------------------------------




 ///---------------------------------------------------------------------------
///
/// Destructor
///
///----------------------------------------------------------------------------
ALineSensor :: ~ALineSensor()
{

}
///----------------------------------------------------------------------------




 ///---------------------------------------------------------------------------
///
/// настройка
///
///----------------------------------------------------------------------------
void ALineSensor :: begin()
{
	pinMode(Setting::pinLineSensorA, INPUT);
	pinMode(Setting::pinLineSensorB, INPUT);
	pinMode(Setting::pinLineSensorC, INPUT);
}
///----------------------------------------------------------------------------




 ///---------------------------------------------------------------------------
///
/// левый сенсор
///
///----------------------------------------------------------------------------
bool ALineSensor :: left() const
{
	  return mLeft;
	  //return digitalRead(Setting::pinLineSensorA) != 0;
}
///----------------------------------------------------------------------------




 ///---------------------------------------------------------------------------
///
/// сентральный сенсор
///
///----------------------------------------------------------------------------
bool ALineSensor :: center() const
{
    return mCenter;
	  //return digitalRead(Setting::pinLineSensorB) != 0;
}
///----------------------------------------------------------------------------







 ///---------------------------------------------------------------------------
///
/// правый сенсор
///
///----------------------------------------------------------------------------
bool ALineSensor :: right() const
{
	  return mRight;
	  //return digitalRead(Setting::pinLineSensorC) != 0;
}
///----------------------------------------------------------------------------





 ///---------------------------------------------------------------------------
///
/// обновление
///
///----------------------------------------------------------------------------
void ALineSensor :: update()
{
  //left
  mFLeft = mFLeft << 1;
  if (digitalRead(Setting::pinLineSensorA) != 0)
  {
    mFLeft |= 1;
  }

  mFCenter = mFCenter << 1;
  if (digitalRead(Setting::pinLineSensorB) != 0)
  {
    mFCenter |= 1;
  }



  //right
  mFRight = mFRight << 1;
  if (digitalRead(Setting::pinLineSensorC) != 0)
  {
    mFRight |= 1;
  }
  


  const bool l = mFLeft > 0 ? true : false;
  const bool c = mFCenter > 0 ? true : false;
  const bool r = mFRight > 0 ? true : false;
  



  if (mLeft == l && mCenter == c && mRight == r)
  {
      return;
  }

  mLeft = l;
  mCenter = c;
  mRight = r;


  if (signal_detect)
  {
      signal_detect();
  }
}
///----------------------------------------------------------------------------





