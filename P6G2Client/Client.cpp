#include <windows.networking.sockets.h>
#include <iostream>
#pragma comment(lib, "Ws2_32.lib")
#include <cstdlib>
#include <fstream>
#include <sstream>

using namespace std;

// Define our DataPacket here
struct DataPacket
{
	// Packet Number?
	int PktNum;

	// Timestamp
	//char DateTime[18];
	string DateTIme;		// Will a string work or will it need to be structured

	// Remaining Fuel
	double Fuel;
};

// Main function
int main()
{
	//This is for random file reading
	string Filepaths[]{"katl-kefd-B737-700", "Telem_2023_3_12 14_56_40", "Telem_2023_3_12 16_26_4", "Telem_czba-cykf-pa28-w2_2023_3_1 12_31_27"};

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
	// Seed for rand
	srand (time(NULL));

	// Random file to open
	int fpnum = rand() % 4;
	string fp = Filepaths[fpnum];

	// Open the file
	ifstream fin;
	fin.open(fp);
	if (fin.is_open())
	{
		// Send data line by line using packet construct
		string line;
		DataPacket SPkt;

		// While not at the end of file
		while (!fin.eof())
		{
			// Get the line
			getline(fin, line);

			// Convert lien to stringstream
			istringstream sline(line);

			// Get the first partition of the line and store it in the datetime part of the packet
			getline(sline, SPkt.DateTIme, ',');

			// Create a temp string
			string tempFuel;

			// Get the secodn partition of the lien and store it in the temp variable
			getline(sline, tempFuel);

			// Convert the temp variable from string to double and put into the pkt
			SPkt.Fuel = stod(tempFuel);

			// Assign PKT Num
			// Send PKT

			// Recv Responce

			//Loop again
		}
	}
	else
	{
		cout << "Cannont Open File: " << fp << endl;
	}

	// File close
	fin.close();

	closesocket(ClientSocket);
	WSACleanup();

	return 1;
}