#include "pch.h"
#include "MosyLogger.h"
#include <string>
#pragma warning(disable:4996)
CRITICAL_SECTION Critical;

HANDLE MosyLogger::Thread = NULL;
queue<string> MosyLogger::LogList;
wstring MosyLogger::GenHead()
{
	time_t nowtime;
	tm* p = NULL;
	time(&nowtime);
	p = gmtime(&nowtime);
	wstring days[] = { L"Sun.",L"Mon.",L"Tues.",L"Wed.",L"Thur.",L"Fri.",L"Sat." };
	wstring mons[] = { L"Jan.",L"Feb.",L"Mar.",L"Apr.",L"May.",L"June.",L"July.",L"Aug.",L"Sept.",L"Oct.",L"Nov.",L"Dec." };
	wchar_t str[MAX_PATH];
	wsprintfW(str, L"[%02d:%02d:%02d %04d/%02d/%02d ", p->tm_hour, p->tm_min, p->tm_sec,  p->tm_year + 1900, p->tm_mon, p->tm_mday);
	wstring sss = str;
	sss += days[p->tm_wday] + L" " + mons[p->tm_mon] + L"]";
	return sss;
}

void MosyLogger::BootLogo()
{
	/*
	  __  __                  _____
	 |  \/  |                / ____|
	 | \  / | ___  ___ _   _| (___   ___ _ ____   _____ _ __
	 | |\/| |/ _ \/ __| | | |\___ \ / _ \ '__\ \ / / _ \ '__|
	 | |  | | (_) \__ \ |_| |____) |  __/ |   \ V /  __/ |
	 |_|  |_|\___/|___/\__, |_____/ \___|_|    \_/ \___|_|
						__/ |
	 ========          |___/        Mosy Server Framework====
	 ========================================================
	*/
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);
	printf(" __  __                  _____                          \n");
	printf("|  \\/  |                / ____|                         \n");
	printf("| \\  / | ___  ___ _   _| (___   ___ _ ____   _____ _ __ \n");
	printf("| |\\/| |/ _ \\/ __| | | |\\___ \\ / _ \\ '__\\ \\ / / _ \\ '__|\n");
	printf("| |  | | (_) \\__ \\ |_| |____) |  __/ |   \\ V /  __/ |   \n");
	printf("|_|  |_|\\___/|___/\\__, |_____/ \\___|_|    \\_/ \\___|_|   \n");
	printf("                   __/ |                                \n");
	printf("========          |___/        Mosy Server Framework====\n");
	printf("========================================================\n");
	Thread = CreateThread(NULL, NULL, LogThread, NULL, NULL, NULL);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
	InitializeCriticalSection(&Critical);
	Log(MosyValue(L"MosyServer Started"));
}

void MosyLogger::Log(MosyValue Text)
{
	EnterCriticalSection(&Critical);
	MosyLogger::LogList.push(MosyString::WString2String(Text.GetString()));
	LeaveCriticalSection(&Critical);
}

DWORD __stdcall LogThread(LPVOID Param)
{
	while (1)
	{
		if (!MosyLogger::LogList.empty())
		{
			wstring out = MosyLogger::GenHead();
			//out += Text.GetString() + L"\n";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);
			wprintf(out.c_str());
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
			printf((MosyLogger::LogList.front().substr(0, 1024) + "\n").c_str());
			EnterCriticalSection(&Critical);
			MosyLogger::LogList.pop();
			LeaveCriticalSection(&Critical);
		}
		Sleep(2);
	}
	return 0;
}
