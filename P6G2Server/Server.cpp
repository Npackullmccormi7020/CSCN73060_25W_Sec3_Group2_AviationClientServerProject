#include <windows.networking.sockets.h>
#include <iostream>
#pragma comment(lib, "Ws2_32.lib")
using namespace std;

// Define our DataPacket here
struct DataPacket
{
	// Packet Number?
	int PktNum;

	// Timestamp
	char DateTime[18];
	//string DateTIme;		// Will a string work or will it need to be structured

	// Remaining Fuel
	double Fuel;
};

void ThreadLogic()
{

}

// Main function
int main()
{
	// Socket Components
	WSADATA wsaData;
	SOCKET ServerSocket, ConnectionSocket;
	sockaddr_in SvrAddr;

	// Socket creation
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	ServerSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ServerSocket == SOCKET_ERROR)
		return -1;

	// Socket Setup Bind
	SvrAddr.sin_family = AF_INET;
	SvrAddr.sin_addr.s_addr = INADDR_ANY;				// Will this check for everything from external?
	SvrAddr.sin_port = htons(27001);					// Make sure to use this for comunication
	bind(ServerSocket, (struct sockaddr*)&SvrAddr, sizeof(SvrAddr));

	if (ServerSocket == SOCKET_ERROR)
		return -1;

	// Listen (TCP)
	listen(ServerSocket, 1);
	cout << "Waiting for client connection\n" << endl;
	ConnectionSocket = SOCKET_ERROR;
	ConnectionSocket = accept(ServerSocket, NULL, NULL);		// MAKE THIS PARALLEL?

	if (ConnectionSocket == SOCKET_ERROR)
		return -1;

	cout << "Connection Established" << endl;

	// Code the comunication here, or in thread logic if we multithread

	closesocket(ConnectionSocket);	//closes incoming socket
	closesocket(ServerSocket);	    //closes server socket	
	WSACleanup();					//frees Winsock resources

	return 1;
}