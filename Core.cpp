#include <locale>
#include "Core.h"
#include "TelegramClient.h"

void Start()
{
    setlocale(LC_ALL, "Russian");

    uint32_t apiId = 22236638;
    ByteArray apiHash = CreateByteArray(32);
    apiHash.data = (uint8_t*)"fdf44e15f78621fe8d76caefac19761a";

    // ����� �������� ������������
    ByteArray phoneNum = CreateByteArray(13);
    phoneNum.data = (uint8_t*)"+998998346521";

    // ������� ��������� Telegram ������� � �������� API ID � API Hash
    TelegramClient client = CreateTelegramClient(apiId, apiHash);
    // ������������� ���������� � Telegram ��������
    Connect(client, false);

    // ���������, ����������� �� ������������
    bool isAuth = IsUserAuthorized(client);

    // ���� ������������ �� �����������
    if (!isAuth)
    {
        printf("���� ����������� �� ���������� :(\n");

        // ���������� ������ �� �������� ���� �������������� �� ��������� ����� ��������
        ByteArray hash = SendCodeRequest(client, phoneNum);
        printf("������� ��� �� SMS:\n");
        ByteArray code = CreateByteArray(6);
        uint32_t ret = scanf_s((char*)code.data);

        // �������� ������������ ������������ � ���������� �����
        TLUser* user = MakeAuth(client, phoneNum, hash, code);

        if (user != nullptr)
        {
            printf("������������ %s �����������\n", user->FirstName.data);
        }
    }
    else
    {
        printf("���� ����������� ���������� :)\n");
    }

    // �������� ������ ��������� ������������
    TLContacts contacts = GetContacts(client);
    uint32_t contactCount = contacts.size;
    printf("� ��� %i ���������\n", contactCount);
}
