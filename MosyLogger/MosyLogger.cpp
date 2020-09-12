#include "pch.h"
#include "MosyLogger.h"
#include <string>

wstring MosyLogger::GenHead()
{
	time_t nowtime;
	struct tm* p;;
	time(&nowtime);
	wstring days[] = { L"Sun.",L"Mon.",L"Tues.",L"Wed.",L"Thur.",L"Fri.",L"Sat." };
	wstring mons[] = { L"Jan.",L"Feb.",L"Mar.",L"Apr.",L"May.",L"June.",L"July.",L"Aug.",L"Sept.",L"Oct.",L"Nov.",L"Dec." };
	wchar_t str[MAX_PATH];
	wsprintfW(str, L"[%d:%d:%d %d/%d/%d ", p->tm_hour, p->tm_min, p->tm_sec, p->tm_year, p->tm_mon, p->tm_mday);
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
	printf(" __  __                  _____                          \n");
	printf("|  \/  |                / ____|                         \n");
	printf("| \  / | ___  ___ _   _| (___   ___ _ ____   _____ _ __ \n");
	printf("| |\/| |/ _ \/ __| | | |\___ \ / _ \ '__\ \ / / _ \ '__|\n");
	printf("| |  | | (_) \__ \ |_| |____) |  __/ |   \ V /  __/ |   \n");
	printf("|_|  |_|\___/|___/\__, |_____/ \___|_|    \_/ \___|_|   \n");
	printf("                   __/ |                                \n");
	printf("========          |___/        Mosy Server Framework====\n");
	printf("========================================================\n");
	Log(MosyValue(L"MosyServer Started"));
}

void MosyLogger::Log(MosyValue Text)
{
	wstring out = GenHead();
	out += Text.GetString() + L"\n";
	wprintf(out.c_str());
}
