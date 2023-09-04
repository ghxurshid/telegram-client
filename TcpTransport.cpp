#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>

#include "CRC.h"
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

bool connected = false;

void TcpConnect()
{
    if (connected) return;

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

    connected = true;
}

void TcpDisconnect()
{
    if (!connected) return;

    if (shutdown(sock, SD_SEND) != 0)
    {
        printf("Client: Well, there is something wrong with the shutdown(). The error code : % ld\n", WSAGetLastError());
        return;
    }
    else
    {
        printf("Client: shutdown() looks OK...\n");
    }

    if (closesocket(sock) != 0)
    {
        printf("Client: Cannot close \"SendingSocket\" socket. Error code: %ld\n", WSAGetLastError());
        return;
    }
    else
    {
        printf("Client: Closing \"SendingSocket\" socket...\n");
    }

    if (WSACleanup() != 0)
    {
        printf("Client: WSACleanup() failed!...\n");
        return;
    }        
    else
        printf("Client: WSACleanup() is OK...\n");

    connected = false;
}

uint64_t AvailableBytes()
{
    unsigned long availableBytes;
    ioctlsocket(sock, FIONREAD, &availableBytes);
    return availableBytes;
}

void TcpSend(ByteArray data)
{ 
    if (!connected) TcpConnect();

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

    idx = data.size - 4;
    uint32_t crc = ComputeCRC(data.data, 0, data.size - 4);

    for (int i = 0; i < 4; i++)
    {
        data.data[idx++] = (crc >> (i * 8)) & 0xFF;
    }     
 
    BytesSent = send(sock, (const char*)data.data, data.size, 0);
  
    if (BytesSent == SOCKET_ERROR) printf("TcpSend: send() error %ld.\n", WSAGetLastError());
    else { printf("TcpSend: %i bayts have sended.", BytesSent); sendCount++; }
}

ByteArray TcpReceive()
{
    uint32_t size = 0;
    int count = recv(sock, (char*)size, sizeof(uint32_t), 0);

    ByteArray recvData{};

    if (count != sizeof(uint32_t))
    {
        printf("TcpReceive: count of readed bytes is not equal to sizeof(uint32_t)\n");
        return CreateByteArray(0);;
    }
    
    if (size <= 0 || size > 0X00100000)
    {
        printf("TcpReceive: size is invalid value\n");
        return CreateByteArray(0);;
    }

    recvData = CreateByteArray(size);

    count = recv(sock, (char*)recvData.data, size, 0);

    if (count != size)
    {
        printf("TcpReceive: received data length is not equal to size of 'data'.\n");
        return CreateByteArray(0);;
    }

    int crcIndx = recvData.size - 4;
    uint8_t* data = recvData.data;

    uint32_t crc = ComputeCRC(data, 0, recvData.size - 4);
    uint32_t crcRecv = data[crcIndx + 0] << 0  | 
                       data[crcIndx + 1] << 8  |
                       data[crcIndx + 2] << 16 |
                       data[crcIndx + 3] << 24 ;

    if (crc != crcRecv)
    {
        printf("TcpReceive: received and computed crc is not equal.\n");
        return CreateByteArray(0);
    }

    printf("TcpReceive: recv is ok! %i bayts have readed.\n");
     
    return recvData;       
}