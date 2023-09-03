// TelegramClientExampleCPP.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string.h>
#include <memory.h>
#include <locale>

#include "TelegramClient.h"

uint32_t main()
{
    setlocale(LC_ALL, "Russian");

    uint32_t apiId = 22236638;
    char* apiHash = (char*)"fdf44e15f78621fe8d76caefac19761a";
    
    // ����� �������� ������������
    char* phoneNum = (char*)"+998998346521";

    // ������� ��������� Telegram ������� � �������� API ID � API Hash
    TelegramClient* client = CreateTelegramClient(apiId, apiHash);
    // ������������� ���������� � Telegram ��������
    Connect(client, false);

    // ���������, ����������� �� ������������
    bool isAuth = IsUserAuthorized(client);
  
    // ���� ������������ �� �����������
    if (!isAuth)
    {
        printf("���� ����������� �� ���������� :(\n");
 
        // ���������� ������ �� �������� ���� �������������� �� ��������� ����� ��������
        char* hash = SendCodeRequest(client, phoneNum);
        printf("������� ��� �� SMS:\n");
        char* code = new char[6];
        uint32_t ret = scanf_s(code);

        // �������� ������������ ������������ � ���������� �����
        TLUser* user = MakeAuth(client, phoneNum, hash, code);

        if (user != nullptr)
        {
            printf("������������ %s �����������", user->FirstName);
        } 
    }
    else
    {
        printf("���� ����������� ���������� :)\n");
    }
     
    // �������� ������ ��������� ������������
    TLContacts contacts = GetContacts(client);
    uint32_t contactCount = contacts.size;
    printf("� ��� %i ���������", contactCount);    
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
