#pragma once
#include "pch.h"

DWORD _declspec(dllimport) ReceiverThread(LPVOID LParam);
DWORD _declspec(dllimport) SenderThread(LPVOID LParam);