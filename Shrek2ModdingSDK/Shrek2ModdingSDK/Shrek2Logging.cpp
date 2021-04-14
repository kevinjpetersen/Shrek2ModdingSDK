#include "Shrek2ModdingSDK.h"

void Shrek2Logging::Log(std::string message)
{
	try {
		std::cout << "[LOG] " << message << std::endl;
	}
	catch (std::exception& ex) {}
}

void Shrek2Logging::Log(char* message)
{
	try {
		std::cout << "[LOG] " << message << std::endl;
	}
	catch (std::exception& ex) {}
}

void Shrek2Logging::LogError(std::string title, std::string message)
{
	try {
		std::cout << "[ERROR] [" << title << "] " << message << std::endl;
	}
	catch (std::exception& ex) {}
}

void Shrek2Logging::LogError(std::string title, char* message)
{
	try {
		std::cout << "[ERROR] [" << title << "] " << message << std::endl;
	}
	catch (std::exception& ex) {}
}
