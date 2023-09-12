#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>

#include "CRC.h"
#include "ByteArray.h"
#include "TcpTransport.h"
#include "TcpMessage.h"
 
// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
//#pragma comment (lib, "Ws2_32.lib")
//#pragma comment (lib, "Mswsock.lib")
//#pragma comment (lib, "AdvApi32.lib")

#pragma comment(lib, "ws2_32.lib")

const int   ConnectionPort = 443;
const char* ConnectionAddress = "149.154.175.100";
  
WSADATA wsData;
SOCKET  sock;

// Server/receiver address
SOCKADDR_IN ServerAddr, ThisSenderInfo;
 
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
        printf("Failed to initialize Winsock.\n");
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
    serverAddr.sin_port = htons(ConnectionPort);  // Server port
    //serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");  // Server IP address
    inet_pton(AF_INET, ConnectionAddress, &serverAddr.sin_addr);

    if (connect(sock, reinterpret_cast<sockaddr*>(&serverAddr), sizeof(serverAddr)) == SOCKET_ERROR) {
        printf("Failed to connect to the server.\n");
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

void TcpSend(Packet packet)
{ 
    if (!connected) TcpConnect();

    int size = packet.body.size;
    uint8_t* data = packet.body.data;

    int idx = 0;
    int lenth12 = size + 12;

    for (int i = 0; i < 4; i++)
    {
        data[idx ++] = (lenth12 >> (i * 8)) & 0xFF;
    }

    for (int i = 0; i < 4; i++)
    {
        data[idx ++] = (sendCount >> (i * 8)) & 0xFF;
    }

    idx = size - 4;
    uint32_t crc = ComputeCRC(data, 0, size - 4);

    for (int i = 0; i < 4; i++)
    {
        data[idx++] = (crc >> (i * 8)) & 0xFF;
    }     
 
    BytesSent = send(sock, (const char*)data, size, 0);
  
    if (BytesSent == SOCKET_ERROR) printf("TcpSend: send() error %ld.\n", WSAGetLastError());
    else { printf("TcpSend: %i bayts have sended.\n", BytesSent); sendCount++; }
}

Packet TcpReceive()
{
    uint32_t size = 0;
    int count = recv(sock, (char*)size, sizeof(uint32_t), 0);
  

    if (count != sizeof(uint32_t))
    {
        printf("TcpReceive: count of readed bytes is not equal to sizeof(uint32_t)\n");
        return CreatePacket(0);
    }
    
    if (size <= 32 || size > 0X00100000)
    {
        printf("TcpReceive: size is invalid value\n");
        return CreatePacket(0);
    }

    Packet recvData = CreatePacket(size - 32); //Tcp socketdan o`qilishi kerak bo`lgan hamma bayt uchun joy ajratildi


    int size2 = recvData.body.size;
    uint8_t* data = recvData.body.data;

    int idx = 0;
    char* buff = new char[128];

    for (int i = 0; i < 4; i++)
    {
        data[idx++] = (size >> (i * 8)) & 0xFF;
    }

    do
    {
        count = recv(sock, buff, 128, 0);
        for (int i = 0; i < count; i++)
        {
            if (idx >= size) break;
            data[idx++] = buff[i];
        }
    } while (idx < size);
    
    if (size2 != size)
    {
        printf("TcpReceive: received data length is not equal to size of 'data'.\n");
        return CreatePacket(0);
    }

    int crcIndx = size2 - 4;     

    uint32_t crc = ComputeCRC(data, 0, crcIndx);
    uint32_t crcRecv = data[crcIndx + 0] << 0  | 
                       data[crcIndx + 1] << 8  |
                       data[crcIndx + 2] << 16 |
                       data[crcIndx + 3] << 24 ;

    if (crc != crcRecv)
    {
        printf("TcpReceive: received and computed crc is not equal.\n");
        return CreatePacket(0);
    }

    printf("TcpReceive: recv is ok! %i bayts have readed.\n", size2);
     
    return recvData;       
}