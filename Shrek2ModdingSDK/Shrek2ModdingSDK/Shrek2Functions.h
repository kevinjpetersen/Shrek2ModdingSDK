#pragma once
class Shrek2Functions
{
public:
	Shrek2Functions() {

	}
	Shrek2Functions(std::string dllName) {
		DllName = dllName;
	}
	void ExecuteConsoleCommand(std::string command);
	void ExecuteConsoleCommands(std::list<std::string> commands);
	void CC(std::string command);
	void CCS(std::list<std::string> commands);
	void OpenMap(Shrek2Maps map);
private:
	void ExecCC(std::string command);
	void ExecCCS(std::list<std::string> commands);
	void Exec();
	std::string MapIdToString(int mapId);
	std::string DllName;
};

