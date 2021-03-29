/*
    Copyright (c) 2021 Kevin J. Petersen https://github.com/kevinjpetersen/
*/

#include "Shrek2ModdingSDK.h"

bool Shrek2Input::OnKeyPress(Keys key)
{
    int vkey = KeyToVKey(key);
    if (vkey == -1) return false;

    if (EnableConsoleProtection)
    {
        if (GetAsyncKeyState(KeyToVKey(Keys::TAB)) & 1)
        {
            AllowKeyInput = false;
            ClearKeyInputBuffer();
            return false;
        }
        else if (GetAsyncKeyState(KeyToVKey(Keys::ENTER)) & 1)
        {
            AllowKeyInput = true;
            ClearKeyInputBuffer();
            return false;
        } else if (GetAsyncKeyState(KeyToVKey(Keys::ESCAPE)) & 1)
        {
            AllowKeyInput = true;
            ClearKeyInputBuffer();
            return false;
        }

        if (!AllowKeyInput) return false;
    }

    return (GetAsyncKeyState(vkey) & 1);
}

void Shrek2Input::ClearKeyInputBuffer()
{
    for (int keyInt = Keys::A; keyInt != Keys::ESCAPE; keyInt++)
    {
        Keys key = static_cast<Keys>(keyInt);
        GetAsyncKeyState(KeyToVKey(key));
    }
}

int Shrek2Input::KeyToVKey(Keys key)
{
    switch (key)
    {
    case Keys::A: return 0x41;
    case Keys::B: return 0x42;
    case Keys::C: return 0x43;
    case Keys::D: return 0x44;
    case Keys::E: return 0x45;
    case Keys::F: return 0x46;
    case Keys::G: return 0x47;
    case Keys::H: return 0x48;
    case Keys::I: return 0x49;
    case Keys::J: return 0x4A;
    case Keys::K: return 0x4B;
    case Keys::L: return 0x4C;
    case Keys::M: return 0x4D;
    case Keys::N: return 0x4E;
    case Keys::O: return 0x4F;
    case Keys::P: return 0x50;
    case Keys::Q: return 0x51;
    case Keys::R: return 0x52;
    case Keys::S: return 0x53;
    case Keys::T: return 0x54;
    case Keys::U: return 0x55;
    case Keys::V: return 0x56;
    case Keys::W: return 0x57;
    case Keys::X: return 0x58;
    case Keys::Y: return 0x59;
    case Keys::Z: return 0x5A;
    case Keys::NUMBER_0: return 0x30;
    case Keys::NUMBER_1: return 0x31;
    case Keys::NUMBER_2: return 0x32;
    case Keys::NUMBER_3: return 0x33;
    case Keys::NUMBER_4: return 0x34;
    case Keys::NUMBER_5: return 0x35;
    case Keys::NUMBER_6: return 0x36;
    case Keys::NUMBER_7: return 0x37;
    case Keys::NUMBER_8: return 0x38;
    case Keys::NUMBER_9: return 0x39;
    case Keys::TAB: return 0x09;
    case Keys::ENTER: return 0x0D;
    case Keys::ESCAPE: return 0x1B;
    default: return -1;
    }
}
