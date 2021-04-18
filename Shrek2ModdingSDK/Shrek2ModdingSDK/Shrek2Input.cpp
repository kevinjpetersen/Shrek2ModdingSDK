/*
    Copyright (c) 2021 Kevin J. Petersen https://github.com/kevinjpetersen/
*/

#include "Shrek2ModdingSDK.h"

bool Shrek2Input::OnKeyPress(Keys key)
{
    return OnKeyPress(KeyToVKey(key));
}

bool Shrek2Input::OnKeyPress(std::string keyBindName)
{
    try {
        if (!IsLoaded) return false;
        if (LoadedJson.count(keyBindName) == 0) return false;
        std::string keyBindValue = (std::string)LoadedJson[keyBindName];

        return OnKeyPress(KeyToVKey(keyBindValue));
    }
    catch (std::exception& ex)
    {
        Shrek2Logging::LogError("Shrek2Input::OnKeyPress2", ex.what());
        return false;
    }
}

bool Shrek2Input::SimulateKeyPress(Keys key)
{
    try {
        int vkey = KeyToVKey(key);
        PostMessage(WindowHandle, WM_KEYDOWN, (int)vkey, 0);
        PostMessage(WindowHandle, WM_KEYUP, (int)vkey, 0);
        return true;
    }
    catch (std::exception& ex)
    {
        Shrek2Logging::LogError("Shrek2Input::SimulateKeyPress", ex.what());
        return false;
    }
}

bool Shrek2Input::OnKeyPress(int vkey)
{
    try {
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
            }
            else if (GetAsyncKeyState(KeyToVKey(Keys::ESCAPE)) & 1)
            {
                AllowKeyInput = true;
                ClearKeyInputBuffer();
                return false;
            }

            if (!AllowKeyInput) return false;
        }

        return (GetAsyncKeyState(vkey) & 1);
    }
    catch (std::exception& ex)
    {
        Shrek2Logging::LogError("Shrek2Input::OnKeyPress1", ex.what());
        return false;
    }
}

bool Shrek2Input::LoadBinds()
{
    try
    {
        if (DllPath.empty()) return false;

        std::string filePath = DllPath + "\\" + "binds.json";
        if (BindsExists(filePath) == false) {
            IsLoaded = false;
            std::cout << "Loaded binds: " << (IsLoaded ? "Yes" : "No") << std::endl;
            return false;
        }

        std::ifstream t(filePath);
        std::string str((std::istreambuf_iterator<char>(t)),
            std::istreambuf_iterator<char>());

        LoadedJson = json::parse(str);
        IsLoaded = true;

        std::cout << "Loaded binds: " << (IsLoaded ? "Yes" : "No") << std::endl;

        return true;
    }
    catch (std::exception& ex)
    {
        IsLoaded = false;
        Shrek2Logging::LogError("Shrek2Input::LoadBinds", ex.what());
        std::cout << "Loaded binds: " << (IsLoaded ? "Yes" : "No") << std::endl;
        return false;
    }
}

bool Shrek2Input::BindsExists(std::string name)
{
    try {
        std::ifstream f(name.c_str());
        return f.good();
    }
    catch (std::exception& ex)
    {
        Shrek2Logging::LogError("Shrek2Input::BindsExists", ex.what());
        return false;
    }
}

void Shrek2Input::ClearKeyInputBuffer()
{
    try {
        for (int keyInt = Keys::A; keyInt != Keys::RIGHT_MOUSE_BUTTON; keyInt++)
        {
            Keys key = static_cast<Keys>(keyInt);
            GetAsyncKeyState(KeyToVKey(key));
        }
    }
    catch (std::exception& ex)
    {
        Shrek2Logging::LogError("Shrek2Input::ClearKeyInputBuffer", ex.what());
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
    case Keys::LEFT_MOUSE_BUTTON: return 0x01;
    case Keys::RIGHT_MOUSE_BUTTON: return 0x02;
    case Keys::END: return 0x23;
    default: return -1;
    }
}

