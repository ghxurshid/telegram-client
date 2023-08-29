#include "TcpTransport.h"
#include "TcpMessage.h"

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

  
WSADATA wsaData;
SOCKET  sock;

// Server/receiver address
SOCKADDR_IN ServerAddr, ThisSenderInfo;

// Server/receiver port to connect to
unsigned int Port = 7171;

int RetCode;
int sendCount = 0;

// Be careful with the array bound, provide some checking mechanism...
char sendbuf[1024] = "This is a test string from sender";
int BytesSent, nlen;

void Connect()
{
    // Initialize Winsock version 2.2
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    printf("Client: Winsock DLL status is %s.\n", wsaData.szSystemStatus);

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

    // Set up a SOCKADDR_IN structure that will be used to connect
    // to a listening server on port 5150. For demonstration
    // purposes, let's assume our server's IP address is 127.0.0.1 or localhost
    // IPv4

    ServerAddr.sin_family = AF_INET;

    // Port no.
    ServerAddr.sin_port = htons(Port);

    // The IP address
    ServerAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Make a connection to the server with socket SendingSocket.
    RetCode = connect(sock, (SOCKADDR*)&ServerAddr, sizeof(ServerAddr));

    if (RetCode != 0)
    {
        printf("Client: connect() failed! Error code: %ld\n", WSAGetLastError());

        // Close the socket
        closesocket(sock);

        // Do the clean up
        WSACleanup();

        // Exit with error
        return;
    }
    else
    {
        printf("Client: connect() is OK, got connected...\n");
        printf("Client: Ready for sending and/or receiving data...\n");
    }

    // At this point you can start sending or receiving data on
    // the socket SendingSocket.
    // Some info on the receiver side...

    getsockname(sock, (SOCKADDR*)&ServerAddr, (int*)sizeof(ServerAddr));
    printf("Client: Receiver IP(s) used: %s\n", inet_ntoa(ServerAddr.sin_addr));
    printf("Client: Receiver port used: %d\n", htons(ServerAddr.sin_port));
}

void Disconnect()
{
    if (shutdown(sock, SD_SEND) != 0)
        printf("Client: Well, there is something wrong with the shutdown(). The error code : % ld\n", WSAGetLastError());
    else
        printf("Client: shutdown() looks OK...\n");

    // When you are finished sending and receiving data on socket SendingSocket,
    // you should close the socket using the closesocket API. We will
    // describe socket closure later in the chapter.
    if (closesocket(sock) != 0)
        printf("Client: Cannot close \"SendingSocket\" socket. Error code: %ld\n", WSAGetLastError());
    else
        printf("Client: Closing \"SendingSocket\" socket...\n");

    // When your application is finished handling the connection, call WSACleanup.
    if (WSACleanup() != 0)
        printf("Client: WSACleanup() failed!...\n");
    else
        printf("Client: WSACleanup() is OK...\n");
}

unsigned long AvailableBytes()
{
    unsigned long availableBytes;
    ioctlsocket(sock, FIONREAD, &availableBytes);
    return availableBytes;
}

void Send(ByteArray data)
{
    TcpMessage message{ sendCount++, data };
    ByteArray buff = Encode(message);

    // Sends some data to server/receiver...
    BytesSent = send(sock, (const char*)buff.data, buff.size, 0);

    if (BytesSent == SOCKET_ERROR) printf("Client: send() error %ld.\n", WSAGetLastError());
}

TcpMessage Receive()
{
    ByteArray recvData;
    unsigned int available = 0;
    while ((available = AvailableBytes()) > 0)
    {
        ByteArray buff = CreateByteArray(available);
        int bytesRead = recv(sock, (char*)buff.data, (int)buff.size, 0);
        recvData = Add2ByteArray(recvData, buff);
    }

    return Decode(recvData);
}