/*
	Copyright (c) 2021 Kevin J. Petersen https://github.com/kevinjpetersen/
*/

#include "Shrek2ModdingSDK.h"

void Shrek2Sound::AddSound(std::string soundFile, std::string alias)
{
	std::string path = DllPath + "\\" + soundFile;
	char chShortPath[1024];
	GetShortPathName(path.c_str(), chShortPath, 1024);

	std::string formattedStr(chShortPath);

	std::string playSoundString = "open " + formattedStr + " alias " + alias;

	AddedSounds.insert(std::pair<std::string, std::string>(alias, playSoundString));
}

void Shrek2Sound::Play(std::string alias)
{
	Stop(alias);
	mciSendString(AddedSounds[alias].c_str(), NULL, 0, 0);
	mciSendString(("play " + alias).c_str(), NULL, 0, 0);
}

void Shrek2Sound::PlayLoop(std::string alias)
{
	// WIP
	/*Stop(alias);
	mciSendString(AddedSounds[alias].c_str(), NULL, 0, 0);
	mciSendString(("play " + alias + " notify repeat").c_str(), NULL, 0, 0);*/
}

void Shrek2Sound::Stop(std::string alias)
{
	mciSendString(("stop " + alias).c_str(), NULL, 0, 0);
	mciSendString(("close " + alias).c_str(), NULL, 0, NULL);
}
