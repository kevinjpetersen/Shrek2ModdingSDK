#include "Shrek2ModdingSDK.h"

bool Shrek2Trigger::IsInsideTrigger(float bx, float by)
{
	return (abs(X - bx) * 2 < (Size)) &&
		(abs(Y - by) * 2 < (Size));
}
