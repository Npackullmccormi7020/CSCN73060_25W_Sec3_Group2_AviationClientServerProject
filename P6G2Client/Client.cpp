#include <windows.networking.sockets.h>
#include <iostream>
#pragma comment(lib, "Ws2_32.lib")
#include <cstdlib>
using namespace std;

// Define our DataPacket here
struct DataPacket
{
	// Packet Number?
	// Timestamp
	// Remaining Fuel
};

// Main function
int main()
{
	// Socket Components
	WSADATA wsaData;
	SOCKET ClientSocket;
	sockaddr_in SvrAddr;

	// Socket Creation
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	ClientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ClientSocket == SOCKET_ERROR)
		return -1;

	// Socket Setup
	SvrAddr.sin_family = AF_INET;
	SvrAddr.sin_port = htons(27001);						// make sure same as Server
	SvrAddr.sin_addr.s_addr = inet_addr("127.0.0.1");		// Set to host PC IP for Server

	// Connect Client to Server
	if (connect(ClientSocket, (struct sockaddr*)&SvrAddr, sizeof(SvrAddr)) == SOCKET_ERROR)
		return -1;

	// Add our Client logic and comunication here

	// File open

	// Send data line by line using packet construct

	// File close

	closesocket(ClientSocket);
	WSACleanup();

	return 1;
}