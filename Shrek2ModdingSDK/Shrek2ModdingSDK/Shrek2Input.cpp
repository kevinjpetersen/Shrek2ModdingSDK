#include "Shrek2ModdingSDK.h"

bool Shrek2Input::OnKeyPress(int vKey)
{
    return (GetAsyncKeyState(vKey) & 1);
}
