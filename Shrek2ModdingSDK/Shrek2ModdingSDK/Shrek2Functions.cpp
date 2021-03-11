#include "Shrek2ModdingSDK.h"

void Shrek2Functions::ExecuteConsoleCommand(std::string command)
{
	ExecCC(command);
}

void Shrek2Functions::ExecuteConsoleCommands(std::list<std::string> commands)
{
	ExecCCS(commands);
}

void Shrek2Functions::CC(std::string command)
{
	ExecCC(command);
}

void Shrek2Functions::CCS(std::list<std::string> commands)
{
	ExecCCS(commands);
}

void Shrek2Functions::ExecCC(std::string command)
{
	std::ofstream execFile(DllName);
	execFile << command << std::endl;
	execFile.close();
    Exec();
}

void Shrek2Functions::ExecCCS(std::list<std::string> commands)
{
    std::ofstream execFile(DllName);
    for (auto const& cmd : commands) {
        execFile << cmd << std::endl;
    }
    execFile.close();
    Exec();
}

void Shrek2Functions::Exec() 
{
    INPUT ip;

    ip.type = INPUT_KEYBOARD;
    ip.ki.wScan = 0;
    ip.ki.time = 0;
    ip.ki.dwExtraInfo = 0;

    ip.ki.wVk = 0x87;
    ip.ki.dwFlags = 0;
    SendInput(1, &ip, sizeof(INPUT));

    ip.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &ip, sizeof(INPUT));
}