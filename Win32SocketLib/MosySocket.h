#pragma once
#include <Winsock2.h>
#include <string.h>
#include <string>
#include <direct.h>
#include <vector>
#include "CharsetUtils.h"
#pragma comment(lib,"Ws2_32.lib")

#define BUF_LENGTH 1024
#define MIN_BUF 128
#ifdef DLL_FILE
class _declspec(dllexport)
	MosySocket
#else
class _declspec(dllexport)
	MosySocket
#endif
{
protected:
	SOCKET CoreSocket = NULL;
	std::wstring RecvStr;
	DWORD ConnectStatus;
	DWORD Port = 80;
	void SetupSocket();
	void Listen();
	void Bind(DWORD Port);
	void Bind();
	DWORD GetPort();
	void ShutDownSocket();
public:

	~MosySocket();
	enum MosySocketErrorCode {
		MSE_TIMEOUT,
		MSE_FAILED_LOAD_WINSOCKET,
		MSE_INVALID_SOCKET,
		MSE_FAILED_LISTEN,
		MSE_FAILED_BIND,
		MSE_ERROR,
	};
	struct MosySocketException : public std::exception
	{
		MosySocketErrorCode ErrorCode;
		int WSAErrCode;
		MosySocketException(MosySocketErrorCode MosyErrorCode)
		{
			ErrorCode = MosyErrorCode;
		}
		MosySocketException(MosySocketErrorCode MosyErrorCode, int WSACode)
		{
			ErrorCode = MosyErrorCode;
			WSAErrCode = WSACode;
		}
		const char * what() const throw ()
		{
			switch (ErrorCode)
			{
			case MSE_TIMEOUT:
				return "Socket Error:Connect Time Out.";
				break;
			case MSE_FAILED_LOAD_WINSOCKET:
				return "Socket Error:Failed to Load Win Socket.";
				break;
			case MSE_INVALID_SOCKET:
				return "Socket Error:Invalid Socket.";
				break;
			case MSE_FAILED_LISTEN:
				return "Socket Error:Failed to Listen.";
				break;
			case MSE_FAILED_BIND:
				return "Socket Error:Failed to Bind.";
				break;
			case MSE_ERROR:
				return "Socket Error.";
				break;
			default:
				return "Socket Unknow Error.";
				break;
			}
		}
		MosySocketErrorCode GetErrorCode()
		{
			return ErrorCode;
		}
		int GetWSAErrCode()
		{
			return WSAErrCode;
		}
	};
	bool HasConnected();
	std::wstring Receive();
	void Send(std::wstring Msg);
	void Send(std::string Msg);
	DWORD GetStatusCode();
	MosySocket(SOCKET Socket);
	void Send(std::vector<char> Msg, int size);
	MosySocket();
	MosySocket(MosySocket* Source);
	int GetConnectPort();
	wstring GetConnectAddr();
	void operator =(MosySocket* Source);
	void Close();
	SOCKET GetHandler();
};

