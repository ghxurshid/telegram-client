#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>

#include "TcpTransport.h"
#include "TcpMessage.h"

 
// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
//#pragma comment (lib, "Ws2_32.lib")
//#pragma comment (lib, "Mswsock.lib")
//#pragma comment (lib, "AdvApi32.lib")

#pragma comment(lib, "ws2_32.lib")
  
WSADATA wsData;
SOCKET  sock;

// Server/receiver address
SOCKADDR_IN ServerAddr, ThisSenderInfo;

// Server/receiver port to connect to
uint32_t Port = 7171;

uint32_t RetCode;
uint32_t sendCount = 0;

// Be careful with the array bound, provide some checking mechanism...
char sendbuf[1024] = "This is a test string from sender";
uint32_t BytesSent, nlen;

void TcpConnect()
{
    // Initialize Winsock version 2.2
    if (WSAStartup(MAKEWORD(2, 2), &wsData) != 0) {
        std::cerr << "Failed to initialize Winsock." << std::endl;
        return;
    }

    printf("Client: Winsock DLL status is %s.\n", wsData.szSystemStatus);

    // Create a new socket to make a client connection.
    // AF_INET = 2, The Internet Protocol version 4 (IPv4) address family, TCP protocol

    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (sock == INVALID_SOCKET)
    {
        printf("Client: socket() failed! Error code: %ld\n", WSAGetLastError());

        // Do the clean up
        WSACleanup();

        // Exit with error
        return;
    }
    else
        printf("Client: socket() is OK!\n");

    // Server information
    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(12345);  // Server port
    //serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");  // Server IP address
    inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);

    if (connect(sock, reinterpret_cast<sockaddr*>(&serverAddr), sizeof(serverAddr)) == SOCKET_ERROR) {
        printf("Failed to connect to the server.");
        closesocket(sock);
        WSACleanup();
        return;
    }
}

void TcpDisconnect()
{
    if (shutdown(sock, SD_SEND) != 0)
        printf("Client: Well, there is something wrong with the shutdown(). The error code : % ld\n", WSAGetLastError());
    else
        printf("Client: shutdown() looks OK...\n");

    if (closesocket(sock) != 0)
        printf("Client: Cannot close \"SendingSocket\" socket. Error code: %ld\n", WSAGetLastError());
    else
        printf("Client: Closing \"SendingSocket\" socket...\n");

    if (WSACleanup() != 0)
        printf("Client: WSACleanup() failed!...\n");
    else
        printf("Client: WSACleanup() is OK...\n");
}

uint64_t AvailableBytes()
{
    unsigned long availableBytes;
    ioctlsocket(sock, FIONREAD, &availableBytes);
    return availableBytes;
}

void TcpSend(ByteArray data)
{ 
    int idx = 0;
    int lenth12 = data.size + 12;

    for (int i = 0; i < 4; i++)
    {
        data.data[idx ++] = (lenth12 >> (i * 8)) & 0xFF;
    }

    for (int i = 0; i < 4; i++)
    {
        data.data[idx ++] = (sendCount >> (i * 8)) & 0xFF;
    }
     
    Crc32 crc = new Crc32();
    byte[] buffer = crc.ComputeHash(memoryStream.GetBuffer(), 0, 8 + Body.Length).Reverse().ToArray();
    binaryWriter.Write(buffer);
    return memoryStream.ToArray();



    // Sends some data to server/receiver...
    BytesSent = send(sock, (const char*)buff.data, buff.size, 0);
    ClearTcpMessage(message);

    if (BytesSent == SOCKET_ERROR) printf("Client: send() error %ld.\n", WSAGetLastError());
}

TcpMessage TcpReceive()
{
    ByteArray recvData{};
    uint32_t available = 0;
    while ((available = AvailableBytes()) > 0)
    {
        ByteArray buff = CreateByteArray(available);
        uint32_t bytesRead = recv(sock, (char*)buff.data, (int)buff.size, 0);
        recvData = Add2ByteArray(recvData, buff);
    }

    return Decode(recvData);
}