int Shrek2Input::KeyToVKey(std::string key)
{
    if (Shrek2Utils::DoesEqualForced(key, "A")) return KeyToVKey(Keys::A);
    if (Shrek2Utils::DoesEqualForced(key, "B")) return KeyToVKey(Keys::B);
    if (Shrek2Utils::DoesEqualForced(key, "C")) return KeyToVKey(Keys::C);
    if (Shrek2Utils::DoesEqualForced(key, "D")) return KeyToVKey(Keys::D);
    if (Shrek2Utils::DoesEqualForced(key, "E")) return KeyToVKey(Keys::E);
    if (Shrek2Utils::DoesEqualForced(key, "F")) return KeyToVKey(Keys::F);
    if (Shrek2Utils::DoesEqualForced(key, "G")) return KeyToVKey(Keys::G);
    if (Shrek2Utils::DoesEqualForced(key, "H")) return KeyToVKey(Keys::H);
    if (Shrek2Utils::DoesEqualForced(key, "I")) return KeyToVKey(Keys::I);
    if (Shrek2Utils::DoesEqualForced(key, "J")) return KeyToVKey(Keys::J);
    if (Shrek2Utils::DoesEqualForced(key, "K")) return KeyToVKey(Keys::K);
    if (Shrek2Utils::DoesEqualForced(key, "L")) return KeyToVKey(Keys::L);
    if (Shrek2Utils::DoesEqualForced(key, "M")) return KeyToVKey(Keys::M);
    if (Shrek2Utils::DoesEqualForced(key, "N")) return KeyToVKey(Keys::N);
    if (Shrek2Utils::DoesEqualForced(key, "O")) return KeyToVKey(Keys::O);
    if (Shrek2Utils::DoesEqualForced(key, "P")) return KeyToVKey(Keys::P);
    if (Shrek2Utils::DoesEqualForced(key, "Q")) return KeyToVKey(Keys::Q);
    if (Shrek2Utils::DoesEqualForced(key, "R")) return KeyToVKey(Keys::R);
    if (Shrek2Utils::DoesEqualForced(key, "S")) return KeyToVKey(Keys::S);
    if (Shrek2Utils::DoesEqualForced(key, "T")) return KeyToVKey(Keys::T);
    if (Shrek2Utils::DoesEqualForced(key, "U")) return KeyToVKey(Keys::U);
    if (Shrek2Utils::DoesEqualForced(key, "V")) return KeyToVKey(Keys::V);
    if (Shrek2Utils::DoesEqualForced(key, "W")) return KeyToVKey(Keys::W);
    if (Shrek2Utils::DoesEqualForced(key, "X")) return KeyToVKey(Keys::X);
    if (Shrek2Utils::DoesEqualForced(key, "Y")) return KeyToVKey(Keys::Y);
    if (Shrek2Utils::DoesEqualForced(key, "Z")) return KeyToVKey(Keys::Z);

    if (Shrek2Utils::DoesEqualForced(key, "0")) return KeyToVKey(Keys::NUMBER_0);
    if (Shrek2Utils::DoesEqualForced(key, "1")) return KeyToVKey(Keys::NUMBER_1);
    if (Shrek2Utils::DoesEqualForced(key, "2")) return KeyToVKey(Keys::NUMBER_2);
    if (Shrek2Utils::DoesEqualForced(key, "3")) return KeyToVKey(Keys::NUMBER_3);
    if (Shrek2Utils::DoesEqualForced(key, "4")) return KeyToVKey(Keys::NUMBER_4);
    if (Shrek2Utils::DoesEqualForced(key, "5")) return KeyToVKey(Keys::NUMBER_5);
    if (Shrek2Utils::DoesEqualForced(key, "6")) return KeyToVKey(Keys::NUMBER_6);
    if (Shrek2Utils::DoesEqualForced(key, "7")) return KeyToVKey(Keys::NUMBER_7);
    if (Shrek2Utils::DoesEqualForced(key, "8")) return KeyToVKey(Keys::NUMBER_8);
    if (Shrek2Utils::DoesEqualForced(key, "9")) return KeyToVKey(Keys::NUMBER_9);
  
    return -1;
}
